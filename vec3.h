#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3{
public:
    vec3() {} //默认构造函数，参数空，用于无参声明如：vec3 a;
    vec3(float e0, float e1, float e2){
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    } //构造函数，用于有参声明如：vec3 a(1,2,3);
    inline float x() const {return e[0];} //inline函数，用于内联函数直接插入代码，提高效率
    inline float y() const {return e[1];} //const函数，用于类里，常量函数，不改变类的成员变量
    inline float z() const {return e[2];} 
    inline float r() const {return e[0];}
    inline float g() const {return e[1];}
    inline float b() const {return e[2];}

    inline const vec3& operator+() const {return *this;} //一元重载运算符，对类进行+-*/等运算，第一个const是类不变，是vec3常量对象，第二个const是返回值不变
    inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);} //新建了一个类，仍然没有对原类进行修改。注意vec3是匿名的，属于临时变量，函数执行完后会销毁，不能引用返回
    inline float operator[](int i) const {return e[i];} //重载[]运算符，用于类的数组访问，不能用作左值，因为返回的是一个值，而不是引用
    inline float& operator[](int i) {return e[i];} //引用，用于左值，如：vec3 a; a[0] = 1; &和后面的const不能共存，除非&也是const，但实际上我们就是为了改变值才用引用的，所以不用const
    //这个引用是结构体返回的常见写法，返回对计算结果的引用，而不是复制一个新的类，虽然二者空间开销相同，但是引用更快，不用调用可能非常复杂的构造函数

    //二元重载函数
    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator+=(const float t);
    inline vec3& operator-=(const float t);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const{
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline float squared_length() const{
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();

    float e[3]; //类的成员变量，用于存储数据，这里声明不多余，因为类的成员变量默认是private的，只能在类内部访问，所以要声明public
};
    //定义矢量的各种运算
inline std::istream& operator>>(std::istream &is, vec3 &t){
    is >> t.e[0] >> t.e[1] >> t.e[2]; //重载>>运算符，依次读取，返回is用于链式输入，如：cin >> a >> b;
    return is;
}
inline std::ostream& operator<<(std::ostream &os, const vec3 &t){
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os; //返回os用于链式输出
}
inline void vec3::make_unit_vector(){
    float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}
inline vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0]+v2.e[0], v1.e[1]+v2.e[1], v1.e[2]+v2.e[2]);
}
inline vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0]-v2.e[0], v1.e[1]-v2.e[1], v1.e[2]-v2.e[2]);
}

inline vec3 operator+(float t, const vec3 &v){
    return vec3(t+v.e[0], t+v.e[1], t+v.e[2]);
}
inline vec3 operator-(float t, const vec3 &v){
    return vec3(v.e[0]-t,v.e[1]-t, v.e[2]-t);
}


inline vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0]*v2.e[0], v1.e[1]*v2.e[1], v1.e[2]*v2.e[2]);
}
inline vec3 operator/(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0]/v2.e[0], v1.e[1]/v2.e[1], v1.e[2]/v2.e[2]);
}
inline vec3 operator*(float t, const vec3 &v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator/(const vec3 &v, float t){
    return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}
inline vec3 operator*(const vec3 &v, float t){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline float dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] +v1.e[2]*v2.e[2];
}
inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3((v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}
inline vec3& vec3::operator+=(const vec3 &v){
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}
inline vec3& vec3::operator-=(const vec3 &v){
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this; 
}
inline vec3& vec3::operator*=(const vec3 &v){
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}
inline vec3& vec3::operator/=(const vec3 &v){
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator+=(const float t){
    e[0] += t;
    e[1] += t;
    e[2] += t;
    return *this;
}
inline vec3& vec3::operator-=(const float t){
    e[0] -= t;
    e[1] -= t;
    e[2] -= t;
    return *this; 
}

inline vec3& vec3::operator*=(const float t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}
inline vec3& vec3::operator/=(const float t){
    float k = 1.0/t;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}
// 以上函数有些不使用引用返回，原因是返回的值太简单（不是复杂的结构体），没必要。
// 其他情况不使用引用返回的原因是函数中有新定义临时变量，引用会导致错误，因为函数执行完后会销毁临时变量，引用为空。

#endif

