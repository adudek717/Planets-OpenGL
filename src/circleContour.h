#ifndef CIRCLECONTOUR_H
#define CIRCLECONTOUR_H

#include <GL/glew.h>

#include "program.h"

class CircleContour{
 public:
    void Initialize();
    ~CircleContour();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // CIRCLECONTOUR_H
