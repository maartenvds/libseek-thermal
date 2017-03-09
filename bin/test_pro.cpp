/*
 *  Test program seek lib
 *  Author: Maarten Vandersteegen
 */
#include <opencv2/highgui/highgui.hpp>
#include "seek.h"
#include <iostream>

int main(int argc, char** argv)
{
    LibSeek::SeekThermalPro seek;
    cv::Mat frame, grey_frame, flat_field;

    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }

    flat_field = cv::imread("ffc.png", cv::ImreadModes::IMREAD_UNCHANGED);

    while(1) {
        if (!seek.grab()) {
            std::cout << "no more LWIR img" << endl;
            return -1;
        }

        seek.retrieve(frame);
        frame += 0x4000 - flat_field;
        //seek.convertToGreyScale(frame, grey_frame);
        cv::normalize(frame, grey_frame, 0, 65535, cv::NORM_MINMAX);
        cv::GaussianBlur(grey_frame, grey_frame, cv::Size(7,7), 0);

        cv::imshow("LWIR", grey_frame);

        char c = cv::waitKey(10);
        if (c == 's') {
            cv::waitKey(0);
        }
    }
}
