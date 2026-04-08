
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src, src_gray;

// src = src frame
// src_gray = src frame in gray
// dst=coloured final frame
// detected_edges = gray scale finall

Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio1 = 3;
const int kernel_size = 3;
const char *window_name = "Edge Map";
static void CannyThreshold(int, void *) {
  blur(src_gray, detected_edges, Size(3, 3));
  Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio1,
        kernel_size);
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
  // imshow(window_name, dst);
}
int main(int argc, char **argv) {
  // CommandLineParser parser(argc, argv, "{@input | fruits.jpg | input
  // image}"); src =
  // imread(samples::findFile(parser.get<String>("@input")),IMREAD_COLOR); //
  // Load an image
  //  if (src.empty()) {
  //    std::cout << "Could not open or find the image!\n" << std::endl;
  //    std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
  //    return -1;
  // }
  // dst.create(src.size(), src.type());
  // cvtColor(src, src_gray, COLOR_BGR2GRAY);
  // namedWindow(window_name, WINDOW_OPENGL);
  // createTrackbar("Min Threshold:", window_name, &lowThreshold,
  // max_lowThreshold,CannyThreshold);

  Mat frame;
  //--- INITIALIZE VIDEOCAPTURE
  string pipeline ="libcamerasrc ! video/x-raw, format=NV12, width=640, height=480, framerate=24/1! ""videoconvert ! video/x-raw, format=BGR ! appsink";
  VideoCapture cap(pipeline, cv::CAP_GSTREAMER);

  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;        // 0 = open default camera
  int apiID = cv::CAP_ANY; // 0 = autodetect default API
  // open selected camera using selected API
  cap.open(deviceID, apiID);
  // check if we succeeded
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open camera\n";
    return -1;
  }

  //--- GRAB AND WRITE LOOP
  cout << "Start grabbing" << endl << "Press any key to terminate" << endl;
 
  for (;;) {
    // wait for a new frame from camera and store it into 'frame'
    cap.read(frame);
    // check if we succeeded
    if (frame.empty()) {
      cerr << "ERROR! blank frame grabbed\n";
      break;
    }

    src = frame;
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    // namedWindow(window_name, WINDOW_OPENGL);

    CannyThreshold(0, 0);
    // show live and wait for a key with timeout long enough to show images

    imshow("Live", dst);
    createTrackbar("Min Threshold:", "Live", &lowThreshold, max_lowThreshold,
                   0);
    if (waitKey(5) >= 0)
      break;
  }

  waitKey(0);
  return 0;
}