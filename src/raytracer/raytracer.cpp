#include "raytracer.h"

int Raytracer::samples_per_pixel{};
int Raytracer::max_depth{};

// CONSTRUCTOR

Raytracer::Raytracer() {
    initialize();
    preview_image = Image{};
    image = Image{};

    // Raytracer parameters
    samples_per_pixel = 100;
    max_depth = 50;

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
    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            point3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_float(0,.5), 0);
                    world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

}

void Raytracer::render_preview() {
    for (int i = 0; i < Image::getImageHeight(); ++i) {
        for (int j = 0; j < Image::getImageWidth(); ++j) {
            color pixel_color{0,0,0};
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                ray sampling_ray_direction = get_sampling_ray(i, j);
                pixel_color += ray_color(sampling_ray_direction, max_depth);
            }
            pixel_color /= static_cast<float>(samples_per_pixel);

            // Color the pixel
            int index = i*Image::getImageWidth() + j;
            preview_image.write_color(index, pixel_color);
        }
    }
}


color Raytracer::ray_color(const ray &r, const int& depth) const {
    if (depth <= 0) {
        return {0, 0, 0};
    }

    if (hit_record rec; world.hit(r, interval(0.001, infinity), rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1);
        }
        return {0, 0, 0};
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
    const auto ray_origin = (Camera::getDefocusAngle() <= 0)? Camera::getCameraCenter(): defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = random_float();

    // Ray directed to pixel
    return {ray_origin, ray_direction, ray_time};
}

point3 Raytracer::defocus_disk_sample() {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return Camera::getCameraCenter() + (p[0] * Viewport::getDefocusDiskU()) + (p[1] * Viewport::getDefocusDiskV());
}
