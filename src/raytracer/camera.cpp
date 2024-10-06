#include "camera.h"

float Camera::defocus_angle{};
float Camera::focus_dist{};
point3 Camera::camera_center{};
float Camera::vfov{};
point3 Camera::lookfrom{};
point3 Camera::lookat{};
vec3 Camera::vup{};
vec3 Camera::u{};
vec3 Camera::v{};
vec3 Camera::w{};

// METHODS
point3 Camera::getCameraCenter() {
    return camera_center;
}

float Camera::getFocusDist() {
    return focus_dist;
}

float Camera::getDefocusAngle() {
    return defocus_angle;
}


float Camera::getVfov() {
    return vfov;
}

vec3 Camera::getU() {
    return u;
}

vec3 Camera::getV() {
    return v;
}

vec3 Camera::getW() {
    return w;
}

void Camera::setFocusDist(const float &focusDist) {
    focus_dist = focusDist;
}

void Camera::setDefocusAngle(const float &defocusAngle) {
    defocus_angle = defocusAngle;
}

void Camera::setCameraCenter(const point3 &cameraCenter) {
    camera_center = cameraCenter;
}

void Camera::setVFov(const float &vFov) {
    vfov = vFov;
}

void Camera::setLookFrom(const point3 &lookFrom) {
    lookfrom = lookFrom;
}

void Camera::setLookAt(const point3 &lookAt) {
    lookat = lookAt;
}

void Camera::setVup(const point3 &vUp) {
    vup = vUp;
}

void Camera::setU(const point3 &U) {
    u = U;
}

void Camera::setV(const point3 &V) {
    v = V;
}

void Camera::setW(const point3 &W) {
    w = W;
}

void Camera::initialize() {
    setVFov(20);
    setLookFrom(point3(13,2,3));
    setLookAt(point3(0,0,0));
    setVup({0, 1, 0});
    setCameraCenter(lookfrom);
    setDefocusAngle(0.6);
    setFocusDist(10.0);
    setW(unit_vector(lookfrom - lookat));
    setU(unit_vector(cross(vup, w)));
    setV(cross(w, u));
}
