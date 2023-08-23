#ifndef RANDOMH
#define RANDOMH

#include <random>
#include "vec3.h"

float randomGenerator() //生成0~1的随机数
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0); //static只初始化一次
    return dis(gen);
}

vec3 random_in_unit_sphere(){ //生成单位球内的随机点
    vec3 p;
    do{
        p = 2.0 * vec3(randomGenerator(),randomGenerator(),randomGenerator()) - vec3(1,1,1); //生成-1~1的随机点
    }while(p.squared_length() >= 1.0); //如果点在球外，重新生成
    return p;
}

vec3 random_in_unit_disk(){
    vec3 p;
    do{
        p = 2.0 * vec3(randomGenerator(),randomGenerator(),0) - vec3(1,1,0);
    }while(p.squared_length() >= 1.0);
    return p;
}

#endif