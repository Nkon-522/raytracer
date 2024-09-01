#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <vector>
#include <cstdint>

#include "utilities/vec3.h"
#include "utilities/interval.h"

using color = vec3;

class Image {
private:
    static float aspect_ratio;
    static int image_width;
    static int image_height;
    static int samples_per_pixel;
    std::vector<std::uint32_t> img;

public:
    Image();
    enum class SetupType;

    [[nodiscard]] const std::vector<std::uint32_t>& getImg() const;
    static int getImageWidth();
    static int getImageHeight();
    static int getSamplesPerPixel();

    static void setImageWidth(int imageWidth);
    static void setImageHeight(int imageHeight);
    static void setAspectRatio(float aspectRatio);
    static void setSamplesPerPixel(int samplesPerPixel);

    static void initialize();
    static void setup(const SetupType& type);
    void write_color(const int& index, const color& pixel_color);

};

#endif //RAYTRACER_IMAGE_H
