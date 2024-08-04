#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "utilities/ray.h"
#include "raytracer/image.h"
#include "raytracer/viewport.h"

class Raytracer {
private:
    Image preview_image;
    Image image;

    static color ray_color(const ray& r) {
        vec3 unit_direction = unit_vector(r.direction());
        float a = 0.5f * float(unit_direction.y() + 1.0);
        return (1.0f-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

public:
    Raytracer(): preview_image{}, image{} {}

    void render_preview() {
        for (int i = 0; i < Image::getImageHeight(); ++i) {
            for (int j = 0; j < Image::getImageWidth(); ++j) {
                // Pixel to evaluate
                auto pixel_center =
                        Viewport::getPixel00Location()
                        + (float(i) * Viewport::getPixelDeltaV())
                        + (float(j) * Viewport::getPixelDeltaU());

                // Direction from camera to evaluated pixel
                auto ray_direction =
                        pixel_center
                        - Camera::getCameraCenter();

                // Ray directed to pixel
                ray r(Camera::getCameraCenter(), ray_direction);
                color pixel_color = ray_color(r);

                // Color the pixel
                int index = i*Image::getImageWidth() + j;
                preview_image.write_color(index, pixel_color);
            }
        }
    }

    [[nodiscard]] const std::vector<std::uint32_t> &getPreviewImage() const {
        return preview_image.getImg();
    }

    [[maybe_unused]] [[nodiscard]] const std::vector<std::uint32_t> &getImage() const {
        return image.getImg();
    }
};

#endif //RAYTRACER_RAYTRACER_H
