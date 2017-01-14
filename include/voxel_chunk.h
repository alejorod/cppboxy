#ifndef GLH_VOXEL_CHUNK
#define GLH_VOXEL_CHUNK

#include <voxel.h>
#include <buffer_manager.h>
#include <vector>

namespace glh
{

class VoxelChunk
{
protected:
  std::vector<std::vector<Voxel>> voxels;

public:
  void set_chunk_data(std::vector<std::vector<int>>);
  glh::InterleavedBufferData get_buffer_data();
};

}

#endif
