#ifndef STARCONTOUR_H
#define STARCONTOUR_H

#include <GL/glew.h>

#include "program.h"

class StarContour{
 public:
    void Initialize();
    ~StarContour();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // STARCONTOUR_H
