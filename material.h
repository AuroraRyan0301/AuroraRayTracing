#ifndef METERIALH
#define METERIALH

#include "ray.h"
#include "hitable.h"

class material{
    public:

        // 不同材质散射不一样，比较复杂，所以用纯虚函数声明，后续分别定义
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0; //纯虚函数，只有声明，没有定义，只能在派生类中定义
        
        
        // 一些公共函数，不同材质都一样
        //反射
        vec3 reflect(const vec3& v, const vec3& n) const
        {
            return v-2*dot(v, n)*n;
        }

        //折射
        bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const //n 是单位化的（sphere.h里定义）， v没有单位化
            {
                vec3 uv = unit_vector(v); //单位化
                float dt = dot(uv, n); //cos_theta
                float discriminant = 1.0-ni_over_nt*ni_over_nt*(1-dt*dt); //判别式
                if (discriminant > 0) //如果有解
                {
                    refracted = ni_over_nt*(uv-n*dt)-n*sqrt(discriminant); //解，折射方向，sqrt(discriminant)是折射角的cos值
                    return true;
                }
                else
                {
                    return false;
                }
            }

        //reflectivity that varies with angle, Christophe Schlick polynomial approximation

        float schlick(float cosine, float ni_over_nt) const
        {
            float r0 = (ni_over_nt-1)/(ni_over_nt+1);
            r0 = r0*r0;
            return r0+(1-r0)*pow((1-cosine), 5);
        }
};





#endif