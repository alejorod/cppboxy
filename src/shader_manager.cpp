#include <shader_manager.h>
#include <fstream>
#include <iostream>
#include <vector>

GLuint glh::ShaderManager::load(std::string vertex_path, std::string fragment_path)
{
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertex_code;
  std::string fragment_code;

  std::ifstream vertex_stream(vertex_path.c_str(), std::ifstream::in);
  std::ifstream fragment_stream(fragment_path.c_str(), std::ifstream::in);

  if (vertex_stream.is_open())
  {
    std::string line = "";
    while(std::getline(vertex_stream, line))
    {
      vertex_code += "\n" + line;
    }
    vertex_stream.close();
  }

  if (fragment_stream.is_open())
  {
    std::string line = "";
    while(std::getline(fragment_stream, line))
    {
      fragment_code += "\n" + line;
    }
    fragment_stream.close();
  }

  GLint result = GL_FALSE;
	int info_log_length;

  std::cout << "Compiling shader: " << vertex_path << std::endl;

  const char* vertex_source = vertex_code.c_str();
  glShaderSource(vertex_id, 1, &vertex_source, NULL);
  glCompileShader(vertex_id);

  glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> vertex_error(info_log_length + 1);
		glGetShaderInfoLog(vertex_id, info_log_length, NULL, &vertex_error[0]);
    for (auto i: vertex_error)
      std::cout << i;
	} else {
    std::cout << "DONE!" << std::endl;
  }

  std::cout << "Compiling shader: " << fragment_path << std::endl;

  const char* fragment_source = fragment_code.c_str();
  glShaderSource(fragment_id, 1, &fragment_source, NULL);
  glCompileShader(fragment_id);

  glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> vertex_error(info_log_length + 1);
		glGetShaderInfoLog(fragment_id, info_log_length, NULL, &vertex_error[0]);
    for (auto i: vertex_error)
      std::cout << i;
	} else {
    std::cout << "DONE!" << std::endl;
  }

  std::cout << "Linking Program" << std::endl;

  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vertex_id);
  glAttachShader(program_id, fragment_id);
  glLinkProgram(program_id);

  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> program_error_message(info_log_length+1);
		glGetProgramInfoLog(program_id, info_log_length, NULL, &program_error_message[0]);
    for (auto i: program_error_message)
      std::cout << i;
	} else {
    std::cout << "DONE!" << std::endl;
  }

  glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

  return program_id;
}

void glh::ShaderManager::use(GLuint shader_id)
{
  glUseProgram(shader_id);
}
