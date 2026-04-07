#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }

  Mat image;
  image = imread(argv[1], IMREAD_GRAYSCALE);

  if (!image.data) {
    printf("No image data \n");
    return -1;
  }
  // namedWindow("Display Image", WINDOW_NORMAL);
  // imshow("Display Image", image);

  int step = 2;
  int y = 0;

  std::ofstream myfile;
  myfile.open("example.txt");
  for (int j = 0; j <= image.rows; j += step) {
    for (int i = 0; i <= image.cols; i += step) {
      uchar intensity = image.at<uchar>(j, i);
      if (0 <= intensity && intensity < 50)
        myfile << "@";
      else if (50 <= intensity && intensity < 100)
        myfile << "#";
      else if (100 <= intensity && intensity < 150)
        myfile << "$";
      else if (150 <= intensity && intensity < 200)
        myfile << "%";
      else if (200 <= intensity && intensity < 250)
        myfile << "+";
      else if (250 <= intensity && intensity <= 255)
        myfile << "&";
    }
    myfile << '\n';
  }

  waitKey(0);

  return 0;
}