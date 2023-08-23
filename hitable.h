#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material; //前置声明，因为hit_record中有material指针，而material中又有hit_record，所以只能前置声明

struct hit_record
{
    float t; // 光线到交点的距离
    vec3 p; //交点坐标
    vec3 normal; //交点处的法向量

    material *mat_ptr; //材质指针
};

class hitable 
// 抽象类，不能实例化，只能被继承。

//只是一个声明，方便后续开发都按这个规范进行。

//有多态性的考虑，后续所有物体都被视为hitable类, 这样就可以用hitable类的指针数组来存储所有物体
{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0; //纯虚函数，只有声明，没有定义，只能在派生类中定义
};

#endif
