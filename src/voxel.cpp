#include <voxel.h>
#include <primitives.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <cmath>
#include <limits>
#include <PerlinNoise.h>

bool compare_floats(float a, float b) {
  float diff = std::fabs(a - b);
  return (diff <= std::numeric_limits<float>::epsilon());
}

void glh::Voxel::set_position(int cx, int cy, int cz)
{
  indexes = glh::primitives::cube_indexes;
  x = cx;
  y = cy;
  z = cz;

  vertices.resize(glh::primitives::cube.size());

  for (int i = 0; i < vertices.size(); i += 3)
  {
    glm::vec4 vertice = glm::translate(glm::vec3(x, y, z)) * glm::vec4(glh::primitives::cube[i], glh::primitives::cube[i + 1], glh::primitives::cube[i + 2], 1.0f);
    vertices[i] = vertice[0];
    vertices[i + 1] = vertice[1];
    vertices[i + 2] = vertice[2];
  }
}

void glh::Voxel::set_color(float r, float g, float b)
{
  color_r = r;
  color_g = g;
  color_b = b;

  colors.resize(glh::primitives::cube.size());

  for (int i = 0; i < colors.size(); i += 3)
  {
    colors[i] = color_r;
    colors[i + 1] = color_g;
    colors[i + 2] = color_b;
  }
}

std::vector<int> glh::Voxel::get_position()
{
  return { x, y, z };
}

bool is_voxel_adjacent(float x, float y, float z, glh::Voxel voxel)
{
  std::vector<GLfloat> vs = voxel.get_vertices_data();

  for (int i = 0; i < vs.size(); i += 3)
  {
    if (compare_floats(x, vs[i]) && compare_floats(y, vs[i + 1]) && compare_floats(z, vs[i + 2]))
    {
      return true;
    }
  }

  return false;
}

float calculate_vertice_occlusion(int side1, int side2, int corner) {
  float ao;

  if (side1 && side2)
  {
    ao = 1.0f;
  }

  if (!side1 && !side2 && !corner)
  {
    ao = 0.0f;
  } else {
    ao = 1.0f / 3.0f;
  }

  // ao = ((float) side1 + side2 + corner) / 3.0f;

  // return ao;
  return ao * 0.35f;
}

template<typename F, typename G>
std::vector<GLfloat> calculate_face_occlusion(std::vector<GLfloat> vertices, std::vector<glh::Voxel> voxels, F is_valid, G is_corner)
{
  std::vector<glh::Voxel> valid_voxels;
  for (glh::Voxel v: voxels) {
    if (is_valid(v)) {
      valid_voxels.push_back(v);
    }
  }

  std::vector<GLfloat> face_occlusion;

  for (int i = 0; i < vertices.size(); i += 3)
  {
    std::vector<glh::Voxel> adjacent_voxels;
    adjacent_voxels.clear();
    for (glh::Voxel v : valid_voxels)
    {
      if (is_voxel_adjacent(vertices[i], vertices[i + 1], vertices[i + 2], v))
      {
        adjacent_voxels.push_back(v);
      }
    }

    if (adjacent_voxels.size() == 0)
    {
      face_occlusion.push_back(calculate_vertice_occlusion(0, 0, 0));
    } else if (adjacent_voxels.size() == 3) {
      face_occlusion.push_back(calculate_vertice_occlusion(1, 1, 1));
    } else if (adjacent_voxels.size() == 2) {
      bool has_corner = is_corner(adjacent_voxels[0]) || is_corner(adjacent_voxels[1]);
      if (has_corner)
      {
        face_occlusion.push_back(calculate_vertice_occlusion(1, 0, 1));
      } else {
        face_occlusion.push_back(calculate_vertice_occlusion(1, 1, 0));
      }
    } else if (is_corner(adjacent_voxels[0])) {
      face_occlusion.push_back(calculate_vertice_occlusion(0, 0, 1));
    } else {
      face_occlusion.push_back(calculate_vertice_occlusion(1, 0, 0));
    }
  }

  return face_occlusion;
}

