#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "utilities/utils.h"

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
    inline static const int init = [] {
        initialize();
        return 1;
    }();

    void setup_scene();

    color ray_color(const ray& r);
public:
    Raytracer();
    [[nodiscard]] const std::vector<std::uint32_t> &getPreviewImage() const;
    [[maybe_unused]] [[nodiscard]] const std::vector<std::uint32_t> &getImage() const;

    void render_preview();
};

#endif //RAYTRACER_RAYTRACER_H
