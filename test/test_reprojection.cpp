#include "reprojection.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    Camera camera;
    camera.fx = 500.0; camera.fy = 500.0;
    camera.cx = 320.0; camera.cy = 240.0;
    camera.R = Mat3::idendity();
    camera.t = Vec3{0.0, 0.0, 0.0};

    Vec2 pixel;
    assert(reprojectionPoint(Vec3{0.0, 0.0, 5.0}, camera, pixel));
    assert(std::abs(pixel.x - 320.0) < 1e-9);
    assert(std::abs(pixel.y - 240.0) < 1e-9);

    const reprojectionResult result =
        reprojectAndError(Vec3{0.0, 0.0, 5.0}, camera, Vec2{323.0, 244.0});
    assert(result.valid);
    assert(std::abs(result.error - 5.0) < 1e-9);

    Vec2 behind;
    assert(!reprojectionPoint(Vec3{0.0, 0.0, -1.0}, camera, behind));

    std::cout << "all tests passed\n";
    return 0;
}