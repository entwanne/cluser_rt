#include "Object.hpp"
#include "../Scene.hpp"

using namespace Rt::Objects;

Object::Object(int texture_id, const matrix_t& matrix_, const matrix_t& inv_matrix_, Scene* scene_): texture(scene_->get_texture(texture_id)), matrix(matrix_), inv_matrix(inv_matrix_), normal_matrix(transpose(inv_matrix_)), scene(scene_)
{}
