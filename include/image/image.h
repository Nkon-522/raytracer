#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <cstdint>
#include "utilities/vec3.h"

using color = vec3;

class Image {
public:
    // Image parameters
    static const int IMAGE_WIDTH = 256;
    static const int IMAGE_HEIGHT = 256;

private:
    std::vector<std::uint32_t> img;

    void write_color(const int& index, const color& pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Translate the [0,1] component values to the byte range [0,255].
        auto rbyte = std::uint32_t(255.999 * r);
        auto gbyte = std::uint32_t(255.999 * g);
        auto bbyte = std::uint32_t(255.999 * b);

        // Write out the pixel color components.
        std::uint32_t abyte = 255;
        img[index] = (rbyte << 24U) | (gbyte << 16U) | (bbyte << 8U) | abyte;
    }

public:
    Image() {
        img = std::vector<std::uint32_t>(IMAGE_WIDTH*IMAGE_HEIGHT, 0U);
    }

    void render() {
        for (int i = 0; i < IMAGE_HEIGHT; ++i) {
            for (int j = 0; j < IMAGE_WIDTH; ++j) {
                auto pixel_color = color(float (i)/(IMAGE_HEIGHT-1), float(j)/(IMAGE_WIDTH-1), 0);
                int index = i*IMAGE_WIDTH + j;
                write_color(index, pixel_color);
            }
        }
    }

    [[nodiscard]] const std::vector<std::uint32_t> &getImg() const {
        return img;
    }
};

#endif //RAYTRACER_IMAGE_H
