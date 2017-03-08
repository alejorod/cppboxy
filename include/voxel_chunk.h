#ifndef GLH_VOXEL_CHUNK
#define GLH_VOXEL_CHUNK

#include <voxel.h>
#include <buffer_manager.h>
#include <drawable.h>
#include <vector>

namespace glh
{

class VoxelChunk
{
protected:
  int size;
  std::vector<std::vector<Voxel>> voxels;
  glh::Drawable drawable;
  bool generated;
  bool in_progress;
  bool has_drawable;

public:
  VoxelChunk(int);
  bool is_generated();
  bool is_in_progress();
  void generate(unsigned int, int, int);
  Drawable get_drawable();

  void set_chunk_data(std::vector<std::vector<int>>, int, int);
  glh::InterleavedBufferData get_buffer_data();
};

}

#endif
