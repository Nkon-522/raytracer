#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "utilities/utils.h"

#include "material/material.h"

#include "shapes/hittable.h"
#include "shapes/hittable_list.h"
#include "shapes/sphere.h"

#include "image.h"
#include "viewport.h"

class Raytracer {

private:
    Image preview_image;
    Image image;
    hittable_list world;

    static void initialize();
    void setup_scene();

    static int samples_per_pixel;
    static int max_depth;

    [[nodiscard]] color ray_color(const ray& r,const int& depth) const;
    [[nodiscard]] static ray get_sampling_ray(const int& i, const int& j);
    [[nodiscard]] static point3 defocus_disk_sample();
public:
    Raytracer();
    [[nodiscard]] const std::vector<std::uint32_t> &getPreviewImage() const;
    [[maybe_unused]] [[nodiscard]] const std::vector<std::uint32_t> &getImage() const;

    void render_preview();
};

#endif //RAYTRACER_RAYTRACER_H
