#ifndef TORUS_H
#define TORUS_H

#include "indexmodel.h"
#include "movablemodel.h"
#include "texturemodel.h"
#include "lightablemodel.h"
#include "materialmodel.h"
#include "lightprogram.h"
#include "matma.h"
#include "texturecameraprogram.h"

class Sphere: public IndexModel, public MovableModel, public TextureModel, public LightableModel, public MaterialModel{
 public:
    Sphere(float init_velocity=10, float init_angle=0);
    void SetMaterialPrim(const Material& material) { material_prim_ = material; };
    void SetMaterialThree(const Material& material) { material_three_ = material; };
    void SetInitAngle(float angle){angle_= angle;}
    void SetVelocity(float velocity){velocity_= velocity;}
    void Initialize(int n, int m, float R);
    void Draw(const LightProgram & program) const;
    void Move(float delta_t);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
 private:
    int n_; // mesh parameter
    int m_; // mesh parameter

    float R; //big radius
    float r; //small radius

    Mat4 model_matrix_prim_;
    Mat3 normal_matrix_prim_;
    Material material_prim_;

    Mat4 model_matrix_three_;
    Mat3 normal_matrix_three_;
    Material material_three_;

    float angle_;
    float velocity_;
    bool animated_;
};

#endif // TORUS_H
