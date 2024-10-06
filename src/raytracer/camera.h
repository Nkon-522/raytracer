#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utilities/vec3.h"

class Camera{
private:
    static float defocus_angle;
    static float focus_dist;
    static point3 camera_center;
    static float vfov;
    static point3 lookfrom;
    static point3 lookat;
    static vec3 vup;
    static vec3 u, v, w;

public:
    static point3 getCameraCenter();
    static float getFocusDist();
    static float getDefocusAngle();
    static float getVfov();
    static vec3 getU();
    static vec3 getV();
    static vec3 getW();

    static void setFocusDist(const float &focusDist);
    static void setDefocusAngle(const float &defocusAngle);
    static void setCameraCenter(const point3 &cameraCenter);
    static void setVFov(const float &vFov);
    static void setLookFrom(const point3 &lookFrom);
    static void setLookAt(const point3 &lookAt);
    static void setVup(const point3 &vUp);
    static void setU(const point3 &U);
    static void setV(const point3 &V);
    static void setW(const point3 &W);

    static void initialize();
};

#endif //RAYTRACER_CAMERA_H
