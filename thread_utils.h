#ifndef THREADUTILSH
#define THREADUTILSH

#include <random>
#include <thread>

#include "vec3.h"
#include "ray.h"
#include "constant.h"
#include "random.h"
#include "hitable_list.h"
#include "color.h"
#include "camera.h"
#include "progress_bar.h"



// 每个线程进行的渲染循环
vec3 pixelRender(int i, int j, hitable *world, camera cam) { // i是nx，宽，j是ny，高
            // 说实话这个地方我想只针对边缘进行判断
            vec3 col(0,0,0);
            for (int s = 0; s < numSamples; s++ ){

                //多数时候随机数生成算法不构成性能瓶颈，不推荐使用老标准的drand48

                float u = float(i+randomGenerator())/float(imageWidth); //映射到0~1，这里利用了随机数小于1的特性
                float v = float(j+randomGenerator())/float(imageHeight); //映射到0~1
                ray r = cam.get_ray(u,v); //光线
                col += color(r, world,0); //颜色
            }
            col /= float(numSamples); //取平均

            // gamma correction
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

            int ir = int(255.99 * col[0]); //映射到0~255
            int ig = int(255.99 * col[1]); //映射到0~255
            int ib = int(255.99 * col[2]); //映射到0~255
            // file << ir << " " << ig << " " << ib << "\n";

            return vec3(ir, ig, ib);
}

void taskAlloc(int threadId, int numThreads, hitable *world, camera cam, vec3 **image) // image存储pixel
{
    // 计算每个线程负责的像素范围

    int taskSize = imageHeight / numThreads;
    int upY = imageHeight - threadId * taskSize;
    int downY =  imageHeight - (threadId+1) * taskSize;

    if (threadId == (numThreads-1)) // 最后一个线程负责剩下的像素
    {
        downY = 0; 
        taskSize = upY - downY; //downY发生变化，更新taskSize
    }

    for (int j = upY-1; j >= downY; j--)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            // 可以上锁
            image[j][i] = pixelRender(i, j, world, cam);
        }
        printProgress(threadId, (upY-1-j)*1.0/taskSize*100);
    }
}

#endif