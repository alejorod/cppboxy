#ifndef GLH_SHADER_MANAGER
#define GLH_SHADER_MANAGER

#include <string>
#include <GL/glew.h>

namespace glh
{

class ShaderManager
{
public:
  static GLuint load(std::string, std::string);
  static void use(GLuint);
};

}

#endif
