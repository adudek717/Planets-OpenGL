#include "sphere.h"
#include "vertices.h"

#include <iostream>
#include <cmath>

Sphere::Sphere(float init_velocity, float init_angle){
    velocity_ = init_velocity;
    angle_ = init_angle;
    animated_ = true;
}


void Sphere::Move(float delta_t){
    if (!animated_) return;
    angle_ += delta_t * velocity_;
    if(angle_>360) angle_ -= 360;
    if(angle_<-360) angle_ += 360;
    model_matrix_.SetUnitMatrix();
    model_matrix_.RotateAboutY(angle_);
    normal_matrix_.SetUnitMatrix();
    normal_matrix_.RotateAboutY(-angle_);

    model_matrix_prim_.SetUnitMatrix();
    model_matrix_prim_.Scale(0.25, 0.25, 0.25);
    model_matrix_prim_.RotateAboutY(3 * angle_);
    model_matrix_prim_.Translate(4, 0, 0);
    model_matrix_prim_.RotateAboutY(5 * angle_);
    normal_matrix_prim_.SetUnitMatrix();
    normal_matrix_prim_.RotateAboutY(-5 * angle_);
    normal_matrix_prim_.RotateAboutY(-3 * angle_);
    normal_matrix_prim_.Scale(4, 4, 4);

    model_matrix_three_.SetUnitMatrix();
    model_matrix_three_.Scale(0.1, 0.1, 0.1);
    model_matrix_three_.RotateAboutY(1 * angle_);
    model_matrix_three_.Translate(1, 0, 0);
    model_matrix_three_.RotateAboutY(2 * angle_);
    model_matrix_three_.Translate(4, 0, 0);
    model_matrix_three_.RotateAboutY(5 * angle_);
    normal_matrix_three_.SetUnitMatrix();
    normal_matrix_three_.RotateAboutY(-5 * angle_);
    normal_matrix_three_.RotateAboutY(-2 * angle_);
    normal_matrix_three_.RotateAboutY(-1 * angle_);
    normal_matrix_three_.Scale(10, 10, 10);
}



void Sphere::SpeedUp(){
    velocity_ *= 1.09544511501;
}

void Sphere::SlowDown(){
    velocity_ /= 1.09544511501;
}

void Sphere::ToggleAnimated(){
    animated_ = ! animated_;
}

void Sphere::Initialize(int n, int m, float R){
    n_=n;
    m_=m;
    NormalTextureVertex * vertices=new NormalTextureVertex[(m_ + 1)*(n_ + 1)];
    int i,j;
    for (i=0;i<=n_;i++) {
      float phi=M_PI/(float)n_*i - M_PI / 2;
      for (j=0;j<=m_;j++){
        float theta=2*M_PI/(float)m_*j;
        vertices[i*(m_ + 1)+j].position[0]=(R*sin(theta) * cos(phi));
        vertices[i*(m_ + 1)+j].position[1]=R*sin(phi);
        vertices[i*(m_ + 1)+j].position[2]=(R*cos(theta) * cos(phi));
        vertices[i*(m_ + 1)+j].position[3]=1.0f;
        vertices[i*(m_ + 1)+j].texture[0]=(float)j/(float)m_;
        vertices[i*(m_ + 1)+j].texture[1]=(float)i/(float)n_;
        vertices[i*(m_ + 1)+j].normal[0]=(sin(theta) * cos(phi));
        vertices[i*(m_ + 1)+j].normal[1]=sin(phi);
        vertices[i*(m_ + 1)+j].normal[2]=(cos(theta) * cos(phi));
      }
    }



    GLuint * indices=new GLuint[2*n_*(m_ + 1)];

    unsigned int k=0;

    for(i=0; i<=n_ - 1; i++){
      for(j=0; j<=m_; j++){
        indices[2*(i*(m_ + 1)+j)]=k;
        indices[2*(i*(m_ + 1)+j)+1]=k+m_+1;
        k++;
      }
    }

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);


    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER,
            (m_+1)*(n_+1)*sizeof(vertices[0]),
            vertices,
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)sizeof(vertices[0].position));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
        (GLvoid*)(sizeof(vertices[0].position) + sizeof(vertices[0].texture)));
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 (m_+1)*n_*2*sizeof(GLuint),
                 indices,
                 GL_STATIC_DRAW
                 );
    delete [] vertices;
    delete [] indices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Sphere::Draw(const LightProgram &program) const{

    glBindVertexArray(vao_);
    glUseProgram(program);


    glActiveTexture(texture_unit_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    program.SetModelMatrix(model_matrix_);
    program.SetMaterial(material_);
    program.SetNormalMatrix(normal_matrix_);
    for (int i=0;i<n_;i++){
      glDrawElements(GL_TRIANGLE_STRIP,
                     2*(m_ + 1),
                     GL_UNSIGNED_INT,
                     (GLvoid*)(sizeof(GLuint) * 2 * i * (m_ + 1))
                     );
    }

    glBindTexture(GL_TEXTURE_2D, texture_prim_);
    program.SetModelMatrix(model_matrix_prim_);
    program.SetMaterial(material_prim_);
    program.SetNormalMatrix(normal_matrix_prim_);
    for (int i = 0; i < n_; i++) {
        glDrawElements(GL_TRIANGLE_STRIP,
            2 * (m_ + 1),
            GL_UNSIGNED_INT,
            (GLvoid*)(sizeof(GLuint) * 2 * i * (m_ + 1))
        );
    }

    glBindTexture(GL_TEXTURE_2D, texture_three_);
    program.SetModelMatrix(model_matrix_three_);
    program.SetMaterial(material_three_);
    program.SetNormalMatrix(normal_matrix_three_);
    for (int i = 0; i < n_; i++) {
        glDrawElements(GL_TRIANGLE_STRIP,
            2 * (m_ + 1),
            GL_UNSIGNED_INT,
            (GLvoid*)(sizeof(GLuint) * 2 * i * (m_ + 1))
        );
    }
    glDisable(GL_CULL_FACE);

    glBindVertexArray(0);
    glUseProgram(0);
}
