#include <iostream>
#include <process.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "show.h"
#include "Rotmat2Euler.h"
#include "Eigen"
#include "Eigenvalues"

int main()
{
    show();

    Eigen::Matrix3f rotation_mat;
    Eigen::Vector3f euler_rad;
    rotation_mat << -0.02697f, -0.96295f, 0.268318f,
        -0.98587f, 0.07001f, 0.15214f,
        -0.16529f, -0.26042f, -0.95123f;

    euler_rad = Mat_Rzyx(rotation_mat);
    std::cout << "Rotation Mat" << std::endl;
    std::cout << rotation_mat << std::endl; // 打印Eigen矩阵
    std::cout << "Euler Angle in Radian ZYX" << std::endl;
    std::cout << euler_rad << std::endl;

    Eigen::Matrix3d rotation_mat_eigen;
    Eigen::Vector3d euler_rad_eigen;
    rotation_mat_eigen << -0.02697, -0.96295, 0.268318,
        -0.98587, 0.07001, 0.15214,
        -0.16529, -0.26042, -0.95123;
    euler_rad_eigen = rotation_mat_eigen.eulerAngles(2,1,0);
    std::cout << euler_rad << std::endl;

    return 0;
}
