//
// Created by liwen on 17-12-7.
//

#ifndef RAY_TRACER_TRACER_H
#define RAY_TRACER_TRACER_H

#include "Object/LightSource/LightSource.h"
#include "Camera.h"
#include "Canvas.h"
#include <vector>

using namespace std;

class Tracer {
private:
    vector<LightSource*> light_src_list;
    vector<Object*> obj_list;
    Camera* camera;

    Color3 recursive(Ray3* ray, int times, double& distance);
    Ray3 trace_in_object_light(Ray3* ray, Intersection& sight_hit, double& distance);
    Color3 recursive_cuda(Ray3* ray, int times, double decay, double& distance);
    static Intersection ray_with_objs(Ray3& ray, vector<Object*>& objs);
public:
    Tracer() = default;
    Tracer(vector<LightSource*>& _light, vector<Object*>& _obj, Camera* _cam);
    ~Tracer() = default;

    void Scan(int times);
    void Scan_cuda(int times);
    void render(string);
};


#endif //RAY_TRACER_TRACER_H
