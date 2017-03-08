#include <drawable.h>

glh::Drawable::Drawable() {};
glh::Drawable::Drawable(GLuint shader, GLuint vao, int count)
: shader(shader), vao(vao), count(count)
{}
