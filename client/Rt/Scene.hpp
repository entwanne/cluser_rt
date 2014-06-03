#ifndef _RT_SCENE_HPP_
#define _RT_SCENE_HPP_

#include <set>

#include "Camera.hpp"
#include "dimensions.hpp"
#include "Objects/Object.hpp"
#include "Lights/Light.hpp"

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
      double imax = 1;
      std::set< std::pair< int, double > > colors;
      for (auto it = _lights.cbegin(); it != _lights.cend(); ++it)
	{
	  int color = (*it)->color_at(inter);
	  double intensity = (*it)->intensity_at(inter);
	  if (intensity > imax)
	    imax = intensity;
	  colors.insert(std::make_pair(color, intensity));
	}
      unsigned int rgb[3] = {0, 0, 0};
      for (auto it = colors.cbegin(); it != colors.cend(); ++it)
	{
	  unsigned char r, g, b;
	  r = it->first / (256 * 256);
	  g = (it->first / 256) % 256;
	  b = it->first % 256;
	  rgb[0] += r * it->second / imax;
	  rgb[1] += g * it->second / imax;
	  rgb[2] += b * it->second / imax;
	}
      unsigned int cmax = max(rgb[0], rgb[1], rgb[2]);
      if (cmax > 255)
	{
	  rgb[0] = (rgb[0] * 255) / cmax;
	  rgb[1] = (rgb[1] * 255) / cmax;
	  rgb[2] = (rgb[2] * 255) / cmax;
	}
      return rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
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
