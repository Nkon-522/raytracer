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
            color pixel_color{0,0,0};
            for (int sample = 0; sample < Image::getSamplesPerPixel(); ++sample) {
                ray sampling_ray_direction = get_sampling_ray(i, j);
                pixel_color += ray_color(sampling_ray_direction);
            }
            pixel_color /= static_cast<float>(Image::getSamplesPerPixel());

            // Color the pixel
            int index = i*Image::getImageWidth() + j;
            preview_image.write_color(index, pixel_color);
        }
    }
}


color Raytracer::ray_color(const ray &r) const {
    if (hit_record rec; world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    const vec3 unit_direction = unit_vector(r.direction());
    const float a = 0.5f * static_cast<float>(unit_direction.y() + 1.0);
    return (1.0f-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

ray Raytracer::get_sampling_ray(const int &i, const int &j) {
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    // Random point in the [-.5,-.5]-[+.5,+.5] unit square.
    const auto offset = vec3(random_float() - 0.5f, random_float() - 0.5f, 0);

    // Pixel to evaluate
    const auto pixel_sample =
            Viewport::getPixel00Location()
            + ((static_cast<float>(i) + offset.y()) * Viewport::getPixelDeltaV())
            + ((static_cast<float>(j) + offset.x()) * Viewport::getPixelDeltaU());

    // Direction from camera to evaluated pixel
    auto ray_direction =
            pixel_sample
            - Camera::getCameraCenter();

    // Ray directed to pixel
    return {Camera::getCameraCenter(), ray_direction};
}
