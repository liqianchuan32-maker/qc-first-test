# qc-first-test
27 赛季算法组视觉侧第一次培训作业：针孔模型重投影。
## 构建
cmake -S . -B build
cmake --build build -j
## 运行
./build/reprojection_demo
输入顺序：
1. 内参 fx fy cx cy
2. 旋转矩阵 R 的 9 个数（行主序）
3. 平移向量 t 的 3 个数
4. 世界点 Pw 的 3 个坐标
5. 观测像素 u v
## 测试
cd build && ctest --output-on-failure
