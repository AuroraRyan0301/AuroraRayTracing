#ifndef RAYH //头文件保护符，ray.h只会被编译一次
#define RAYH
#include"vec3.h"

class ray
{
    public:
        ray() {} //默认构造函数，参数空，用于无参声明如：ray a;
        ray(const vec3& a,const vec3& b){A = a; B = b;} //构造函数，用于有参声明，a是起点，b是方向
        vec3 origin() const{return A;}
        vec3 direction() const{return B;}
        vec3 point_at_parameter(float t) const{return A+t*B;}

        vec3 A;
        vec3 B; //类的成员变量，用于存储数据，这里声明不多余，因为类的成员变量默认是private的，只能在类内部访问，所以要声明public
};
#endif