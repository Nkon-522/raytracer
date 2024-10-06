#include "viewport.h"

float Viewport::viewport_height{};
float Viewport::viewport_width{};

vec3 Viewport::viewport_u{};
vec3 Viewport::viewport_v{};

vec3 Viewport::pixel_delta_u{};
vec3 Viewport::pixel_delta_v{};

point3 Viewport::viewport_upper_left{};
point3 Viewport::pixel00_loc{};

vec3 Viewport::defocus_disk_u{};
vec3 Viewport::defocus_disk_v{};

// ENUM
enum class Viewport::SetupType {
    VIEWPORT_HEIGHT,
    VIEWPORT_WIDTH
};

// METHODS
float Viewport::getViewportHeight() {
    return viewport_height;
}

float Viewport::getViewportWidth() {
    return viewport_width;
}

const vec3 &Viewport::getViewportU() {
    return viewport_u;
}

const vec3 &Viewport::getViewportV() {
    return viewport_v;
}

vec3 Viewport::getPixelDeltaU() {
    return pixel_delta_u;
}

vec3 Viewport::getPixelDeltaV() {
    return pixel_delta_v;
}

const point3 &Viewport::getViewportUpperLeft() {
    return viewport_upper_left;
}

point3 Viewport::getPixel00Location() {
    return pixel00_loc;
}

vec3 Viewport::getDefocusDiskU() {
    return defocus_disk_u;
}

vec3 Viewport::getDefocusDiskV() {
    return defocus_disk_v;
}

void Viewport::setViewportHeight(float viewportHeight) {
    viewport_height = viewportHeight;
}

void Viewport::setViewportWidth(float viewportWidth) {
    viewport_width = viewportWidth;
}

void Viewport::setViewportU(const vec3 &viewportU) {
    viewport_u = viewportU;
}

void Viewport::setViewportV(const vec3 &viewportV) {
    viewport_v = viewportV;
}

void Viewport::setPixelDeltaU(const vec3 &pixelDeltaU) {
    pixel_delta_u = pixelDeltaU;
}

void Viewport::setPixelDeltaV(const vec3 &pixelDeltaV) {
    pixel_delta_v = pixelDeltaV;
}

void Viewport::setViewportUpperLeft(const point3 &viewportUpperLeft) {
    viewport_upper_left = viewportUpperLeft;
}

void Viewport::setPixel00Loc(const point3 &pixel00Loc) {
    pixel00_loc = pixel00Loc;
}

void Viewport::setDefocusDiskU(const vec3 &defocusDiskU) {
    defocus_disk_u = defocusDiskU;
}

void Viewport::setDefocusDiskV(const vec3 &defocusDiskV) {
    defocus_disk_v = defocusDiskV;
}

void Viewport::initialize() {
    setup(SetupType::VIEWPORT_WIDTH);
}

void Viewport::setup(const Viewport::SetupType &type) {
    const auto theta = degrees_to_radians(Camera::getVfov());
    const auto h = std::tan(theta/2);

    switch (type) {
        case SetupType::VIEWPORT_HEIGHT:
            setViewportWidth(2 * h * Camera::getFocusDist());
            setViewportHeight(viewport_width * static_cast<float>(Image::getImageHeight())/ static_cast<float>(Image::getImageWidth()));
            break;
        case SetupType::VIEWPORT_WIDTH:
            setViewportHeight(2 * h * Camera::getFocusDist());
            setViewportWidth(viewport_height * static_cast<float>(Image::getImageWidth())/ static_cast<float>(Image::getImageHeight()));
            break;
    }
    setViewportU(viewport_width * Camera::getU());
    setViewportV(viewport_height * - Camera::getV());
    setPixelDeltaU(viewport_u / static_cast<float>(Image::getImageWidth()));
    setPixelDeltaV(viewport_v / static_cast<float>(Image::getImageHeight()));

    setViewportUpperLeft(
        Camera::getCameraCenter()
        - (Camera::getFocusDist() * Camera::getW())
        - viewport_u / 2
        - viewport_v / 2
    );

    setPixel00Loc(
        viewport_upper_left
        + 0.5 * (pixel_delta_u + pixel_delta_v)
    );

    const auto defocus_radius = Camera::getFocusDist() * std::tan(degrees_to_radians(Camera::getDefocusAngle() / 2));
    setDefocusDiskU(Camera::getU() * defocus_radius);
    setDefocusDiskV(Camera::getV() * defocus_radius);
}


