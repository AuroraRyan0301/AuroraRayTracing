#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


class sphere: public hitable //public继承, 不写的话继承的成员变量和成员函数都是private的
{
    public:
        sphere() {}
        sphere(vec3 cen, float r, material *mat) : center(cen), radius(r), mat_ptr(mat){}; // : center(cen), radius(r)初始化列表
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override; //virtual 允许派生类进一步覆写
        vec3 center;
        float radius;
        material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc)-radius*radius;
    float discriminant = b*b-a*c;
    if (discriminant > 0) // 如果相交
    {
        float temp = (-b-sqrt(b*b-a*c))/a; // 交点t值
        if (temp < t_max && temp > t_min) // 这个地方的判断保证了交点一定与最近的物体相关，解决了遮挡问题。
        // 由于direction是同一向量，因此这里也不涉及归一化的问题。
        {
            //更新交点信息，不要忘记更新材质指针
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t); //交点坐标
            rec.normal = (rec.p-center)/radius; //归一化法向量
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b+sqrt(b*b-a*c))/a; //另外一个交点t值，优先考虑近的交点
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t); 
            rec.normal = (rec.p-center)/radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif