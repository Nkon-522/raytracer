#ifndef RAYTRACER_VIEWPORT_H
#define RAYTRACER_VIEWPORT_H

#include "raytracer/image.h"
#include "raytracer/camera.h"

class Viewport {
private:
    inline static float viewport_height{2.0};
    inline static float viewport_width{viewport_height * ((float) Image::getImageWidth())/ (float) Image::getImageHeight()};

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    inline static vec3 viewport_u{viewport_width, 0, 0};
    inline static vec3 viewport_v{0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    inline static vec3 pixel_delta_u = viewport_u / float(Image::getImageWidth());
    inline static vec3 pixel_delta_v = viewport_v / float(Image::getImageHeight());

    // Upper left pixel
    inline static point3 viewport_upper_left =
            Camera::getCameraCenter()
            - vec3{0.0f, 0.0f, Camera::getFocalLength()}
            - viewport_u / 2
            - viewport_v / 2;

    inline static point3 pixel00_loc =
            viewport_upper_left
            + 0.5 * (pixel_delta_u + pixel_delta_v);

public:

    static float getViewportHeight() {
        return viewport_height;
    }

    static float getViewportWidth() {
        return viewport_width;
    }

    static const vec3 &getViewportU() {
        return viewport_u;
    }

    static const vec3 &getViewportV() {
        return viewport_v;
    }

    static vec3 getPixelDeltaU() {
        return pixel_delta_u;
    }

    static vec3 getPixelDeltaV() {
        return pixel_delta_v;
    }

    static const point3 &getViewportUpperLeft() {
        return viewport_upper_left;
    }

    static point3 getPixel00Location() {
        return pixel00_loc;
    }

    static void recalibrate() {
        viewport_width = viewport_height * ((float) Image::getImageWidth())/ (float) Image::getImageHeight();
        viewport_u = {viewport_width, 0, 0};
        viewport_v = {0, -viewport_height, 0};
        pixel_delta_u = viewport_u / float(Image::getImageWidth());
        pixel_delta_v = viewport_v / float(Image::getImageHeight());

        viewport_upper_left =
                Camera::getCameraCenter()
                - vec3{0.0f, 0.0f, Camera::getFocalLength()}
                - viewport_u / 2
                - viewport_v / 2;

        pixel00_loc =
                viewport_upper_left
                + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
};

#endif //RAYTRACER_VIEWPORT_H
