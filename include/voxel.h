#ifndef GLH_VOXEL
#define GLH_VOXEL

#include <GL/glew.h>
#include <vector>

namespace glh
{

class Voxel
{
protected:
  std::vector<GLfloat> vertices;
  std::vector<GLfloat> colors;
  std::vector<GLfloat> occlusion;
  std::vector<unsigned int> indexes;

  int x, y, z;
  float color_r, color_g, color_b;

public:

  void set_position(int, int, int);
  void set_color(float, float, float);
  void occlude(std::vector<Voxel>);
  std::vector<int> get_position();
  std::vector<GLfloat> get_vertices_data();
  std::vector<GLfloat> get_colors_data();
  std::vector<GLfloat> get_normals_data();
  std::vector<GLfloat> get_ambient_occlusion_data();
  std::vector<GLfloat> get_interleaved_data();
  std::vector<unsigned int> get_indexes();

  std::vector<GLfloat> get_top_face_vertices();
  std::vector<GLfloat> get_bottom_face_vertices();
  std::vector<GLfloat> get_right_face_vertices();
  std::vector<GLfloat> get_left_face_vertices();
  std::vector<GLfloat> get_front_face_vertices();
  std::vector<GLfloat> get_back_face_vertices();

};

}

#endif
