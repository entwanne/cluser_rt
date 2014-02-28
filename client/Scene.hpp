#ifndef _SCENE_HPP_
#define _SCENE_HPP_

class Scene
{
public:
  Scene(const Camera& cam_, const dim_t& size_, const dim_t& definition_): cam(cam_), size(size_), definition(definition_)
  {}
  void add_object(Object* obj)
  {
    _objects.insert(obj);
  }
  void add_light(Light* light)
  {
    _lights.insert(light);
  }
  Intersection intersect(const Ray& ray) const
  {
    Intersection inter(ray);
    std::set< Object* >::const_iterator it;
    for (it = _objects.begin(); it != _objects.end(); ++it)
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
    std::set< Light* >::const_iterator it;
    std::set< std::pair< int, double > > colors;
    for (it = _lights.cbegin(); it != _lights.cend(); ++it)
      {
	int color = (*it)->color_at(inter);
	double intensity = (*it)->intensity_at(inter);
	if (intensity > imax)
	  imax = intensity;
	colors.insert(std::make_pair(color, intensity));
      }
    unsigned int rgb[3] = {0, 0, 0};
    std::set< std::pair< int, double > >::const_iterator itc;
    for (itc = colors.cbegin(); itc != colors.cend(); ++itc)
      {
	unsigned char r, g, b;
	r = itc->first / (256 * 256);
	g = (itc->first / 256) % 256;
	b = itc->first % 256;
	rgb[0] += r * itc->second / imax;
	rgb[1] += g * itc->second / imax;
	rgb[2] += b * itc->second / imax;
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
  std::set< Object* > _objects;
  std::set< Light* > _lights;
};

#endif
