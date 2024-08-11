#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utilities/vec3.h"

class Camera{
private:
    static float focal_length;
    static point3 camera_center;

public:
    static point3 getCameraCenter();
    static float getFocalLength();

    static void setFocalLength(const float &focalLength);
    static void setCameraCenter(const point3 &cameraCenter);

    static void initialize();
};

#endif //RAYTRACER_CAMERA_H
