#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include <GL/glew.h>

class TextureModel{
public:
    void SetTextureUnit(GLuint t){texture_unit_=t;}
    void SetTexture(GLuint t){texture_ = t;}
    void SetTexturePrim(GLuint t) { texture_prim_ = t; }
    void SetTextureThree(GLuint t) { texture_three_ = t; }
protected:
    GLuint texture_unit_;
    GLuint texture_;
    GLuint texture_prim_;
    GLuint texture_three_;
};

#endif // TEXTUREMODEL_H
