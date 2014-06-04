#ifndef _RT_SCENE_HPP_
#define _RT_SCENE_HPP_

#include <set>

#include "Camera.hpp"
#include "dimensions.hpp"
#include "Objects/Object.hpp"
#include "Lights/Light.hpp"
#include "Color.hpp"

namespace Rt
{

  class Scene
  {
  public:
    Scene(const Camera& cam_, const dim_t& size_, const dim_t& definition_): cam(cam_), size(size_), definition(definition_)
    {}
    void add_object(Objects::Object* obj)
    {
      _objects.insert(obj);
    }
    void add_light(Lights::Light* light)
    {
      _lights.insert(light);
    }
    Intersection intersect(const Ray& ray) const
    {
      Intersection inter(ray);
      for (auto it = _objects.cbegin(); it != _objects.cend(); ++it)
	{
	  double k = (*it)->intersect(ray);
	  if (LESS_AND_POSITIVE(k, inter.k))
	    {
	      inter.k = k;
	      inter.object = *it;
	    }
	}
      return inter;
    }
    int get_color(const Intersection& inter) const
    {
      Color color(0);
      for (auto it = _lights.cbegin(); it != _lights.cend(); ++it)
	color += Color((*it)->color_at(inter)) * (*it)->intensity_at(inter);
      return color.to_int();
    }
    Ray get_screen_ray(int s_x, int s_y)
    {
      double x = (((double) s_x / definition.width) - 0.5) * size.width;
      double z = (((double) s_y / definition.height) - 0.5) * size.height;
      return Ray(cam.pos, Vector(x, cam.dist, -z));
    }
    Camera cam;
    dim_t size;
    dim_t definition;
  protected:
    std::set< Objects::Object* > _objects;
    std::set< Lights::Light* > _lights;
  };

}

#endif
