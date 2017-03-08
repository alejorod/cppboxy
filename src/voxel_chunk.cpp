#include <voxel_chunk.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <drawer.h>
#include <PerlinNoise.h>

glh::VoxelChunk::VoxelChunk(int size)
: size(size), generated(false), in_progress(false), has_drawable(false)
{}

glh::Drawable glh::VoxelChunk::get_drawable()
{
  if (!has_drawable)
  {
    has_drawable = true;
    glh::InterleavedBufferData data = get_buffer_data();
    GLuint vao  = glh::BufferManager::create(data);
    drawable = glh::Drawer::create_drawable(vao, data.indexes.size());
  }


  return drawable;
}

void glh::VoxelChunk::generate(unsigned int seed, int x, int z)
{
  in_progress = true;
  PerlinNoise pn { seed };

  voxels.resize(size);

  for (int xi = 0; xi < size; xi++) {
    voxels[xi].resize(size);

    for (int zi = 0; zi < size; zi++) {

      double _x = (double) (xi + x) / (double) (100);
      double _z = (double) (zi + z) / (double) (100);

      double n = std::abs(pn.noise(_x, _z, 0))
                + 0.5 * std::abs(pn.noise(2 * _x, 2 * _z, 0))
                + 0.25 * std::abs(pn.noise(4 * _x, 2 * _z, 0));

      voxels[xi][zi].set_position(xi + x, (int) floor(n * 50), zi + z);
      voxels[xi][zi].set_color(0.0f, 1.0f, 0.0f);
    }
  }

  int min_x;
  int max_x;
  int min_z;
  int max_z;

  std::set<int> xs;
  std::set<int> zs;

  for (int x = 0; x < voxels.size(); x++) {
    min_x = std::max(0, x - 1);
    max_x = std::min(x + 1, (int) voxels.size() - 1);

    xs = {x, min_x, max_x};
    for (int z = 0; z < voxels[x].size(); z++) {
      min_z = std::max(0, z - 1);
      max_z = std::min(z + 1, (int) voxels[x].size() - 1);
      zs = {z, min_z, max_z};

      std::vector<Voxel> a_voxels;

      for (auto xi: xs) {
        for (auto zi: zs) {
          a_voxels.push_back(voxels[xi][zi]);
        }
      }

      voxels[x][z].occlude(a_voxels);
    }
  }

  generated = true;
  in_progress = false;
}

bool glh::VoxelChunk::is_generated()
{
  return generated;
}

bool glh::VoxelChunk::is_in_progress()
{
  return in_progress;
}

glh::InterleavedBufferData glh::VoxelChunk::get_buffer_data()
{
  std::vector<GLfloat> data;
  std::vector<unsigned int> indexes;
  std::vector<GLfloat> voxel_data;
  std::vector<unsigned int> voxel_indexes;

  int last_index = 0;

  for (int x = 0; x < voxels.size(); x++) {
    for (int z = 0; z < voxels[x].size(); z++) {
      last_index = data.size() / 11;
      voxel_data = voxels[x][z].get_interleaved_data();
      voxel_indexes = voxels[x][z].get_indexes();

      data.insert(data.end(), voxel_data.begin(), voxel_data.end());

      for (int i = 0; i < voxel_indexes.size(); i++) {
        indexes.push_back(last_index + voxel_indexes[i]);
      }
    }
  }

  std::cout << indexes.size() << std::endl;

  return { data, indexes, 11 };
}
