#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utilities/vec3.h"

class Camera{
private:
    inline static float focal_length{1.0};
    inline static point3 camera_center{0, 0, 0};

public:
    static point3 getCameraCenter() {
        return camera_center;
    }

    static float getFocalLength() {
        return focal_length;
    }

    static void setFocalLength(const float &focalLength) {
        focal_length = focalLength;
    }

    static void setCameraCenter(const point3 &cameraCenter) {
        camera_center = cameraCenter;
    }

};

#endif //RAYTRACER_CAMERA_H
