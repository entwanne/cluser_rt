#ifndef _TRACECLIENT_HPP_
#define _TRACECLIENT_HPP_

#include <set>
#include <array>
#include <tuple>
#include <map>
#include <functional>
#include "Network/Calculator.hpp"
#include "Network/Consumer.hpp"

#include "Rt/Scene.hpp"
#include "Rt/Objects/Objects.hpp"
#include "Rt/Lights/Lights.hpp"

#include "Network/consumer_collect.hpp"
#include "expand_tuple.hpp"
#include "constructor.hpp"

using namespace Rt;

class TraceClient
{
public:

  TraceClient(const std::string& conn): scene(nullptr),
				     _calc(conn, std::bind(&TraceClient::calculate_chunk, this, std::placeholders::_1, std::placeholders::_2), std::bind(&TraceClient::initialize_scene, this, std::placeholders::_1, std::placeholders::_2))
  {}

  void start()
  {
    _calc.start();
  }

  template < typename L, typename ... Types >
  Lights::Light* construct_light(Network::Consumer& consumer)
  {
    std::tuple< Types... > properties = Network::collect< Types... >(consumer);
    int color;
    consumer.read(color);
    double intensity;
    consumer.read(intensity);
    return call_expand_tuple< Lights::Light* >(constructor< L, Lights::Light >(), properties, color, intensity, scene);
  }

  template < typename O, typename ... Types >
  Objects::Object* construct_object(Network::Consumer& consumer)
  {
    std::tuple< Types... > properties = Network::collect< Types... >(consumer);
    int color;
    consumer.read(color);
    matrix_t m;
    consumer.read(m);
    matrix_t inv_m;
    consumer.read(inv_m);
    return call_expand_tuple< Objects::Object* >(constructor< O, Objects::Object >(), properties, color, m, inv_m, scene);
  }

  void initialize_scene(const char* data, size_t size)
  {
    Network::Consumer consumer(data, size);

    double cam[3];
    double dist;
    consumer.read(cam);
    consumer.read(dist);

    int scn_size[2];
    consumer.read(scn_size);
    int scn_definition[2];
    consumer.read(scn_definition);

    scene = new Scene(Camera(Point(cam[0], cam[1], cam[2]), dist), dim_t(scn_size[0], scn_size[1]), dim_t(scn_definition[0], scn_definition[1]));

    int nb;

    // Lights
    typedef std::map<std::string, std::function<Lights::Light* (TraceClient&, Network::Consumer&)>> light_types_t;
    light_types_t light_types;
    light_types["AMB"] = &TraceClient::construct_light<Lights::Ambiant>;
    light_types["DIF"] = &TraceClient::construct_light<Lights::Diffuse, double, double, double>;
    light_types["SPE"] = &TraceClient::construct_light<Lights::Specular, double, double, double>;
    consumer.read(nb);
    for (int i = 0; i < nb; ++i)
      {
	char type[3];
	consumer.read(type);
	auto it = light_types.find(std::string(type, sizeof(type)));
	if (it != light_types.end())
	  scene->add_light(it->second(*this, consumer));
      }

    // Objects
    typedef std::map< std::string, std::function<Objects::Object* (TraceClient&, Network::Consumer&)>> object_types_t;
    object_types_t object_types;
    object_types["PLA"] = &TraceClient::construct_object<Objects::Plane>;
    object_types["SPH"] = &TraceClient::construct_object<Objects::Sphere>;
    object_types["CYL"] = &TraceClient::construct_object<Objects::Cylinder>;
    object_types["CON"] = &TraceClient::construct_object<Objects::Cone, double>;
    consumer.read(nb);
    for (int i = 0; i < nb; ++i)
      {
	char type[3];
	consumer.read(type);
	auto it = object_types.find(std::string(type, sizeof(type)));
	if (it != object_types.end())
	  scene->add_object(it->second(*this, consumer));
      }
  }

  static const int nb_lines_chunk = 50;

  void* calculate_chunk(int ys, size_t& size)
  {
    static int* array = new int[scene->definition.width * nb_lines_chunk];
    for (int y = 0; y < nb_lines_chunk; ++y)
      for (int x = 0; x < scene->definition.width; ++x)
	{
	  Ray ray = scene->get_screen_ray(x, y + ys);
	  Intersection inter = scene->intersect(ray);
	  int color = 0;
	  if (inter)
	    color = scene->get_color(inter);
	  array[y * scene->definition.width + x] = color;
	}
    size = scene->definition.width * nb_lines_chunk * sizeof(int);
    return array;
  }

  Scene* scene;
  Network::Calculator< int > _calc;
};

#endif
