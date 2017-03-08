#ifndef GLH_WORLD
#define GLH_WORLD

#include <set>
#include <vector>
#include <voxel_chunk.h>
#include <camera.h>
#include <drawable.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <future>

namespace glh
{

class World
{
protected:
  std::vector<std::vector<VoxelChunk>> chunks;
  std::queue<std::vector<int>> pairs;
  int chunk_size;
  int distance;
  int seed;
  int world_size;

public:
  World(int chunk_size, int distance, int world_size, int seed)
  : chunk_size(chunk_size), distance(distance), world_size(world_size), seed(seed)
  {
    chunks.resize(world_size);
    for (int i = 0; i < world_size; i++) {
      for (int j = 0; j < world_size; j++) {
        glh::VoxelChunk chunk { chunk_size };
        chunks[i].push_back(chunk);
      }
    }
  }

  void update(glh::Camera camera)
  {
    std::vector<int> position = camera.get_position();
    std::set<int> x_values;

    for (int d = position[0] / chunk_size - distance; d < position[0] / chunk_size + distance; d++)
    {
      x_values.insert(std::min(world_size - 1, std::max(0, d)));
    }

    std::set<int> z_values;

    for (int d = position[2] / chunk_size - distance; d < position[2] / chunk_size + distance; d++)
    {
      z_values.insert(std::min(world_size - 1, std::max(0, d)));
    }

    for (auto x: x_values) {
      for (auto z: z_values) {
        if (!chunks[x][z].is_generated() && !chunks[x][z].is_in_progress())
        {
          std::vector<int> v { x, z };
          pairs.push(v);
        }
      }
    }

    while(
      !pairs.empty() &&
      chunks[pairs.front()[0]][pairs.front()[1]].is_generated() &&
      !chunks[pairs.front()[0]][pairs.front()[1]].is_in_progress()
    )
    {
      pairs.pop();
    }

    if (!pairs.empty())
    {
      std::vector<int> gv = pairs.front();
      chunks[gv[0]][gv[1]].generate(seed, gv[0] * chunk_size, gv[1] * chunk_size);

      // auto f = std::async(std::launch::async, &VoxelChunk::generate, &chunks[gv[0]][gv[1]], seed, gv[0] * chunk_size, gv[1] * chunk_size);
    }
  }


  std::vector<glh::Drawable> get_drawables(glh::Camera camera)
  {
    std::vector<glh::Drawable> drawables;

    std::vector<int> position = camera.get_position();

    std::set<int> x_values;

    for (int d = position[0] / chunk_size - distance; d < position[0] / chunk_size + distance; d++)
    {
      x_values.insert(std::min(world_size - 1, std::max(0, d)));
    }

    std::set<int> z_values;

    for (int d = position[2] / chunk_size - distance; d < position[2] / chunk_size + distance; d++)
    {
      z_values.insert(std::min(world_size - 1, std::max(0, d)));
    }

    int max_x = 0;
    int max_z = 0;

    for (auto x: x_values) {
      if (x > max_x) max_x = x;
      for (auto z: z_values) {
        {
          if (z > max_z) max_z = z;
          if (chunks[x][z].is_generated())
          {
            drawables.push_back(chunks[x][z].get_drawable());
          }
        }
      }
    }

    return drawables;
  }
};

}

#endif
