#include "raytracer.h"

// CONSTRUCTOR

Raytracer::Raytracer() {
    initialize();
    preview_image = Image{};
    image = Image{};
    setup_scene();
}

// METHODS

void Raytracer::initialize() {
    Camera::initialize();
    Image::initialize();
    Viewport::initialize();
}

const std::vector<std::uint32_t> &Raytracer::getPreviewImage() const {
    return preview_image.getImg();
}

const std::vector<std::uint32_t> &Raytracer::getImage() const {
    return image.getImg();
}

void Raytracer::setup_scene() {
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));
}

void Raytracer::render_preview() {
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


color Raytracer::ray_color(const ray &r) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    float a = 0.5f * float(unit_direction.y() + 1.0);
    return (1.0f-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
