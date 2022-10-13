#include "detectAruco.h"

void detectAruco(std::string path, int aruco_ID)
{
    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_6X6_250);

    double fx, fy, cx, cy, k1, k2, k3, p1, p2;
    fx = 955.8925;
    fy = 955.4439;
    cx = 296.9006;
    cy = 215.9074;
    k1 = -0.1523;
    k2 = 0.7722;
    k3 = 0;
    p1 = 0;
    p2 = 0;

    int ID = aruco_ID;

    cv::Mat cameraMatrix = (cv::Mat_<float>(3, 3) << fx, 0.0, cx,
                            0.0, fy, cy,
                            0.0, 0.0, 1.0);
    cv::Mat distCoeffs = (cv::Mat_<float>(5, 1) << k1, k2, p1, p2, k3);

    cv::Mat image, imageCopy;
    image = cv::imread(path);
    image.copyTo(imageCopy);
    std::vector<int> ids, op_ids;                              // 储存结果id
    std::vector<std::vector<cv::Point2f>> corners, op_corners; // 储存结果位置
    cv::aruco::detectMarkers(image, dictionary, corners, ids); // 检测靶标
    // if at least one marker detected
    if (ids.size() > 0)
    {
        for (int t = 0; t < ids.size(); t++)
        {
            if (ids[t] == ID)
            {
                op_ids.push_back(ids[t]);
                op_corners.push_back(corners[t]);
            }
            // cout<<"ids"<<ids[t]<<endl;
        }
        if (op_ids.size() > 0)
        {
            cv::aruco::drawDetectedMarkers(imageCopy, op_corners, op_ids);                                   // 绘制检测到的靶标的框
            std::vector<cv::Vec3d> rvecs, tvecs;                                                             // 储存结果R/t
            cv::aruco::estimatePoseSingleMarkers(op_corners, 0.055, cameraMatrix, distCoeffs, rvecs, tvecs); // 求解旋转矩阵rvecs和平移矩阵tvecs
            std::cout << "R :" << rvecs[0] << std::endl;
            std::cout << "T :" << tvecs[0] << std::endl;
            // draw axis for each marker
            for (int i = 0; i < op_ids.size(); i++)
                cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1f); // 画出坐标轴
        }
        else
        {
            std::cout << "No Object Detected" << std::endl;
        }
    }
    cv::imshow("out", imageCopy);
    cv::waitKey(0);
}

void generate_Aruco()
{
    //创建aruco标记
    cv::Mat marker;
    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_6X6_250);
    for (int i = 0; i < 250; i++)
    {
        cv::aruco::drawMarker(dictionary, i, 200, marker, 1);
        std::string windowName = "marker" + std::to_string(i);
        std::string path = windowName + ".jpg";
        imwrite(path, marker);
    }
}