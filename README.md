# AuroraRayTracing
Aurora Ryan's Ray Tracing Kernel

## 效果图

<img src="./hello world.png" class="floatpic">

## 目前已实现的功能

- 多线程渲染
- Defocus Blur
- Movable Camera with arbitrary field of view
- Simple Sphere Rendering
- 单向光线追踪
- 一般漫反射
- glass(with Christophe Schlick polynomial approximation)
- metal(with fuzz)

## 下一阶段目标

- light
- **BDPT**
- 三角形
- surface textures
- solid textures
- volumes
- media

## Instruction

- 图片参数设置在constant.h里
- 各种material在scatter.h里，material.h只是声明
- world 与 各种物体的集合 在hitable_list.h里，hitable.h只是声明 

