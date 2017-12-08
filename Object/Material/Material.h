//
// Created by liwen on 17-12-7.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

#include "../../Core/LightRay3.h"

class Material {
public:
    Material() = default;
    virtual ~Material() = default;
    virtual Color3 sample(const Ray3& ray,const LightRay3& light, const Vector3& position,const Vector3& normal)=0;
    float reflectivity;
    float refractivity;
    float n;
};


#endif //RAY_TRACER_MATERIAL_H
