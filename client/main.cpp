#include <set>
#include <array>
#include <tuple>
#include <map>
#include <math.h>
#include <iostream>
#include "Calculator.hpp"
#include "Consumer.hpp"

#include "utils.hpp"

// Polynomes

#include "Polynome.hpp"

// Vectors

#include "Vector.hpp"

// Matrix

#include "matrix.hpp"

// Ray

#include "Ray.hpp"

// Camera

#include "Camera.hpp"

// Object

#include "Object.hpp"

// Intersection

#include "Intersection.hpp"

// Light

#include "Light.hpp"

// Scene

#include "dimensions.hpp"

#include "Scene.hpp"

// Objects

#include "Objects.hpp"

// Lights

#include "Lights.hpp"

Scene* scene = 0;

#include "consumer_collect.hpp"

#include "expand_tuple.hpp"

#include "ConstructorCaller.hpp"

template < typename O, typename ... Types >
Object* construct_object(Consumer& consumer)
{
  std::tuple< Types... > properties = collect< Types... >(consumer);
  int color;
  consumer.read(color);
  matrix_t m;
  consumer.read(m);
  matrix_t inv_m;
  consumer.read(inv_m);
  return call_expand_tuple< Object* >(ConstructorCaller< Object, O >(), properties, color, m, inv_m);
}

template < typename L, typename ... Types >
Light* construct_light(Consumer& consumer)
{
  std::tuple< Types... > properties = collect< Types... >(consumer);
  int color;
  consumer.read(color);
  double intensity;
  consumer.read(intensity);
  return call_expand_tuple< Light* >(ConstructorCaller< Light, L >(), properties, color, intensity);
}

void initialize_scene(const char* data, size_t size)
{
  Consumer consumer(data, size);

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
  typedef std::map< std::string, Light* (*)(Consumer&) > light_types_t;
  light_types_t light_types;
  light_types["AMB"] = construct_light< Ambiant >;
  light_types["DIF"] = construct_light< Diffuse, double, double, double >;
  light_types["SPE"] = construct_light< Specular, double, double, double >;
  consumer.read(nb);
  for (int i = 0; i < nb; ++i)
    {
      char type[3];
      consumer.read(type);
      light_types_t::const_iterator it = light_types.find(std::string(type, sizeof(type)));
      if (it != light_types.end())
	scene->add_light(it->second(consumer));
    }

  // Objects
  typedef std::map< std::string, Object* (*)(Consumer&) > object_types_t;
  object_types_t object_types;
  object_types["PLA"] = construct_object< Plane >;
  object_types["SPH"] = construct_object< Sphere >;
  object_types["CYL"] = construct_object< Cylinder >;
  object_types["CON"] = construct_object< Cone, double >;
  consumer.read(nb);
  for (int i = 0; i < nb; ++i)
    {
      char type[3];
      consumer.read(type);
      object_types_t::const_iterator it = object_types.find(std::string(type, sizeof(type)));
      if (it != object_types.end())
	scene->add_object(it->second(consumer));
    }
}

static int nb_lines_chunk = 50;

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

#include <iostream>

int main()
{
  Calculator< int > calc("tcp://127.0.0.1:61385", calculate_chunk, initialize_scene);
  calc.start();
}
