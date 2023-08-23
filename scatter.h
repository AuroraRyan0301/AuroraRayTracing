#ifndef SCATTERH
#define SCATTERH

#include "material.h"
#include "random.h"

class lambertian : public material
{
    public:
        lambertian(const vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
        {
            vec3 target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p, target-rec.p); //计算散射光线
            // 这里假设碰撞点有一个相切球，相切球内随机选一点与碰撞点连线，对于某个theta角的概率正比于cos_theta，Lambertian reflection model（反射强度正比于cos_theta）于是被实现
            // 数学证明可以这样想，某个theta角的射线长度正比于cos_theta，所有射线都是转一圈，体积微元来看，theta概率正比于cos_theta
            attenuation = albedo;
            return true;
        }

        vec3 albedo;
};

class metal : public material
{
    public:
        metal(const vec3& a, float f) : albedo(a) {if (f < 1) fuzz = f; else fuzz = 1;}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override
        {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal); //获取反射方向
            scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0); //因为有fuzzy的存在，这里有可能为负，所以要判断
        }

        vec3 albedo;
        float fuzz;

};

class dielectric: public material{
    public:
        dielectric(float ri) : ref_idx(ri) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override
        {
            vec3 up_normal; // 一般两材料折射图中，向上的法线，物体内部指向外部，入射光线从外部到内部
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            float ni_over_nt;
            attenuation = vec3(1.0, 1.0, 1.0); //折射光线衰减为黄色，即去除蓝色
            vec3 refracted;
            float reflect_prob;
            float cosine;


            // 根据入射光线分球内球外两种情况，更新折射相关参数。这里光线方向假设眼睛会发光
            if (dot(r_in.direction(), rec.normal) > 0) //从物体外部射入，已有光线为球体内部的折射光线，追踪入射光线
            {
                up_normal = -rec.normal; //入射光线在球内，因而法线方向相反，rec.normal恒指向球外
                ni_over_nt = ref_idx; 
            }
            else //从物体内部射出，已有光线为球外光线，追踪球体内部的折射光线
            {
                up_normal = rec.normal;
                ni_over_nt = 1.0/ref_idx;
            }

            if (refract(r_in.direction(), up_normal, ni_over_nt, refracted)) //折射
            {
                cosine = dot(refracted,-up_normal); //cos_theta

                reflect_prob = schlick(cosine, ni_over_nt); //计算反射概率
            }
            else //全反射
            {
                reflect_prob = 1.0;
            }

            // 计算折射
            if (randomGenerator() < reflect_prob) //全反射
            {
                scattered = ray(rec.p, reflected);
            }
            else //折射
            {
                scattered = ray(rec.p, refracted);
            }
            return true;

        }

        float ref_idx;



};





#endif