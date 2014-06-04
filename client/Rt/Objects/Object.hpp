#ifndef _RT_OBJECTS_OBJECT_HPP_
#define _RT_OBJECTS_OBJECT_HPP_

#include "../Textures/Texture.hpp"
#include "../matrix.hpp"
#include "../Vector.hpp"
#include "../Ray.hpp"

namespace Rt
{
  class Scene;

  namespace Objects
  {

    class Object
    {
    public:
Object(int texture_id, const matrix_t& matrix_, const matrix_t& inv_matrix_, Scene* scene_);
      virtual double intersect(const Ray&) const = 0;
      // Unit vector of normal in simple coords
      virtual Vector normal(const Point&) const = 0;
      inline int color_at(int x, int y) const
      {
	return texture->color_at(x, y);
      }
      Textures::Texture* texture;
      matrix_t matrix, inv_matrix, normal_matrix;

      Scene* scene;
    };

  }
}

#endif
