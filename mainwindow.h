#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "opencv.hpp"
#include "features2d/features2d.hpp"
#include "core/core.hpp"
#include "nonfree/features2d.hpp"
#include "highgui/highgui.hpp"
#include "nonfree/nonfree.hpp"
#include <QDebug>
#include <string>
#include "stitch.h"
#include "opencv2/stitching/detail/blenders.hpp"
#include <QTextCodec>
#include "opencv2/imgproc/imgproc.hpp"
#include <Qlist>
#include <QCameraInfo>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Stitch(cv::Mat &temp);
    void StitchOvr(cv::Mat temp,cv::Mat &Output);
    void Fake_r(std::vector<cv::Mat> &temp,std::vector<cv::Mat> &fakeresult,std::vector<cv::Point> &displacement );
    //void Caculate_dxdy(int x, int y);
private slots:
    void on_StartButton_clicked();

    void on_pushButton_2_clicked();

    void on_closeButton_clicked();

    void on_LF1Button_clicked();

    void on_LF2Button_clicked();

    void on_LF3Button_clicked();

    void on_LF4Button_clicked();

    void on_Save1Button_clicked();

    void on_Save2Button_clicked();

    void on_Save3Button_clicked();

    void on_Save4Button_clicked();

    void on_LoadButton_clicked();

    void on_Merger_2Buttom_clicked();

    void on_horizontalSlider_frame1_sliderMoved(int position);

    void on_horizontalSlider_frame2_sliderMoved(int position);

    void on_horizontalSlider_frame3_sliderMoved(int position);

    void on_horizontalSlider_frame4_sliderMoved(int position);


    void on_Fake_Buttom_clicked();

    void on_ShowButton_clicked();


    void on_CalibrationButton_clicked();

    void on_CalButton_clicked();


    void on_pushButton_clicked();

    void on_RSlider1_sliderMoved(int position);

    void on_RSlider2_sliderMoved(int position);

    void on_RSlider3_sliderMoved(int position);

    void on_RSlider4_sliderMoved(int position);

    void on_Filter1_sliderMoved(int position);

    void on_Filter3_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    cv::Mat frame1;
    cv::Mat frame2;
    cv::Mat frame3;
    cv::Mat frame4;

    std::vector<cv::Mat> TWarp;  //單個的Warping Img

    std::vector<cv::Mat> FWarp;  //單個Fake在合成圖的區域

    std::vector<cv::Mat> FSWarp;

    std::vector<cv::Mat> FSCWarp;

    cv::Mat T1;
    cv::Mat T2;
    cv::Mat T3;
    cv::Mat T4;


    cv::Mat QTemp1;
    cv::Mat QTemp2;
    cv::Mat QTemp3;
    cv::Mat QTemp4;

    QImage img1;
    QImage img2;
    QImage img3;
    QImage img4;

    cv::Mat result;

    cv::Mat rImg;

    std::vector<cv::Ptr<cv::detail::Blender>> blender_2;
    std::vector<cv::Mat> dilate_mask;

    std::vector<cv::Mat> nodilate_warp;

    std::vector<cv::Point> displace;

};

#endif // MAINWINDOW_H
