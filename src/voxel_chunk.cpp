#include <voxel_chunk.h>
#include <algorithm>
#include <iostream>

void glh::VoxelChunk::set_chunk_data(std::vector<std::vector<int>> data)
{
  voxels.resize(data.size());

  for (int x = 0; x < data.size(); x++) {
    voxels[x].resize(data[x].size());
    for (int z = 0; z < data[x].size(); z++) {
      voxels[x][z].set_position(x, data[x][z], z);
      voxels[x][z].set_color(0.0f, 1.0f, 0.0f);
    }
  }

  int min_x;
  int max_x;
  int min_z;
  int max_z;

  for (int x = 0; x < voxels.size(); x++) {
    min_x = std::max(0, x - 1);
    max_x = std::min(x + 1, (int) voxels.size() - 1);
    for (int z = 0; z < voxels[x].size(); z++) {
      min_z = std::max(0, z - 1);
      max_z = std::min(z + 1, (int) voxels[x].size() - 1);

      std::vector<Voxel> a_voxels {
        voxels[x][min_z],
        voxels[x][max_z],
        voxels[min_x][z],
        voxels[max_x][z],
        voxels[min_x][min_z],
        voxels[min_x][max_z],
        voxels[max_x][min_z],
        voxels[max_x][max_z],
      };

      voxels[x][z].occlude(a_voxels);
    }
  }
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
      last_index = data.size() / 10;
      voxel_data = voxels[x][z].get_interleaved_data();
      voxel_indexes = voxels[x][z].get_indexes();

      data.insert(data.end(), voxel_data.begin(), voxel_data.end());

      for (int i = 0; i < voxel_indexes.size(); i++) {
        indexes.push_back(last_index + voxel_indexes[i]);
      }
    }
  }

  return { data, indexes, 10 };
}
