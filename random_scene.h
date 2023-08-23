#ifndef RANDOMSCENEH
#define RANDOMSCENEH

#include "hitable_list.h"
#include "random.h"
#include "sphere.h"
#include "scatter.h"

hitable *random_scene(){
    int n = 500;
    hitable **list = new hitable*[n+1]; //list是指针数组，指向hitable对象的指针
    list[0] = new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5,0.5,0.5))); //地面
    int i = 1;
    for (int a = -11; a < 11; a += 1)
    {
        for (int b = -11; b < 11; b += 1)
        {
            float choose_mat = randomGenerator();
            float center_offset1 = 0.9*randomGenerator()/2;
            float center_offset2 = 0.9*randomGenerator()/2;
            vec3 center(a+center_offset1,0.2,b + center_offset2);
            if (((center - vec3(4, 0.2, 0)).length() > 2) && ((center - vec3(-4, 0.2, 0)).length() > 0.9) && ((center - vec3(0, 0.2, 0)).length() > 0.9)) //避免小球在大球里面
            {
                if (choose_mat < 0.8) //diffuse
                {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(randomGenerator()*randomGenerator(), randomGenerator()*randomGenerator(), randomGenerator()*randomGenerator())));
                }
                else if (choose_mat < 0.95) //metal
                {
                    list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+randomGenerator()), 0.5*(1+randomGenerator()), 0.5*(1+randomGenerator())), 0.5*randomGenerator()));
                }
                else //glass
                {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }

    }
    list[i++] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5)); //中间的大球
    list[i++] = new sphere(vec3(-4,1,0), 1.0, new lambertian(vec3(0.4,0.2,0.1))); //左边的大球
    list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(vec3(0.7,0.6,0.5), 0.0)); //右边的大球

    // 打印生成完毕，汇报球体总数
    std::cout << "Spheres generation completed! Total number of spheres: " << i << std::endl;

    return new hitable_list(list, i); //返回hitable_list对象
}

#endif