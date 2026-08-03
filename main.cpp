#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat satellite_img = cv::imread("../satellite.png");
  if(satellite_img.empty()) {
      std::cerr << "위성 사진 불러들이기 실패!" << std::endl;
      return -1;
  }

  cv::imshow("img", satellite_img);
  cv::waitKey(0);

  return 1;
}
