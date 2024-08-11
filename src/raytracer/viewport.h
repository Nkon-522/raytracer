#ifndef RAYTRACER_VIEWPORT_H
#define RAYTRACER_VIEWPORT_H

#include "image.h"
#include "camera.h"

class Viewport {
private:
    static float viewport_height;
    static float viewport_width;

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    static vec3 viewport_u;
    static vec3 viewport_v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    static vec3 pixel_delta_u;
    static vec3 pixel_delta_v;

    // Upper left pixel
    static point3 viewport_upper_left;
    static point3 pixel00_loc;

public:
    enum class SetupType;

    static float getViewportHeight();
    static float getViewportWidth();
    static const vec3 &getViewportU();
    static const vec3 &getViewportV();
    static vec3 getPixelDeltaU();
    static vec3 getPixelDeltaV();
    static const point3& getViewportUpperLeft();
    static point3 getPixel00Location();

    static void setViewportHeight(float viewportHeight);
    static void setViewportWidth(float viewportWidth);
private:
    static void setViewportU(const vec3 &viewportU);
    static void setViewportV(const vec3 &viewportV);
    static void setPixelDeltaU(const vec3 &pixelDeltaU);
    static void setPixelDeltaV(const vec3 &pixelDeltaV);
    static void setViewportUpperLeft(const point3 &viewportUpperLeft);
    static void setPixel00Loc(const point3 &pixel00Loc);
public:
    static void initialize();
    static void setup(const SetupType& type);
};

#endif //RAYTRACER_VIEWPORT_H
