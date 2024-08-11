#include "camera.h"

float Camera::focal_length{};
point3 Camera::camera_center{};

// METHODS
point3 Camera::getCameraCenter() {
    return camera_center;
}

float Camera::getFocalLength() {
    return focal_length;
}

void Camera::setFocalLength(const float &focalLength) {
    focal_length = focalLength;
}

void Camera::setCameraCenter(const point3 &cameraCenter) {
    camera_center = cameraCenter;
}

void Camera::initialize() {
    setFocalLength(1.0);
    setCameraCenter({0, 0, 0});
}
