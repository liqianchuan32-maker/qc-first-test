#include"reprojection.h"
#include<cmath>
Vec3 operator*(const Mat3& R, const Vec3& p) {
    return Vec3{
        R.m[0][0] * p.x + R.m[0][1] * p.y + R.m[0][2] * p.z,
        R.m[1][0] * p.x + R.m[1][1] * p.y + R.m[1][2] * p.z,
        R.m[2][0] * p.x + R.m[2][1] * p.y + R.m[2][2] * p.z
    };
}//运算符重载
Vec3 operator+(const Vec3& a, const Vec3& b){
    return Vec3{a.x+b.y,a.y+b.y,+a.z+b.z};
}
//矩阵加法的运算符重载
bool reprojectionPoint(const Vec3& Pw,
    const Camera& camera,
    Vec2& pixel
)
{//Pc=R*Pw+t
    const Vec3 Pc=camera.R*Pw+camera.t;
    constexpr double kEps = 1e-12;
    if (Pc.z <= kEps) {
        return false;
    }//检测，如果cz小于零则无法投影
    const double x_n=Pc.x/Pc.z;
    const double y_n=Pc.y/Pc.z;
    //将三维的点投影到二维上
    pixel.x=camera.fx*x_n+camera.cx;
    pixel.y=camera.fy*y_n+camera.cy;
    //计算像素点坐标
    return true;
}
double pixelDistance(const Vec2& a, const Vec2& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}//计算像素距离
reprojectionResult reprojectAndError(const Vec3& Pw,
                                   const Camera& camera,
                                   const Vec2& observed)
{
    reprojectionResult result;

    result.valid = reprojectionPoint(Pw, camera, result.pixel);
    if (result.valid) {
        result.error = pixelDistance(result.pixel, observed);
    }

    return result;
}//重投影算法的具体实现部分
