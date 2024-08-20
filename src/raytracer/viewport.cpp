#include "viewport.h"

float Viewport::viewport_height{};
float Viewport::viewport_width{};

vec3 Viewport::viewport_u{};
vec3 Viewport::viewport_v{};

vec3 Viewport::pixel_delta_u{};
vec3 Viewport::pixel_delta_v{};

point3 Viewport::viewport_upper_left{};
point3 Viewport::pixel00_loc{};

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

void Viewport::initialize() {
    setViewportHeight(2.0);
    setup(SetupType::VIEWPORT_WIDTH);
}

void Viewport::setup(const Viewport::SetupType &type) {
    switch (type) {
        case SetupType::VIEWPORT_HEIGHT:
            setViewportHeight(viewport_width * static_cast<float>(Image::getImageHeight())/ static_cast<float>(Image::getImageWidth()));
            break;
        case SetupType::VIEWPORT_WIDTH:
            setViewportWidth(viewport_height * static_cast<float>(Image::getImageWidth())/ static_cast<float>(Image::getImageHeight()));
            break;
    }
    setViewportU({viewport_width, 0, 0});
    setViewportV({0, -viewport_height, 0});
    setPixelDeltaU(viewport_u / static_cast<float>(Image::getImageWidth()));
    setPixelDeltaV(viewport_v / static_cast<float>(Image::getImageHeight()));

    setViewportUpperLeft(
        Camera::getCameraCenter()
        - vec3{0.0f, 0.0f, Camera::getFocalLength()}
        - viewport_u / 2
        - viewport_v / 2
    );

    setPixel00Loc(
        viewport_upper_left
        + 0.5 * (pixel_delta_u + pixel_delta_v)
    );
}


