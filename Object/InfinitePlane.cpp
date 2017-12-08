//
// Created by liwen on 12/8/17.
//

#include "InfinitePlane.h"

InfinitePlane::InfinitePlane(const Vector3& _refPoint, const Vector3& _normal) {
    refPoint = _refPoint;
    normal = _normal;
}

Vector3 InfinitePlane::getNormal(Vector3 point) {
    return normal;
}

Intersection InfinitePlane::isIntersected(const Ray3 &ray) {
    Intersection result;
    Vector3 v = ray.getOrigin() - refPoint;
    Vector3 d = ray.getDirection();
    float vn = v*normal;
    float dn = d*normal;
    if(dn!=0){
        float distance = - vn/dn;
        if(distance>1e-4){
            result.isHit=1;
            result.object = this;
            result.distance = distance;
            result.position = ray.getPoint(distance);
            result.normal = this->normal;
            return result;
        }
    }
}