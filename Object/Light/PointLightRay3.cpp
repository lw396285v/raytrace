//
// Created by liwen on 12/21/17.
//

#include "PointLightRay3.h"

Color3 PointLightRay3::get_color(double distance) const{
    return color/(1+distance*distance/1500);
}