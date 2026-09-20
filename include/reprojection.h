#pragma once
struct Vec2{
    double x,y;
};
//二维向量，用于储存结果
struct Vec3{
    double x,y,z;
};
//三维世界下的三维点，相机坐标系下的三维点，还有平移向量
struct Mat3{
    double m[3][3];
    static Mat3 idendity(){//标准旋转矩阵
        Mat3 R;
        R.m[0][0]=1.0;
        R.m[1][1]=1.0;
        R.m[2][2]=1.0;
        return R;
    }
};
Vec3 operator*(const Mat3& R, const Vec3& p);//矩阵乘向量
Vec3 operator+(const Vec3& a, const Vec3& b);//矩阵加法
//Mat3为相机的朝向
struct Camera{
    double fx,fy,cx,cy;
    Mat3 R=Mat3::idendity();//相机旋转矩阵
    Vec3 t;//相机平移向量
};//fx fy为像素，cx cy为主点像素坐标
struct reprojectionResult{
     bool valid = false;//判断是否有效（在不在相机后面）
    Vec2 pixel{};//返回的像素点坐标
    double error = 0.0;//欧氏距离
};
bool reprojectionPoint(const Vec3& Pw,
    const Camera& camera,
    Vec2& pixel
);//如果结果正确将会返回true
double pixelDistance(const Vec2& a, const Vec2& b);//两个像素点之间的欧氏距离
reprojectionResult reprojectAndError(const Vec3& Pw,
                                   const Camera& camera,
                                   const Vec2& observed);
//重投影并且计算误差
