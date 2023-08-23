#ifndef COLORH
#define COLORH

#include "ray.h"
#include "constant.h"
#include "hitable_list.h"
#include "random.h"
#include "scatter.h" // 材质头文件，前向声明是虚拟的不能直接用

vec3 color(const ray& r, hitable *world, int depth){ //r是光线，world是物体
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)){ //如果光线与物体相交。
        //0.001 为了消除shadow acne problem。浮点计算导致碰撞点不是刚好在表面，而是在表面附近，会有一些极小的碰撞点，本来是该接受背景光照的地方，接受了碰撞点附近点的光照，而theta角一般又特别大，导致碰撞点暗下去一块。

        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){ //如果反射次数小于50，且材质有反射
            return attenuation*color(scattered, world, depth+1); //递归计算反射光线的颜色
        }
        else{
            return vec3(0, 0, 0); //如果反射次数大于50，或者材质没有反射，返回黑色
        }
    }

    else{ //背景色
        vec3 unit_direction = unit_vector(r.direction()); //单位化光线方向
        float t = 0.5*(unit_direction.y() + 1.0); //映射到0~1
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0); //返回渐变色
    }
}


#endif