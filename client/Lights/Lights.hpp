#ifndef _LIGHTS_HPP_
#define _LIGHTS_HPP_

extern Scene* scene;

class Ambiant : public Light
{
public:
  Ambiant(int color, double intensity) : Light(color, intensity)
  {}
  int color_at(const Intersection& inter)
  {
    return inter.object->color & color;
  }
  double intensity_at(const Intersection&)
  {
    return intensity;
  }
};

class Diffuse : public Light
{
public:
  Diffuse(double x, double y, double z, int color, double intensity) : Light(color, intensity), pos(x, y, z)
  {}
  int color_at(const Intersection& inter)
  {
    return inter.object->color & color;
  }
  double intensity_at(const Intersection& inter)
  {
    Point point = inter.ray.point(inter.k);
    Vector to_obj(point.x - pos.x, point.y - pos.y, point.z - pos.z);
    Intersection shadow = scene->intersect(Ray(pos, to_obj));
    if (shadow.object != inter.object)
      return 0;
    Vector normal = inter.normal();
    Vector to_light(pos.x - point.x, pos.y - point.y, pos.z - point.z);
    double cos_angle = (normal * to_light) / (normal.norm() * to_light.norm());
    if (cos_angle < 0)
      cos_angle = 0;
    return (intensity * cos_angle);
  }
  Point pos;
};

class Specular : public Light
{
public:
  Specular(double x, double y, double z, int color, double intensity) : Light(color, intensity), pos(x, y, z)
  {}
  int color_at(const Intersection&)
  {
    return color;
  }
  // Assume that inter.object has a specularity of 1
  double intensity_at(const Intersection& inter)
  {
    Point point = inter.ray.point(inter.k);
    Vector to_obj(point.x - pos.x, point.y - pos.y, point.z - pos.z);
    Intersection shadow = scene->intersect(Ray(pos, to_obj));
    if (shadow.object != inter.object)
      return 0;
    Vector normal = inter.normal();
    Vector to_light(pos.x - point.x, pos.y - point.y, pos.z - point.z);
    normal = (1. / normal.norm()) * normal;
    to_light = (1. / to_light.norm()) * to_light;
    Vector r = (2. * (normal * to_light)) * normal - to_light;
    double cos_angle = -(r * inter.ray.dir) / (r.norm() * inter.ray.dir.norm());
    double k;
    if (cos_angle <= 0)
      k = 0;
    else
      {
	k = cos_angle;
	for (int i = 0; i < 5; ++i)
	  k *= cos_angle;
      }
    return (intensity * k);
  }
  Point pos;
};

#endif