void glh::Voxel::occlude(std::vector<glh::Voxel> adjacent_voxels)
{
  occlusion.clear();
  occlusion.resize(0);

  // for (int i = 0; i < 6 * 4; i++) {
  //   occlusion.push_back(0);
  // }
  //
  indexes = glh::primitives::cube_indexes;

  std::vector<GLfloat> face_occlusion;
  std::vector<GLfloat> top_vertices = get_top_face_vertices();
  std::vector<GLfloat> left_vertices = get_left_face_vertices();
  std::vector<GLfloat> right_vertices = get_right_face_vertices();
  std::vector<GLfloat> front_vertices = get_front_face_vertices();
  std::vector<GLfloat> back_vertices = get_back_face_vertices();
  std::vector<GLfloat> bottom_vertices = get_bottom_face_vertices();

  face_occlusion = calculate_face_occlusion(
    top_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (y - p[1]) == -1;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x != p[0] && z != p[2]);
    }
  );

  // 0 3 1 2
  float a00 = face_occlusion[0];
  float a01 = face_occlusion[3];
  float a10 = face_occlusion[1];
  float a11 = face_occlusion[2];

  if (a00 + a11 > a01 + a10)
  {
    indexes[0] = 3;
    indexes[1] = 1;
    indexes[2] = 2;

    indexes[3] = 3;
    indexes[4] = 0;
    indexes[5] = 1;
  }

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());

  face_occlusion = calculate_face_occlusion(
    left_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x - p[0]) == 1;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (y != p[1] && z != p[2]);
    }
  );

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());

  // for (int i = 0; i < 4 * 2; i++) {
  //   occlusion.push_back(0);
  // }

  face_occlusion = calculate_face_occlusion(
    right_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x - p[0]) == -1;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (y != p[1] && z != p[2]);
    }
  );

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());

  face_occlusion = calculate_face_occlusion(
    front_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (z - p[2]) < 0;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x != p[0] && y != p[1]);
    }
  );
  //
  // 15 14 13
  // 15 13 12

  indexes[0 + 6 * 3] = 15;
  indexes[1 + 6 * 3] = 14;
  indexes[2 + 6 * 3] = 13;

  indexes[3 + 6 * 3] = 15;
  indexes[4 + 6 * 3] = 13;
  indexes[5 + 6 * 3] = 12;

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());

  // for (int i = 0; i < 4 * 2; i++) {
  //   occlusion.push_back(0);
  // }

  face_occlusion = calculate_face_occlusion(
    back_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (z - p[2]) == 1;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x != p[0] && y != p[1]);
    }
  );

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());

  face_occlusion = calculate_face_occlusion(
    bottom_vertices, adjacent_voxels,
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (y - p[1]) == 1;
    },
    [&] (Voxel v) -> bool {
      std::vector<int> p = v.get_position();
      return (x != p[0] && z != p[2]);
    }
  );

  occlusion.insert(occlusion.end(), face_occlusion.begin(), face_occlusion.end());
}

std::vector<GLfloat> glh::Voxel::get_vertices_data()
{
  return vertices;
}

std::vector<GLfloat> glh::Voxel::get_colors_data()
{
  return colors;
}

std::vector<GLfloat> glh::Voxel::get_ambient_occlusion_data()
{
  return occlusion;
}

std::vector<GLfloat> glh::Voxel::get_interleaved_data()
{
  std::vector<GLfloat> interleaved;


  PerlinNoise pn;
  int size = 100;
  int w_size = 100;


  for (int i = 0; i < vertices.size(); i += 3)
  {
    interleaved.push_back(vertices[i]);
    interleaved.push_back(vertices[i + 1]);
    interleaved.push_back(vertices[i + 2]);

    interleaved.push_back(colors[i]);
    interleaved.push_back(colors[i + 1]);
    interleaved.push_back(colors[i + 2]);

    interleaved.push_back(glh::primitives::cube_normals[i]);
    interleaved.push_back(glh::primitives::cube_normals[i + 1]);
    interleaved.push_back(glh::primitives::cube_normals[i + 2]);

    interleaved.push_back(occlusion[i / 3]);

    double x = (double) vertices[i] / (double) (size);
    double y = (double) vertices[i + 1] / (double) (size);

    double n = pn.noise(x, y, 0)
              + 0.25 * pn.noise(2 * x, 2 * y, 0);

    interleaved.push_back(n - floor(n));
  }

  return interleaved;
}

std::vector<GLfloat> get_normals_data()
{
  return glh::primitives::cube_normals;
}

std::vector<unsigned int> glh::Voxel::get_indexes()
{
  return indexes;
}

std::vector<GLfloat> glh::Voxel::get_top_face_vertices()
{
  return { vertices.begin(), vertices.begin() + 3 * 4 };
}

std::vector<GLfloat> glh::Voxel::get_left_face_vertices()
{
  return { vertices.begin() + 3 * 4, vertices.begin() + 3 * 8 };
}

std::vector<GLfloat> glh::Voxel::get_right_face_vertices()
{
  return { vertices.begin() + 3 * 8, vertices.begin() + 3 * 12 };
}

std::vector<GLfloat> glh::Voxel::get_front_face_vertices()
{
  return { vertices.begin() + 3 * 12, vertices.begin() + 3 * 16 };
}

std::vector<GLfloat> glh::Voxel::get_back_face_vertices()
{
  return { vertices.begin() + 3 * 16, vertices.begin() + 3 * 20 };
}

std::vector<GLfloat> glh::Voxel::get_bottom_face_vertices()
{
  return { vertices.begin() + 3 * 20, vertices.begin() + 3 * 24 };
}
