#include "../include/ar_tag_pad.h"

double src_marker_size = 18.0;
double output_marker_size = 24.0;
std::string src_image_path = "/home/aicrobo/tags";
int id_max = 50;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ar_tag_pad");
  ros::NodeHandle n;
  ROS_INFO("ar_tag_pad start!");

  n.getParam("/ar_tag_pad/src_marker_size", src_marker_size);
  n.getParam("/ar_tag_pad/output_marker_size", output_marker_size);
  n.getParam("/ar_tag_pad/src_image_path", src_image_path);
  n.getParam("/ar_tag_pad/id_max", id_max);

  if(output_marker_size < src_marker_size)
  {
    ROS_ERROR("output_marker_size < src_marker_size 参数错误！");
    return -1;
  }

  if(id_max < 1)
  {
    ROS_ERROR("id_max < 1 参数错误！");
    return -1;
  }

  for(int i=1; i<=id_max; i++)
  {
    std::string src_file = "MarkerData_" + std::to_string(i) + ".png";
    std::string src_path = src_image_path + "/" + src_file;
    cv::Mat src_image = cv::imread(src_path);
    cv::Mat output_iamge;

    int src_side = src_image.cols;
    int output_side = src_side * output_marker_size / src_marker_size;
    int pad_length = (output_side - src_side)/2;

    cv::copyMakeBorder(src_image,output_iamge,pad_length,pad_length,pad_length,pad_length,cv::BORDER_CONSTANT,cv::Scalar(255,255,255));
    cv::putText(output_iamge, std::to_string(i), cv::Point2f(pad_length/2, pad_length/2), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, CV_RGB(0,0,0), 2.0);

    std::string output_file = "/Pad_" + src_file;
    std::string output_path = src_image_path + output_file;
    cv::imwrite(output_path, output_iamge);
    ROS_INFO("ar tag file: %s, size: %f cm", output_file.c_str(), output_marker_size);
//      cv::imshow("output_iamge", output_iamge);
//      cv::waitKey(0);
  }

  return 0;
}
