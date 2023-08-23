#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list: public hitable
{
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) : list(l), list_size(n) {}; // : list(l), list_size(n)初始化列表, 这里改成这样会比在函数体里面赋值快
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
        hitable **list; // hitable list本身只存储指针，不存储实际的物体（开销考虑），指针数组可以访问到指向物体的指针
        int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max; // 初始值设为最远端
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) // 这里如果list[i]是球体，就是调用的hit函数是sphere::hit， 不会循环调用hitable_list::hit
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif