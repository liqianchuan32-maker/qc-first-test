#include "reprojection.h"

#include <iomanip>
#include <iostream>

int main() {
    Camera camera;
    Vec3 Pw;
    Vec2 observed;

    // 1. 输入内参
    std::cout << "请输入内参 fx fy cx cy: ";
    if (!(std::cin >> camera.fx >> camera.fy >> camera.cx >> camera.cy)) {
        std::cerr << "内参输入错误\n";
        return 1;
    }

    // 2. 输入旋转矩阵 R，行主序，共 9 个数
    std::cout << "请输入旋转矩阵 R 的 9 个数（按行输入）:\n";
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (!(std::cin >> camera.R.m[r][c])) {
                std::cerr << "旋转矩阵 R 输入错误\n";
                return 1;
            }
        }
    }

    // 3. 输入平移向量 t
    std::cout << "请输入平移向量 t 的 3 个数 tx ty tz: ";
    if (!(std::cin >> camera.t.x >> camera.t.y >> camera.t.z)) {
        std::cerr << "平移向量 t 输入错误\n";
        return 1;
    }

    // 4. 输入世界点 Pw
    std::cout << "请输入世界点 Pw 的 3 个坐标 Xw Yw Zw: ";
    if (!(std::cin >> Pw.x >> Pw.y >> Pw.z)) {
        std::cerr << "世界点输入错误\n";
        return 1;
    }

    // 5. 输入观测像素
    std::cout << "请输入观测像素 u_obs v_obs: ";
    if (!(std::cin >> observed.x >> observed.y)) {
        std::cerr << "观测像素输入错误\n";
        return 1;
    }

    // 6. 调用重投影函数
    const reprojectionResult result =
        reprojectAndError(Pw, camera, observed);

    // 7. 判断深度是否有效
    if (!result.valid) {
        std::cerr << "重投影失败：点在相机后方，或深度接近 0"
                  << "（Pc.z <= 0）\n";
        return 2;
    }

    // 8. 输出结果
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\n===== 重投影结果 =====\n";
    std::cout << "预测像素: ("
              << result.pixel.x << ", "
              << result.pixel.y << ")\n";
    std::cout << "重投影误差: "
              << result.error << " 像素\n";

    return 0;
}
