//
// Created by liwen on 17-12-7.
//

#include "Tracer.h"

const float Tracer::epsilon = 1e-4;

Tracer::Tracer(vector<LightSource *>& _light, vector<Object*>& _obj, Camera *_cam): light_src_list(_light), obj_list(_obj), camera(_cam) {}

Intersection Tracer::ray_with_objs(Ray3 &ray, vector<Object*>& objs){
    Intersection res;
    for(Object * temp_obj:objs){
        Intersection temp = temp_obj->isIntersected(ray);
        if(temp.distance<res.distance){
            res = temp;
        }
    }
    return res;
}

Color3 Tracer::recusive(Ray3& ray, int times, Color3& result, float decay) {
    times--;
    Intersection sight_hit = ray_with_objs(ray, obj_list);
    if(sight_hit.isHit){
        for(LightSource* temp_light:light_src_list) {
            LightRay3 temp_light_ray = temp_light->traceLight(sight_hit.position);
            Intersection light_hit = ray_with_objs(temp_light_ray, obj_list);
            if (!light_hit.isHit || light_hit.object == temp_light) {
                Color3 color = sight_hit.object->material->sample(ray, temp_light_ray, sight_hit.position, sight_hit.normal);
                result += color;
                if(times>0){
                    if(sight_hit.object->material->reflectivity>0) {
                        Ray3 reflect(sight_hit.position, ray.direction + 2 * ray.direction.project(sight_hit.normal));
                        recusive(reflect, times, result, sight_hit.object->material->reflectivity);
                    }
                    if(sight_hit.object->material->refractivity>0){
                        Vector3 proj = ray.direction.project(sight_hit.normal);
                        Vector3 parallel = ray.direction + proj;
                        float sin_theta1 = parallel.getLength();
                        float sin_theta2 = sin_theta1/sight_hit.object->material->n;
                        float tan_theta2 = sin_theta2/sqrt(1-sin_theta2*sin_theta2);
                        Ray3 refract(sight_hit.position,sight_hit.normal+parallel.normalize()*tan_theta2);
                        recusive(refract, times, result, sight_hit.object->material->reflectivity);
                    }
                }
            }
        }
    }
}

void Tracer::Scan(int times) {
    bool working = true;
    while(working){
        Ray3 temp_sight_ray = camera->generateRay(working); // emit
        Color3 result = Color3(0,0,0);
        recusive(temp_sight_ray,times,result,1);
        camera->recieveColor(result); // receive
    }
}