#include <lccv.hpp>
#include <opencv2/opencv.hpp>
#include <unistd.h>

int main()
{
    std::cout<<"Sample program for LCCV video capture"<<std::endl;
    std::cout<<"Press ESC to stop."<<std::endl;
    cv::Mat cam_0_im, cam_1_im;
    lccv::PiCamera cam_0;
    cam_0.options->camera = 0;
    cam_0.options->video_width=1456;
    cam_0.options->video_height=1088;
    cam_0.options->framerate=60;
    cam_0.options->verbose=true;
    cv::namedWindow("Video",cv::WINDOW_NORMAL);
    cv::namedWindow("Video1", cv::WINDOW_NORMAL);
    cam_0.startVideo();
    std::cout << "Camera 0 Started" << std::endl;
    lccv::PiCamera cam_1;
    cam_1.options->camera = 1;
    cam_1.options->video_width=1456;
    cam_1.options->video_height=1088;
    cam_1.options->framerate=60;
    cam_1.options->verbose=true;

    cam_1.startVideo();
    int ch=0;
    int counter = 0;
    sleep(1);
    while(ch!=27){
        if(!cam_0.getVideoFrame(cam_0_im,99999999) || !cam_1.getVideoFrame(cam_1_im, 99999999)){
            std::cout<<"Timeout error " << counter <<std::endl;
            counter++;
        }
        else{
            cv::imshow("Video",cam_0_im);
            cv::imshow("Video1",cam_1_im);
            ch=cv::waitKey(10);
            counter = 0;
        }
    }
    cam_0.stopVideo();
    cv::destroyWindow("Video");
}
