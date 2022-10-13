#ifndef _DETECTARUCO_H_
#define _DETECTARUCO_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/aruco/dictionary.hpp>

void detectAruco(std::string path,int aruco_ID);

#endif