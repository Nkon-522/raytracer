#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <cstdint>
#include "utilities/vec3.h"

using color = vec3;

class Image {
private:
    // Image parameters
    inline static float aspect_ratio{16.0 / 9.0};
    inline static int image_width{400};
    inline static int image_height{int(float(image_width)/aspect_ratio) < 1? 1: int(float(image_width)/aspect_ratio)};

    std::vector<std::uint32_t> img;

public:
    Image():img{std::vector<std::uint32_t>(image_width*image_height, 0U)} {};

    [[nodiscard]] const std::vector<std::uint32_t>& getImg() const {
        return img;
    }

    static int getImageWidth() {
        return image_width;
    }

    static int getImageHeight() {
        return image_height;
    }

    static void setAspectRatio(float aspectRatio) {
        aspect_ratio = aspectRatio;
    }

    static void setImageWidth(int imageWidth) {
        image_width = imageWidth;
    }

    static void setImageHeight(int imageHeight) {
        image_height = imageHeight;
    }

    void write_color(const int& index, const color& pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Translate the [0,1] component values to the byte range [0,255].
        auto red_byte = std::uint32_t(255.999 * r);
        auto green_byte = std::uint32_t(255.999 * g);
        auto blue_byte = std::uint32_t(255.999 * b);

        // Write out the pixel color components.
        std::uint32_t alpha_byte = 255;
        img[index] = (red_byte << 24U) | (green_byte << 16U) | (blue_byte << 8U) | alpha_byte;
    }

    static void recalibrate_aspect_ratio(const int& aspect_ratio_type) {
        switch (aspect_ratio_type) {
            case -1:
                aspect_ratio = -1;
                break;
            case 0:
                aspect_ratio = 16.0 / 9.0;
                setImageHeight(int(float(image_width)/aspect_ratio) < 1? 1: int(float(image_width)/aspect_ratio));
                break;
            case 1:
                aspect_ratio = 1.0;
                setImageHeight(int(float(image_width)/aspect_ratio) < 1? 1: int(float(image_width)/aspect_ratio));
                break;
            default:
                aspect_ratio = -1;
                break;
        }
    }

};

#endif //RAYTRACER_IMAGE_H
