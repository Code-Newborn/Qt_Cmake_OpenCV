#include "show.h"

void show()
{
    cv::Mat img = cv::imread("..\\lena.jpg");
    cv::imshow("IMAGE_TO_SHOW", img);
    

    int numfeature = 400;
    cv::Ptr<cv::SIFT> detector = cv::SIFT::create(numfeature);
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(img, keypoints, cv::Mat());
    printf("所有特征点数：%lld \n", keypoints.size());
    cv::Mat resultImg;
    cv::drawKeypoints(img, keypoints, resultImg, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", resultImg);

    cv::waitKey(0);
}