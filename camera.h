#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "constant.h"
#include "random.h"

class camera
{
    public:

        // camera原理是固定相机在自己坐标系，距离z=-1有一个成像平面，ray初始方向由像素坐标和camera连线决定，ray初始位置是相机位置
        // 这里修改成像平面的theta角，实际上就是修改了相机的视场，等效于修改相机到成像平面距离，可以认为相机一直在通过一个窗口看世界，修改视场实际上在移动这个窗口。
        // 但最好的理解还是修改成像平面大小，即视场
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist){ //vfov is top to bottom in degrees, aspect is width to height, like 16:9
           
            lens_radius = aperture/2;

            float theta = vfov*M_PI/180; //弧度制
            float half_height = tan(theta/2); //tan(theta/2) = (h/2)/f
            float half_width = aspect*half_height;

            origin = lookfrom;

            w = unit_vector(lookfrom-lookat); //相机坐标系下，成像平面中心指向相机的方向，相机坐标系下，w轴负方向是相机方向
            u = unit_vector(cross(vup, w)); 
            v = cross(w, u);
            
            lower_left_corner = origin - (half_width*u + half_height*v + w)*focus_dist; //这里其实是根据聚焦点重新定义成像平面，原来默认成像平面是z=-1，现在是focus_dist
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;

            // 模糊的本质是某一个采样点，对应多个像素点，通俗地说就是图像某一点和周围点融合了，取了平均
            // 这里代码让透镜圆盘上所有点到聚焦平面（成像平面）的中心连成线，线与线的交点在成像平面中心
            // 如果某个物体不在聚焦平面上，这些线会在该物体平面形成一个圆盘，一个采样点对应了多个像素点，模糊
            // 金属模糊是类似的道理，该kernel是微扰反射光线，其实微扰反射点应该也可以

        }

        ray get_ray(float s, float t){
            vec3 rd = lens_radius*random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y(); //相机uv平面单位圆盘随机选一点
            return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
            } // ray代表返回类型，命名空间是camera
        
        vec3 lower_left_corner; //左下角
        vec3 horizontal; //水平方向
        vec3 vertical; //垂直方向
        vec3 origin; //原点
        vec3 u, v, w;
        float lens_radius;
};

#endif