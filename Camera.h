//
// Created by liwen on 17-12-7.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "Core/Ray3.h"
#include "Core/Vector2.h"
#include "Canvas.h"

class Camera{
public:
    // constructor and destructor
    ~Camera() = default;
    Camera(const Vector3& _eye,const Vector3& _front,const Vector3& _up,double angle_x,double angle_y);

    void setCanvas(int width, int height);

    // this two functions must be used in pairs !!!
    Ray3 generateRay(bool& working, int& x, int& y);
    Ray3 generateRay(int i);
    Ray3 generateRay(int x, int y);
    int rayNum();
    void recieveColor(Color3& color);

    void resetScan();
    // get the normalized coordinate on canvas

    static const Vector2 OUT;

    Vector3 eye;
    Vector3 frontDirection;
    Vector3 upDirection;
    Vector3 rightDirection;
    double angleX;
    double angleY;
    double v_ref_len;
    double h_ref_len;

    Canvas canvas;

private:
    int scan_x = 0;
    int scan_y = 0;
    int last_x = 0;
    int last_y = 0;
    double dx;
    double dy;
};


#endif //RAY_TRACER_CAMERA_H
