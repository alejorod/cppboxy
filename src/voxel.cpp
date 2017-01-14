#include <voxel.h>
#include <primitives.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <cmath>
#include <limits>

bool compare_floats(float a, float b) {
  float diff = std::fabs(a - b);
  return (diff <= std::numeric_limits<float>::epsilon());
}

void glh::Voxel::set_position(int cx, int cy, int cz)
{
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

bool glh::Voxel::similar_coords(int cx, int cy, int cz)
{
  int similar = 0;

  if (y == cy) return true;

  if (x == cx) { similar++; }
  if (y == cy) { similar++; }
  if (z == cz) { similar++; }

  return similar >= 2;
}

void glh::Voxel::occlude(std::vector<Voxel> adjacent_voxels)
{
  std::vector<GLfloat> temp_vertices;
  std::vector<int> touching_vertices_count;
  touching_vertices_count.resize(vertices.size() / 3);
  std::fill(touching_vertices_count.begin(), touching_vertices_count.end(), 0);

  for (int i = 0; i < adjacent_voxels.size(); i++) {
    if (adjacent_voxels[i].similar_coords(x, y, z))
    {
      continue;
    }

    temp_vertices = adjacent_voxels[i].get_vertices_data();

    for (int t = 0; t < touching_vertices_count.size(); t++) {
      float vx = vertices[t * 3];
      float vy = vertices[(t * 3) + 1];
      float vz = vertices[(t * 3) + 2];

      for (int v = 0; v < temp_vertices.size(); v += 3)
      {
        if (compare_floats(temp_vertices[v], vx) && compare_floats(temp_vertices[v + 1], vy) && compare_floats(temp_vertices[v + 2], vz))
        {
          touching_vertices_count[t]++;
          break;
        }
      }
    }
  }

  occlusion.resize(touching_vertices_count.size());

  for (int tv = 0; tv < touching_vertices_count.size(); tv++)
  {
    if (touching_vertices_count[tv])
    {
      occlusion[tv] = std::min(0.15f * (float) (touching_vertices_count[tv] / 3.0f), 0.8f);
    } else {
      occlusion[tv] = 0;
    }
  }
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
  int i = 0;
  std::vector<GLfloat> interleaved;

  for (i = 0; i < vertices.size(); i += 3)
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
  }

  return interleaved;
}

std::vector<GLfloat> get_normals_data()
{
  return glh::primitives::cube_normals;
}

std::vector<unsigned int> glh::Voxel::get_indexes()
{
  return glh::primitives::cube_indexes;
}

std::vector<GLfloat> glh::Voxel::get_top_face_vertices()
{
  return { glh::primitives::cube.begin(), glh::primitives::cube.begin() + 3 * 4 };
}

std::vector<GLfloat> glh::Voxel::get_left_face_vertices()
{
  return { glh::primitives::cube.begin() + 3 * 4, glh::primitives::cube.begin() + 3 * 8 };
}

std::vector<GLfloat> glh::Voxel::get_right_face_vertices()
{
  return { glh::primitives::cube.begin() + 3 * 8, glh::primitives::cube.begin() + 3 * 12 };
}

std::vector<GLfloat> glh::Voxel::get_front_face_vertices()
{
  return { glh::primitives::cube.begin() + 3 * 12, glh::primitives::cube.begin() + 3 * 16 };
}

std::vector<GLfloat> glh::Voxel::get_back_face_vertices()
{
  return { glh::primitives::cube.begin() + 3 * 16, glh::primitives::cube.begin() + 3 * 20 };
}

std::vector<GLfloat> glh::Voxel::get_bottom_face_vertices()
{
  return { glh::primitives::cube.begin() + 3 * 20, glh::primitives::cube.begin() + 3 * 24 };
}
