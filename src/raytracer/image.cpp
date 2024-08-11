# include "image.h"

float Image::aspect_ratio{};
int Image::image_width{};
int Image::image_height{};

// CONSTRUCTOR
Image::Image():img{std::vector<std::uint32_t>(image_width*image_height, 0U)} {}

// ENUM
enum class Image::SetupType {
    IMAGE_HEIGHT,
    IMAGE_WIDTH
};


// METHODS
const std::vector<std::uint32_t> &Image::getImg() const {
    return img;
}

int Image::getImageWidth() {
    return image_width;
}

int Image::getImageHeight() {
    return image_height;
}

void Image::setImageWidth(int imageWidth) {
    image_width = imageWidth;
}

void Image::setImageHeight(int imageHeight) {
    image_height = imageHeight;
}

void Image::setAspectRatio(float aspectRatio) {
    aspect_ratio = aspectRatio;
}

void Image::initialize() {
    setAspectRatio(16.0 / 9.0);
    setImageWidth(400);
    setup(SetupType::IMAGE_HEIGHT);
}

// Setups either the height/width of the image based on the aspect ratio and the width/height
void Image::setup(const SetupType& type) {
    switch (type) {
        case SetupType::IMAGE_HEIGHT:
            setImageHeight(int(float(image_width)/aspect_ratio) < 1? 1: int(float(image_width)/aspect_ratio));
            break;
        case SetupType::IMAGE_WIDTH:
            setImageWidth(int(float(image_height)/aspect_ratio) < 1? 1: int(float(image_height)/aspect_ratio));
            break;
    }
}

void Image::write_color(const int &index, const color &pixel_color) {
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



