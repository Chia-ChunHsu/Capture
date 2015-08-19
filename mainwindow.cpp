#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(ui->closeButton->isChecked()== true)
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    //The Information of the QCameraInfo : http://doc.qt.io/qt-5/qcamerainfo.html
    //fit the correct Camera
    int DeviceID[4]={-1,-1,-1,-1};
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    int size = 0;
    QString VideoName0 = "@device:pnp:\\\\?\\usb#vid_05ac&pid_8507&mi_02#7&cb29abf&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global";
    QString VideoName1 = "@device:pnp:\\\\?\\usb#vid_05ac&pid_8507&mi_02#7&3225fc09&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global";
    QString VideoName2 = "@device:pnp:\\\\?\\usb#vid_05ac&pid_8507&mi_02#7&60715e6&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global";
    QString VideoName3 = "@device:pnp:\\\\?\\usb#vid_05ac&pid_8507&mi_02#7&2b7a7730&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global";
    //QString VideoName3 = "@device:pnp:\\\\?\\usb#vid_05ac&pid_8507&mi_02#7&2b7a7730&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global

    foreach (const QCameraInfo &cameraInfo, cameras) {
        qDebug()<<cameraInfo.deviceName();
        if(cameraInfo.deviceName() == VideoName0)
        {
            DeviceID[0] = size;
        }
        else if(cameraInfo.deviceName() == VideoName1)
        {
            DeviceID[1] = size;
        }
        else if(cameraInfo.deviceName() == VideoName2)
        {
            DeviceID[2] = size;
        }
        else if(cameraInfo.deviceName() == VideoName3)
        {
            DeviceID[3] = size;
        }
        size++;
    }
    qDebug()<<size;



    //const std::string video0 = "USB\VID_05AC&PID_8507\6&29250CCB&0&4";

    qDebug()<<DeviceID[0];
    qDebug()<<DeviceID[1];
    qDebug()<<DeviceID[2];
    qDebug()<<DeviceID[3];

    cv::VideoCapture cap1(DeviceID[0]);
    cv::VideoCapture cap2(DeviceID[1]);

    cap1.set(CV_CAP_PROP_BRIGHTNESS,160);
    cap2.set(CV_CAP_PROP_BRIGHTNESS,160);
    cap1.set(CV_CAP_PROP_CONTRAST,165);
    cap2.set(CV_CAP_PROP_CONTRAST,165);
    cap1.set(CV_CAP_PROP_SATURATION,125);
    cap2.set(CV_CAP_PROP_SATURATION,125);


    if(!cap1.isOpened() || !cap2.isOpened())
        return;


    for(int i = 0; i< 100;i++)
    {
        cap1>>frame1;
        cap2>>frame2;
        cv::waitKey(100);
    }
    cap1.release();
    cap2.release();

    //    cv::imshow("1",frame1);
    //    cv::imshow("2",frame2);

    cv::VideoCapture cap3(DeviceID[2]);
    cv::VideoCapture cap4(DeviceID[3]);

    cap3.set(CV_CAP_PROP_BRIGHTNESS,160);
    cap4.set(CV_CAP_PROP_BRIGHTNESS,160);
    cap3.set(CV_CAP_PROP_CONTRAST,165);
    cap4.set(CV_CAP_PROP_CONTRAST,165);
    cap3.set(CV_CAP_PROP_SATURATION,125);
    cap4.set(CV_CAP_PROP_SATURATION,125);


    if(!cap3.isOpened() || !cap4.isOpened())
        return;
    for(int i = 0; i< 100;i++)
    {
        cap3>>frame3;
        cap4>>frame4;
        cv::waitKey(100);
    }
    cap3.release();
    cap4.release();


    QTemp1 = frame1.clone();
    QTemp2 = frame2.clone();
    QTemp3 = frame3.clone();
    QTemp4 = frame4.clone();

    img1 = QImage((const unsigned char*)(frame1.data),frame1.cols,frame1.rows,frame1.step,QImage::Format_RGB888);
    img2 = QImage((const unsigned char*)(frame2.data),frame2.cols,frame1.rows,frame2.step,QImage::Format_RGB888);
    img3 = QImage((const unsigned char*)(frame3.data),frame3.cols,frame1.rows,frame3.step,QImage::Format_RGB888);
    img4 = QImage((const unsigned char*)(frame4.data),frame4.cols,frame1.rows,frame4.step,QImage::Format_RGB888);


    ui->label1->clear();
    ui->label1->setPixmap(QPixmap::fromImage(img1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    ui->label1->resize(ui->label1->pixmap()->size());
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(img2.scaled(ui->label2->width(),ui->label2->height(),Qt::KeepAspectRatio)));
    ui->label3->clear();
    ui->label3->setPixmap(QPixmap::fromImage(img3.scaled(ui->label3->width(),ui->label3->height(),Qt::KeepAspectRatio)));
    ui->label4->clear();
    ui->label4->setPixmap(QPixmap::fromImage(img4.scaled(ui->label4->width(),ui->label4->height(),Qt::KeepAspectRatio)));
    ui->label1->show();
    ui->label2->show();
    ui->label3->show();
    ui->label4->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    cv::Mat first;
    cv::Size size(frame1.cols*2,frame1.rows*2);
    result.create(size,CV_MAKETYPE(first.depth(),3));
    result = cv::Scalar::all(0);

    for(int i=0;i<frame1.rows;i++)
    {
        for(int j=0;j<frame1.cols;j++)
        {
            result.at<cv::Vec3b>(i+frame1.rows/4, j+frame1.cols/4)[0] = frame1.at<cv::Vec3b>(i,j)[0];
            result.at<cv::Vec3b>(i+frame1.rows/4, j+frame1.cols/4)[1] = frame1.at<cv::Vec3b>(i,j)[1];
            result.at<cv::Vec3b>(i+frame1.rows/4, j+frame1.cols/4)[2] = frame1.at<cv::Vec3b>(i,j)[2];
        }
    }

    //qDebug()<<"x = "<<frame1.cols<<" y = "<<frame1.rows;

//    Stitch(frame2);
//    Stitch(frame3);
//    Stitch(frame4);
    T1 = QTemp1.clone();
    T2 = QTemp2.clone();
    T3 = QTemp3.clone();
    T4 = QTemp4.clone();
    StitchOvr(frame2,T2);
    StitchOvr(frame3,T3);
    StitchOvr(frame4,T4);

    cv::imshow("T1",T1);
    cv::imshow("T2",T2);
    cv::imshow("T3",T3);
    cv::imshow("T4",T4);
}

void MainWindow::StitchOvr(cv::Mat temp,cv::Mat& Output)
{
    int minHessian = 400;
    cv::SiftFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints1,keypoints2;

    detector.detect(frame1,keypoints1);
    detector.detect(temp,keypoints2);

    cv::SiftDescriptorExtractor extractor;

    cv::Mat descriptors_1,descriptors_2;

    extractor.compute(frame1,keypoints1,descriptors_1);
    extractor.compute(temp,keypoints2,descriptors_2);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors_1,descriptors_2,matches);

    double max = 0;
    double min = 100;

    for(int i = 0;i<descriptors_1.rows;i++)
    {
        double dist = matches[i].distance;
        if(dist <min)  min = dist;
        if(dist >max)  max = dist;
    }

    int x = 0;
    int y = 0;
    int total = 0;
    std::vector<cv::DMatch> good_matches;
    qDebug()<<"456"<<frame1.rows<<frame1.cols;
    for(int i = 0;i<descriptors_1.rows;i++)
    {
        if( matches[i].distance <= std::max(2*min,0.02))
        {
            good_matches.push_back(matches[i]);
            x = x + (keypoints1[matches[i].queryIdx].pt.x - keypoints2[matches[i].trainIdx].pt.x);
            y = y + (keypoints1[matches[i].queryIdx].pt.y - keypoints2[matches[i].trainIdx].pt.y);
            total++;
        }
    }

//    x = x/descriptors_1.rows;
//    y = y/descriptors_1.rows;
    x = x/total;
    y = y/total;

    qDebug()<< x <<" "<< y;
    if(x >=0 && y>= 0)  // 圖片在原圖的右上方
    {
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }
                else
                {
                    if(result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0]> 160 && temp.at<cv::Vec3b>(i,j)[0] > 160 && result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1]> 160 && temp.at<cv::Vec3b>(i,j)[1] > 160  &&result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2]> 160 && temp.at<cv::Vec3b>(i,j)[2] > 160)
                    {
                        if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< frame1.cols )
                        {
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0]=255;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1]=0;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2]=0;
                            Output.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0]=255;
                            Output.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1]=0;
                            Output.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2]=0;
                        }

                    }
                }

            }
        }
    }
    else if(x>=0 && y<0)   //右下方
    {
        qDebug()<<"Hererd";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j-x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j-x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j-x)[2] == 0)
                {
                    if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < 2*frame1.rows && frame1.cols/4+j-x >= 0 && frame1.cols/4+j-x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }
                else
                {
                    if(result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[0]> 160 && temp.at<cv::Vec3b>(i,j)[0] > 160  && result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[1]> 160 && temp.at<cv::Vec3b>(i,j)[1] > 160  &&result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j-x)[2]> 160 && temp.at<cv::Vec3b>(i,j)[2]> 160)
                    {
                        if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < frame1.rows && frame1.cols/4+j-x >= 0 && frame1.cols/4+j-x< frame1.cols )
                        {
                            Output.at<cv::Vec3b>(i,j)[0]=255;
                            Output.at<cv::Vec3b>(i,j)[1]=0;
                            Output.at<cv::Vec3b>(i,j)[2]=0;
                        }
                        if(i-y >= 0 &&i-y < frame1.rows && j-x >= 0 && j-x< frame1.cols)
                        {
                            T1.at<cv::Vec3b>(i-y, j-x)[0]=255;
                            T1.at<cv::Vec3b>(i-y, j-x)[1]=0;
                            T1.at<cv::Vec3b>(i-y, j-x)[2]=0;
                        }

                    }
                }

            }
        }
    }
    else if(x<0 && y<0)  //左下方
    {
        qDebug()<<"Hereld";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i-y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }
                else
                {
                    if(result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0]> 160 && temp.at<cv::Vec3b>(i,j)[0] > 160  && result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1]> 160 && temp.at<cv::Vec3b>(i,j)[1] > 160  &&result.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2]> 160 && temp.at<cv::Vec3b>(i,j)[2]> 160)
                    {
                        if(frame1.rows/4+i-y >= 0 &&frame1.rows/4+i-y < frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< frame1.cols )
                        {
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[0]=255;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[1]=0;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i-y, frame1.cols/4+j+x)[2]=0;
                            Output.at<cv::Vec3b>(i,j)[0]=255;
                            Output.at<cv::Vec3b>(i,j)[1]=0;
                            Output.at<cv::Vec3b>(i,j)[2]=0;
                        }
                    }
                }

            }
        }
    }
    else if(x<0 && y>=0) //左上方
    {
        qDebug()<<"Herelu";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }
                else
                {
                    if(result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0]> 160 && temp.at<cv::Vec3b>(i,j)[0] > 160  && result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1]> 160 && temp.at<cv::Vec3b>(i,j)[1] > 160  &&result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2]> 160 && temp.at<cv::Vec3b>(i,j)[2] > 160)
                    {
                        if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                        {
//                            T1.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0]=255;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1]=0;
//                            T1.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2]=0;
                            Output.at<cv::Vec3b>(i,j)[0]=255;
                            Output.at<cv::Vec3b>(i,j)[1]=0;
                            Output.at<cv::Vec3b>(i,j)[2]=0;
                        }
                    }
                }

            }
        }
    }
//    cv::imshow("result",result);
//        ui->label1->clear();
//        ui->label1->setPixmap(QPixmap::fromImage(img1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    QImage imgResult = QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_RGB888);

    ui->labelresult->clear();
    ui->labelresult->setPixmap(QPixmap::fromImage(imgResult.scaled(ui->labelresult->width(),ui->labelresult->height(),Qt::KeepAspectRatio)));
    ui->labelresult->show();
}


void MainWindow::Stitch(cv::Mat &temp)
{
    int minHessian = 400;
    cv::SiftFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints1,keypoints2;

    detector.detect(frame1,keypoints1);
    detector.detect(temp,keypoints2);

    cv::SiftDescriptorExtractor extractor;

    cv::Mat descriptors_1,descriptors_2;

    extractor.compute(frame1,keypoints1,descriptors_1);
    extractor.compute(temp,keypoints2,descriptors_2);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors_1,descriptors_2,matches);

    double max = 0;
    double min = 100;

    for(int i = 0;i<descriptors_1.rows;i++)
    {
        double dist = matches[i].distance;
        if(dist <min)  min = dist;
        if(dist >max)  max = dist;
    }

    int x = 0;
    int y = 0;
    int total = 0;
    std::vector<cv::DMatch> good_matches;
    qDebug()<<"456";
    for(int i = 0;i<descriptors_1.rows;i++)
    {
        if( matches[i].distance <= std::max(2*min,0.02))
        {
            good_matches.push_back(matches[i]);
            x = x + (keypoints1[matches[i].queryIdx].pt.x - keypoints2[matches[i].trainIdx].pt.x);
            y = y + (keypoints1[matches[i].queryIdx].pt.y - keypoints2[matches[i].trainIdx].pt.y);
            total++;
        }
    }

//    x = x/descriptors_1.rows;
//    y = y/descriptors_1.rows;
    x = x/total;
    y = y/total;

    qDebug()<< x <<" "<< y;
    if(x >0 && y> 0)  // 圖片在原圖的右上方
    {
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }

            }
        }
    }
    else if(x>0 && y<0)   //右下方
    {
        qDebug()<<"Hererd";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }

            }
        }
    }
    else if(x<0 && y<0)  //左下方
    {
        qDebug()<<"Hereld";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j-x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j-x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j-x)[2] == 0)
                {
                    if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j-x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j-x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j-x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }

            }
        }
    }
    else if(x<0 && y>0) //左上方
    {
        qDebug()<<"Herelu";
        for(int i=0;i<temp.rows;i++)
        {
            for(int j=0;j<temp.cols;j++)
            {

                if(result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[0] == 0  && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[1] == 0 && result.at<cv::Vec3b>(frame1.rows/4+i+y,frame1.cols/4+j+x)[2] == 0)
                {
                    if(frame1.rows/4+i+y >= 0 &&frame1.rows/4+i+y < 2*frame1.rows && frame1.cols/4+j+x >= 0 && frame1.cols/4+j+x< 2*frame1.cols )
                    {
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[0] = temp.at<cv::Vec3b>(i,j)[0];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[1] = temp.at<cv::Vec3b>(i,j)[1];
                        result.at<cv::Vec3b>(frame1.rows/4+i+y, frame1.cols/4+j+x)[2] = temp.at<cv::Vec3b>(i,j)[2];
                    }
                }

            }
        }
    }
//    cv::imshow("result",result);
//        ui->label1->clear();
//        ui->label1->setPixmap(QPixmap::fromImage(img1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    QImage imgResult = QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_RGB888);
    ui->labelresult->clear();
    ui->labelresult->setPixmap(QPixmap::fromImage(imgResult.scaled(ui->labelresult->width(),ui->labelresult->height(),Qt::KeepAspectRatio)));
    ui->labelresult->show();
}

void MainWindow::on_closeButton_clicked()
{

    close();
}

void MainWindow::on_LF1Button_clicked()
{
    cv::VideoCapture cap1(0);

    if(!cap1.isOpened())
        return;
    //    if(!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened())
    //        return;
    for(int i = 0; i< 10;i++)
    {
        cap1>>frame1;
        cv::waitKey(100);
    }
    cap1.release();

    img1 = QImage((const unsigned char*)(frame1.data),frame1.cols,frame1.rows,QImage::Format_RGB888);


    ui->label1->clear();
    ui->label1->setPixmap(QPixmap::fromImage(img1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    ui->label1->show();
}

void MainWindow::on_LF2Button_clicked()
{
    cv::VideoCapture cap1(0);

    if(!cap1.isOpened())
        return;
    //    if(!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened())
    //        return;
    for(int i = 0; i< 10;i++)
    {
        cap1>>frame2;
        cv::waitKey(100);
    }
    cap1.release();
    img2 = QImage((const unsigned char*)(frame2.data),frame2.cols,frame1.rows,QImage::Format_RGB888);



    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(img2.scaled(ui->label2->width(),ui->label2->height(),Qt::KeepAspectRatio)));
    ui->label2->show();
}

void MainWindow::on_LF3Button_clicked()
{
    cv::VideoCapture cap1(0);

    if(!cap1.isOpened())
        return;
    //    if(!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened())
    //        return;
    for(int i = 0; i< 10;i++)
    {
        cap1>>frame3;
        cv::waitKey(100);
    }
    cap1.release();


    img3 = QImage((const unsigned char*)(frame3.data),frame3.cols,frame1.rows,QImage::Format_RGB888);



    ui->label3->clear();
    ui->label3->setPixmap(QPixmap::fromImage(img3.scaled(ui->label3->width(),ui->label3->height(),Qt::KeepAspectRatio)));
}

void MainWindow::on_LF4Button_clicked()
{
    cv::VideoCapture cap1(0);

    if(!cap1.isOpened())
        return;
    //    if(!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened())
    //        return;
    for(int i = 0; i< 10;i++)
    {
        cap1>>frame4;
        cv::waitKey(100);
    }
    cap1.release();

    img4 = QImage((const unsigned char*)(frame4.data),frame4.cols,frame1.rows,QImage::Format_RGB888);


    ui->label4->clear();
    ui->label4->setPixmap(QPixmap::fromImage(img4.scaled(ui->label4->width(),ui->label4->height(),Qt::KeepAspectRatio)));
    ui->label4->show();
}

void MainWindow::on_Save1Button_clicked()
{
    cv::Mat gray_image;
    cv::cvtColor(frame1,gray_image,CV_BGR2GRAY);
    cv::imwrite("frame1.jpg",gray_image);
}

void MainWindow::on_Save2Button_clicked()
{
    cv::Mat gray_image;
    cv::cvtColor(frame2,gray_image,CV_BGR2GRAY);
    cv::imwrite("frame2.jpg",gray_image);
}

void MainWindow::on_Save3Button_clicked()
{
    cv::Mat gray_image;
    cv::cvtColor(frame3,gray_image,CV_BGR2GRAY);
    cv::imwrite("frame3.jpg",gray_image);
}

void MainWindow::on_Save4Button_clicked()
{
    cv::Mat gray_image;
    cv::cvtColor(frame4,gray_image,CV_BGR2GRAY);
    cv::imwrite("frame4.jpg",gray_image);
}

void MainWindow::on_LoadButton_clicked()
{
    std::string img1Name("frame1.jpg");
    frame1 = cv::imread(img1Name.c_str(),cv::IMREAD_COLOR);
    std::string img2Name("frame2.jpg");
    frame2 = cv::imread(img2Name.c_str(),cv::IMREAD_COLOR);
    std::string img3Name("frame3.jpg");
    frame3 = cv::imread(img3Name.c_str(),cv::IMREAD_COLOR);
    std::string img4Name("frame4.jpg");
    frame4 = cv::imread(img4Name.c_str(),cv::IMREAD_COLOR);

    img1 = QImage((const unsigned char*)(frame1.data),frame1.cols,frame1.rows,QImage::Format_RGB888);
    img2 = QImage((const unsigned char*)(frame2.data),frame2.cols,frame1.rows,QImage::Format_RGB888);
    img3 = QImage((const unsigned char*)(frame3.data),frame3.cols,frame1.rows,QImage::Format_RGB888);
    img4 = QImage((const unsigned char*)(frame4.data),frame4.cols,frame1.rows,QImage::Format_RGB888);

    QTemp1 = frame1.clone();
    QTemp2 = frame2.clone();
    QTemp3 = frame3.clone();
    QTemp4 = frame4.clone();

    ui->label1->clear();
    ui->label1->setPixmap(QPixmap::fromImage(img1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    ui->label1->show();
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(img2.scaled(ui->label2->width(),ui->label2->height(),Qt::KeepAspectRatio)));
    ui->label2->show();
    ui->label3->clear();
    ui->label3->setPixmap(QPixmap::fromImage(img3.scaled(ui->label3->width(),ui->label3->height(),Qt::KeepAspectRatio)));
    ui->label3->show();
    ui->label4->clear();
    ui->label4->setPixmap(QPixmap::fromImage(img4.scaled(ui->label4->width(),ui->label4->height(),Qt::KeepAspectRatio)));
    ui->label4->show();
}

void MainWindow::on_Merger_2Buttom_clicked()
{
     TWarp.clear();
     std::vector< cv::Mat > vImg;
     std::vector< cv::Mat > img_warp;
     //std::vector< cv::Mat > mask_warp;
     //std::vector<cv::Ptr<cv::detail::Blender>> blender;

     //cv::Mat fakeImg;

     vImg.push_back(QTemp1);
     vImg.push_back(QTemp2);
     vImg.push_back(QTemp3);
     vImg.push_back(QTemp4);

     //std::vector<cv::Mat> nodilate_warp;


     cv::Stitch stitcher = cv::Stitch::createDefault();
     qDebug()<<"0";
     ui->progressBar_Merge->setValue(5);
     cv::Stitch::Status status;

     status = stitcher.stitch2(vImg,vImg ,rImg,img_warp,nodilate_warp,dilate_mask,1,ConrnerPoint);

     ui->progressBar_Merge->setValue(25);
     qDebug()<<"1";

     do
     {
         qDebug()<<"2";
         if (cv::Stitch::OK == status)
         {
             cv::imwrite("result.jpg",rImg);
             QImage imgResult = QImage((const unsigned char*)(rImg.data),rImg.cols,rImg.rows,rImg.step,QImage::Format_RGB888);
             ui->labelresult->clear();
             ui->labelresult->setPixmap(QPixmap::fromImage(imgResult.scaled(ui->labelresult->width(),ui->labelresult->height(),Qt::KeepAspectRatio)));
             ui->labelresult->show();
         }
         else
         {
             status = stitcher.stitch2(vImg, vImg,rImg,img_warp,nodilate_warp,dilate_mask,1,ConrnerPoint);
             qDebug()<<"Stitching fail.";
         }
     }while(cv::Stitch::OK != status);
    qDebug()<<"Size "<<img_warp.size();

    cv::Mat resultTemp;

    ui->progressBar_Merge->setValue(75);

    for(int i = 0;i<img_warp.size();i++)
    {
        resultTemp = cv::Mat(img_warp[i].rows,img_warp[i].cols,CV_8UC3);
        for(int b = 0 ; b<img_warp[i].rows;b++)
        {
            for(int a = 0; a<img_warp[i].cols;a++)
            {
                //qDebug()<<mask_warp[i].at<uchar>(b,a);
                if(nodilate_warp[i].at<uchar>(b,a) == 255)
                {
                    resultTemp.at<cv::Vec3b>(b, a)[0] = img_warp[i].at<cv::Vec3b>(b,a)[0];
                    resultTemp.at<cv::Vec3b>(b, a)[1] = img_warp[i].at<cv::Vec3b>(b,a)[1];
                    resultTemp.at<cv::Vec3b>(b, a)[2] = img_warp[i].at<cv::Vec3b>(b,a)[2];

                }
                else
                {
                    resultTemp.at<cv::Vec3b>(b, a)[0] = 0;
                    resultTemp.at<cv::Vec3b>(b, a)[1] = 0;
                    resultTemp.at<cv::Vec3b>(b, a)[2] = 0;
                }
                //qDebug()<<i;
            }
        }
        //cv::imshow(QString::number(i).toStdString()+"result",resultTemp);
        TWarp.push_back(resultTemp);
        //cv::waitKey(0);
    }
    ui->labelwarp1->clear();
    ui->labelwarp2->clear();
    ui->labelwarp3->clear();
    ui->labelwarp4->clear();

//    for(int i=0;i<TWarp.size();i++)
//    {
//        cv::imshow(QString::number(i).toStdString(),TWarp[i]);
//    }
    ui->progressBar_Merge->setValue(95);
    QImage wimg1 = QImage((const unsigned char*)(TWarp[0].data),TWarp[0].cols,TWarp[0].rows,TWarp[0].step,QImage::Format_RGB888);
    QImage wimg2 = QImage((const unsigned char*)(TWarp[1].data),TWarp[1].cols,TWarp[1].rows,TWarp[1].step,QImage::Format_RGB888);
    QImage wimg3 = QImage((const unsigned char*)(TWarp[2].data),TWarp[2].cols,TWarp[2].rows,TWarp[2].step,QImage::Format_RGB888);
    QImage wimg4 = QImage((const unsigned char*)(TWarp[3].data),TWarp[3].cols,TWarp[3].rows,TWarp[3].step,QImage::Format_RGB888);
    //imgResult.scaled(ui->labelresult->width(),ui->labelresult->height(),Qt::KeepAspectRatio)
    ui->labelwarp1->setPixmap(QPixmap::fromImage(wimg1.scaled(ui->labelwarp1->width(),ui->labelwarp1->height(),Qt::KeepAspectRatio)));
    ui->labelwarp1->show();

    ui->labelwarp2->setPixmap(QPixmap::fromImage(wimg2.scaled(ui->labelwarp2->width(),ui->labelwarp2->height(),Qt::KeepAspectRatio)));
    ui->labelwarp2->show();

    ui->labelwarp3->setPixmap(QPixmap::fromImage(wimg3.scaled(ui->labelwarp3->width(),ui->labelwarp3->height(),Qt::KeepAspectRatio)));
    ui->labelwarp3->show();

    ui->labelwarp4->setPixmap(QPixmap::fromImage(wimg4.scaled(ui->labelwarp4->width(),ui->labelwarp4->height(),Qt::KeepAspectRatio)));
    ui->labelwarp4->show();
    ui->progressBar_Merge->setValue(100);
}


void MainWindow::on_horizontalSlider_frame1_sliderMoved(int position)
{
    QTemp1 = frame1.clone();
    for(int i = 0;i<frame1.cols;i++)
    {
        for(int j=0;j<frame1.rows;j++)
        {
            double pix =(frame1.at<cv::Vec3b>(j, i)[0]+frame1.at<cv::Vec3b>(j, i)[1]+frame1.at<cv::Vec3b>(j, i)[2])/3;
            if(pix<position)
            {
                QTemp1.at<cv::Vec3b>(j,i)[0] = 0;
                QTemp1.at<cv::Vec3b>(j,i)[1] = 0;
                QTemp1.at<cv::Vec3b>(j,i)[2] = 0;
            }
        }
    }
    QImage qimage1=QImage((const unsigned char*)QTemp1.data,QTemp1.cols,QTemp1.rows,QTemp1.step,QImage::Format_RGB888);
    ui->label1->clear();
    ui->label1->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->label1->width(),ui->label1->height(),Qt::KeepAspectRatio)));
    ui->label1->show();
}

void MainWindow::on_horizontalSlider_frame2_sliderMoved(int position)
{
    QTemp2 = frame2.clone();
    for(int i = 0;i<frame2.cols;i++)
    {
        for(int j=0;j<frame2.rows;j++)
        {
            double pix =(frame2.at<cv::Vec3b>(j, i)[0]+frame2.at<cv::Vec3b>(j, i)[1]+frame2.at<cv::Vec3b>(j, i)[2])/3;
            if(pix<position)
            {
                QTemp2.at<cv::Vec3b>(j,i)[0] = 0;
                QTemp2.at<cv::Vec3b>(j,i)[1] = 0;
                QTemp2.at<cv::Vec3b>(j,i)[2] = 0;
            }
        }
    }
    QImage qimage2=QImage((const unsigned char*)QTemp2.data,QTemp2.cols,QTemp2.rows,QTemp2.step,QImage::Format_RGB888);
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(qimage2.scaled(ui->label2->width(),ui->label2->height(),Qt::KeepAspectRatio)));
    ui->label2->show();

}

void MainWindow::on_horizontalSlider_frame3_sliderMoved(int position)
{
    QTemp3 = frame3.clone();
    for(int i = 0;i<frame3.cols;i++)
    {
        for(int j=0;j<frame3.rows;j++)
        {
            double pix =(frame3.at<cv::Vec3b>(j, i)[0]+frame3.at<cv::Vec3b>(j, i)[1]+frame3.at<cv::Vec3b>(j, i)[2])/3;
            if(pix<position)
            {
                QTemp3.at<cv::Vec3b>(j,i)[0] = 0;
                QTemp3.at<cv::Vec3b>(j,i)[1] = 0;
                QTemp3.at<cv::Vec3b>(j,i)[2] = 0;
            }
        }
    }
    QImage qimage3=QImage((const unsigned char*)QTemp3.data,QTemp3.cols,QTemp3.rows,QTemp3.step,QImage::Format_RGB888);
    ui->label3->clear();
    ui->label3->setPixmap(QPixmap::fromImage(qimage3.scaled(ui->label3->width(),ui->label3->height(),Qt::KeepAspectRatio)));
    ui->label3->show();
}

void MainWindow::on_horizontalSlider_frame4_sliderMoved(int position)
{
    QTemp4 = frame4.clone();
    for(int i = 0;i<frame4.cols;i++)
    {
        for(int j=0;j<frame4.rows;j++)
        {
            double pix =(frame4.at<cv::Vec3b>(j, i)[0]+frame4.at<cv::Vec3b>(j, i)[1]+frame4.at<cv::Vec3b>(j, i)[2])/3;
            if(pix<position)
            {
                QTemp4.at<cv::Vec3b>(j,i)[0] = 0;
                QTemp4.at<cv::Vec3b>(j,i)[1] = 0;
                QTemp4.at<cv::Vec3b>(j,i)[2] = 0;
            }
        }
    }
    QImage qimage4=QImage((const unsigned char*)QTemp4.data,QTemp4.cols,QTemp4.rows,QTemp4.step,QImage::Format_RGB888);
    ui->label4->clear();
    ui->label4->setPixmap(QPixmap::fromImage(qimage4.scaled(ui->label4->width(),ui->label4->height(),Qt::KeepAspectRatio)));
    ui->label4->show();
}






void MainWindow::on_Fake_Buttom_clicked()
{
    std::vector<cv::Mat> fakeresult;
    displace.clear();
    //std::vector<cv::Point> displace;
    std::vector<cv::Mat> TempWarp;
    TempWarp.push_back(TWarp[0]);
    TempWarp.push_back(TWarp[1]);
    TempWarp.push_back(TWarp[2]);
    TempWarp.push_back(TWarp[3]);
    qDebug()<<"*********************";
    Fake_r(TempWarp,fakeresult,displace);


}

void MainWindow::Fake_r(std::vector<cv::Mat> &temp,std::vector<cv::Mat> &fakeresult,std::vector<cv::Point> &displacement)
{
    int minHessian = 400;
    cv::SiftFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints1,keypoints2;

    for(int number=0;number<temp.size();number++)
    {
        detector.detect(rImg,keypoints1);
        detector.detect(temp[number],keypoints2);

        cv::SiftDescriptorExtractor extractor;

        cv::Mat descriptors_1,descriptors_2;

        extractor.compute(rImg,keypoints1,descriptors_1);
        extractor.compute(temp[number],keypoints2,descriptors_2);

        cv::FlannBasedMatcher matcher;
        std::vector<cv::DMatch> matches;
        matcher.match(descriptors_1,descriptors_2,matches);

        double max = 0;
        double min = 100;

        for(int i = 0;i<descriptors_1.rows;i++)
        {
            double dist = matches[i].distance;
            if(dist <min)  min = dist;
            if(dist >max)  max = dist;
        }

        int x = 0;
        int y = 0;
        int total = 0;
        std::vector<cv::DMatch> good_matches;
        //qDebug()<<"456"<<rImg.rows<<rImg.cols;

        cv::Mat tempresult;
        cv::Size size(rImg.cols,rImg.rows);
        tempresult.create(size,CV_MAKETYPE(rImg.depth(),3));
        tempresult = rImg.clone();
        //cv::tempResult;
        std::vector<cv::KeyPoint> keypoints;
        //std::vector<cv::DMatch> gmatches;
        for(int i = 0;i<descriptors_1.rows;i++)
        {
            if( matches[i].distance <= std::max(2*min,0.02))
            {
                good_matches.push_back(matches[i]);
                x = x + (keypoints1[matches[i].queryIdx].pt.x - keypoints2[matches[i].trainIdx].pt.x);
                y = y + (keypoints1[matches[i].queryIdx].pt.y - keypoints2[matches[i].trainIdx].pt.y);
                total++;
                keypoints.push_back(keypoints1[matches[i].queryIdx]);
            }
        }
        x = x/total;
        y = y/total;

        cv::Mat good;
        qDebug()<<x<<y;

        cv::drawMatches(rImg,keypoints1,temp[number],keypoints2,good_matches,good,cv::Scalar::all(-1),cv::Scalar::all(-1),cv::vector<char>(),cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        cv::circle(good,cv::Point(x,y),5,cv::Scalar(0,0,255));
        cv::imshow("good"+QString::number(number).toStdString(),good);
        fakeresult.push_back(good);
        cv::Point p = cv::Point(x,y);
        displacement.push_back(p);
    }
}

void MainWindow::on_ShowButton_clicked()
{
    qDebug()<<"showButtom Clicked";
    cv::Mat temp;
    qDebug()<<FSWarp.size() << displace.size();
    //cv::Mat rImgTemp;
    //cv::cvtColor(rImgTemp,rImg,CV_GRAY2BGR);
    cv::Size size(rImg.cols,rImg.rows);
    temp.create(size,CV_MAKETYPE(temp.type(),3));
    temp = cv::Scalar::all(0);
    qDebug()<<FWarp[0].cols<<FWarp[0].rows<<rImg.channels()<<temp.channels()<<FWarp[0].channels()<<FWarp[1].channels()<<FWarp[2].channels()<<FWarp[3].channels();
    qDebug()<<"123123123123";
//    for(int i=0;i<FWarp.size();i++)
//    {
//        cv::imshow(QString::number(i).toStdString(),FWarp[i]);
//    }
    for(int number=0;number<FSWarp.size();number++)
    {
        qDebug()<<number;
        for(int i = 0;i<FSWarp[number].cols;i++)
        {
            for(int j=0;j<FSWarp[number].rows;j++)
            {
                //qDebug()<<j<<i;
                //qDebug()<<"0";
                int x = displace[number].x;
                int y = displace[number].y;
                if((FSCWarp[number].at<cv::Vec3b>(j,i)[0]+FSCWarp[number].at<cv::Vec3b>(j,i)[1]+FSCWarp[number].at<cv::Vec3b>(j,i)[2])/3 >250)
                {
                    if(j+y<rImg.rows && i+x<rImg.cols && j+y>=0 && i+x>=0)
                    {
                        temp.at<cv::Vec3b>(j+y,i+x)[0] = 255;
                        temp.at<cv::Vec3b>(j+y,i+x)[1] = 255;
                        temp.at<cv::Vec3b>(j+y,i+x)[2] = 255;
                    }
                }
            }
        }
    }
    cv::imshow("test",temp);

}



void MainWindow::on_CalibrationButton_clicked()
{
    qDebug()<<"Start!! ";
    FWarp.clear();
    std::vector< cv::Mat > vImg;
    std::vector< cv::Mat > img_warp;
    std::vector< cv::Mat > vImg2;
    std::vector< cv::Mat > img_warp2;
    //std::vector< cv::Mat > mask_warp;
    //std::vector<cv::Ptr<cv::detail::Blender>> blender;

    //cv::Mat fakeImg;

    vImg.push_back(frame1);
    vImg.push_back(frame2);
    vImg.push_back(frame3);
    vImg.push_back(frame4);

    vImg2.push_back(QTemp1);
    vImg2.push_back(QTemp2);
    vImg2.push_back(QTemp3);
    vImg2.push_back(QTemp4);

    //std::vector<cv::Mat> nodilate_warp;


    cv::Stitch stitcher = cv::Stitch::createDefault();
    qDebug()<<"0";
    ui->progressBar_Merge->setValue(5);
    cv::Stitch::Status status;

    qDebug()<<"Bomb!";
    std::vector<cv::Mat> non_warp,dil_mask;
    status = stitcher.stitch2(vImg, vImg2,rImg,img_warp2,non_warp,dil_mask,2,ConrnerPoint);

    ui->progressBar_Merge->setValue(25);
    qDebug()<<"1";

    do
    {
        qDebug()<<"2";
        if (cv::Stitch::OK == status)
        {
            cv::imwrite("result.jpg",rImg);
            QImage imgResult = QImage((const unsigned char*)(rImg.data),rImg.cols,rImg.rows,rImg.step,QImage::Format_RGB888);
            ui->labelresult->clear();
            ui->labelresult->setPixmap(QPixmap::fromImage(imgResult.scaled(ui->labelresult->width(),ui->labelresult->height(),Qt::KeepAspectRatio)));
            ui->labelresult->show();
        }
        else
        {
            status = stitcher.stitch2(vImg,vImg2, rImg,img_warp2,non_warp,dil_mask,2,ConrnerPoint);
            qDebug()<<"Stitching fail.";
        }
    }while(cv::Stitch::OK != status);
   qDebug()<<"Size "<<img_warp2.size();
//vector<Point> corners(imgs_.size());


   qDebug()<<"Bomb!  = = = ";
   ui->progressBar_Merge->setValue(75);
   //cv::Mat book;

   qDebug()<<non_warp.size();
   std::vector<cv::Mat> dil_resizemask(non_warp.size());
   for(int i=0;i<non_warp.size();i++)
   {
        cv::resize(non_warp[i],dil_resizemask[i],cv::Size(img_warp2[i].cols,img_warp2[i].rows));
        //cv::imshow(QString::number(i).toStdString(),img_warp2[i]);
   }
   ui->progressBar_Merge->setValue(80);

   cv::Mat resultTemp;
   for(int i = 0;i<img_warp2.size();i++)
   {
       resultTemp = cv::Mat(img_warp2[i].rows,img_warp2[i].cols,CV_8UC3);
       for(int b = 0 ; b<img_warp2[i].rows;b++)
       {
           for(int a = 0; a<img_warp2[i].cols;a++)
           {
               //qDebug()<<mask_warp[i].at<uchar>(b,a);
               if(dil_resizemask[i].at<uchar>(b,a) == 255)
               {
                   resultTemp.at<cv::Vec3b>(b, a)[0] = img_warp2[i].at<cv::Vec3b>(b,a)[0];
                   resultTemp.at<cv::Vec3b>(b, a)[1] = img_warp2[i].at<cv::Vec3b>(b,a)[1];
                   resultTemp.at<cv::Vec3b>(b, a)[2] = img_warp2[i].at<cv::Vec3b>(b,a)[2];

               }
               else
               {
                   resultTemp.at<cv::Vec3b>(b, a)[0] = 0;
                   resultTemp.at<cv::Vec3b>(b, a)[1] = 0;
                   resultTemp.at<cv::Vec3b>(b, a)[2] = 0;
               }
               //qDebug()<<i;
           }
       }
      // cv::imshow(QString::number(i).toStdString()+"result",resultTemp);
       FWarp.push_back(resultTemp);
       FSWarp.push_back(resultTemp);
       FSCWarp.push_back(resultTemp);
       //cv::waitKey(0);
   }
   ui->labelaffect1->clear();
   ui->labelaffect2->clear();
   ui->labelaffect3->clear();
   ui->labelaffect4->clear();
   QImage qimage1=QImage((const unsigned char*)FWarp[0].data,FWarp[0].cols,FWarp[0].rows,FWarp[0].step,QImage::Format_RGB888);
   QImage qimage2=QImage((const unsigned char*)FWarp[1].data,FWarp[1].cols,FWarp[1].rows,FWarp[1].step,QImage::Format_RGB888);
   QImage qimage3=QImage((const unsigned char*)FWarp[2].data,FWarp[2].cols,FWarp[2].rows,FWarp[2].step,QImage::Format_RGB888);
   QImage qimage4=QImage((const unsigned char*)FWarp[3].data,FWarp[3].cols,FWarp[3].rows,FWarp[3].step,QImage::Format_RGB888);
   ui->labelaffect1->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect1->width(),ui->labelaffect1->height(),Qt::KeepAspectRatio)));
   ui->labelaffect2->setPixmap(QPixmap::fromImage(qimage2.scaled(ui->labelaffect2->width(),ui->labelaffect2->height(),Qt::KeepAspectRatio)));
   ui->labelaffect3->setPixmap(QPixmap::fromImage(qimage3.scaled(ui->labelaffect3->width(),ui->labelaffect3->height(),Qt::KeepAspectRatio)));
   ui->labelaffect4->setPixmap(QPixmap::fromImage(qimage4.scaled(ui->labelaffect4->width(),ui->labelaffect4->height(),Qt::KeepAspectRatio)));
   ui->labelaffect1->show();
   ui->labelaffect2->show();
   ui->labelaffect3->show();
   ui->labelaffect4->show();
   ui->progressBar_Merge->setValue(100);

}

void MainWindow::on_CalButton_clicked()
{
    std::vector<cv::Mat> src;
    src.push_back(nodilate_warp[0]);
    src.push_back(nodilate_warp[1]);
    src.push_back(nodilate_warp[2]);
    src.push_back(nodilate_warp[3]);
    cv::imshow("Outpu",src[0]);
}


void MainWindow::on_pushButton_clicked()
{
    std::string img1Name("frame10.jpg");
    QTemp1 = cv::imread(img1Name.c_str(),cv::IMREAD_COLOR);
    std::string img2Name("frame20.jpg");
    QTemp2 = cv::imread(img2Name.c_str(),cv::IMREAD_COLOR);
    std::string img3Name("frame30.jpg");
    QTemp3 = cv::imread(img3Name.c_str(),cv::IMREAD_COLOR);
    std::string img4Name("frame40.jpg");
    QTemp4 = cv::imread(img4Name.c_str(),cv::IMREAD_COLOR);

}

void MainWindow::on_RSlider1_sliderMoved(int position)
{
    FSWarp[0] = FWarp[0].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[0].cols;i++)
    {
        for(int j=0;j<FWarp[0].rows;j++)
        {
            double pix =(FWarp[0].at<cv::Vec3b>(j, i)[0]+FWarp[0].at<cv::Vec3b>(j, i)[1]+FWarp[0].at<cv::Vec3b>(j, i)[2])/3;
            if(ui->checkBox1->isChecked())
            {
                if(pix<position)
                {
                    FSWarp[0].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[0].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[0].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[0].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[0].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[0].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
            else
            {
                if(pix>position)
                {
                    FSWarp[0].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[0].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[0].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[0].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[0].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[0].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
        }
    }
    QImage qimage1=QImage((const unsigned char*)FSWarp[0].data,FSWarp[0].cols,FSWarp[0].rows,FSWarp[0].step,QImage::Format_RGB888);
    ui->labelaffect1->clear();
    ui->labelaffect1->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect1->width(),ui->labelaffect1->height(),Qt::KeepAspectRatio)));
    ui->labelaffect1->show();
}


void MainWindow::on_RSlider2_sliderMoved(int position)
{
    FSWarp[1] = FWarp[1].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[1].cols;i++)
    {
        for(int j=0;j<FWarp[1].rows;j++)
        {
            double pix =(FWarp[1].at<cv::Vec3b>(j, i)[0]+FWarp[1].at<cv::Vec3b>(j, i)[1]+FWarp[1].at<cv::Vec3b>(j, i)[2])/3;
            if(ui->checkBox2->isChecked())
            {
                if(pix<position)
                {
                    FSWarp[1].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[1].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[1].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[1].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[1].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[1].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
            else
            {
                if(pix>position)
                {
                    FSWarp[1].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[1].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[1].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[1].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[1].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[1].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
        }
    }
    QImage qimage1=QImage((const unsigned char*)FSWarp[1].data,FSWarp[1].cols,FSWarp[1].rows,FSWarp[1].step,QImage::Format_RGB888);
    ui->labelaffect2->clear();
    ui->labelaffect2->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect2->width(),ui->labelaffect2->height(),Qt::KeepAspectRatio)));
    ui->labelaffect2->show();
}

void MainWindow::on_RSlider3_sliderMoved(int position)
{
    FSWarp[2] = FWarp[2].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[2].cols;i++)
    {
        for(int j=0;j<FWarp[2].rows;j++)
        {
            double pix =(FWarp[2].at<cv::Vec3b>(j, i)[0]+FWarp[2].at<cv::Vec3b>(j, i)[1]+FWarp[2].at<cv::Vec3b>(j, i)[2])/3;
            if(ui->checkBox3->isChecked())
            {
                if(pix<position)
                {
                    FSWarp[2].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[2].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[2].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[2].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[2].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[2].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
            else
            {
                if(pix>position)
                {
                    FSWarp[2].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[2].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[2].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[2].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[2].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[2].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }

        }
    }
    QImage qimage1=QImage((const unsigned char*)FSWarp[2].data,FSWarp[2].cols,FSWarp[2].rows,FSWarp[2].step,QImage::Format_RGB888);
    ui->labelaffect3->clear();
    ui->labelaffect3->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect3->width(),ui->labelaffect3->height(),Qt::KeepAspectRatio)));
    ui->labelaffect3->show();
}

void MainWindow::on_RSlider4_sliderMoved(int position)
{
    FSWarp[3] = FWarp[3].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[3].cols;i++)
    {
        for(int j=0;j<FWarp[3].rows;j++)
        {
            double pix =(FWarp[3].at<cv::Vec3b>(j, i)[0]+FWarp[3].at<cv::Vec3b>(j, i)[1]+FWarp[3].at<cv::Vec3b>(j, i)[2])/3;
            if(ui->checkBox4->isChecked())
            {
                if(pix<position)
                {
                    FSWarp[3].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[3].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[3].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[3].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[3].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[3].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
            else
            {
                if(pix>position)
                {
                    FSWarp[3].at<cv::Vec3b>(j,i)[0] = 0;
                    FSWarp[3].at<cv::Vec3b>(j,i)[1] = 0;
                    FSWarp[3].at<cv::Vec3b>(j,i)[2] = 0;
                }
                else
                {
                    FSWarp[3].at<cv::Vec3b>(j,i)[0] = 255;
                    FSWarp[3].at<cv::Vec3b>(j,i)[1] = 255;
                    FSWarp[3].at<cv::Vec3b>(j,i)[2] = 255;
                }
            }
        }
    }
    QImage qimage1=QImage((const unsigned char*)FSWarp[3].data,FSWarp[3].cols,FSWarp[3].rows,FSWarp[3].step,QImage::Format_RGB888);
    ui->labelaffect4->clear();
    ui->labelaffect4->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect4->width(),ui->labelaffect4->height(),Qt::KeepAspectRatio)));
    ui->labelaffect4->show();
}

void MainWindow::on_Filter1_sliderMoved(int position)
{
    //FSWarp[0] = FWarp[0].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[0].cols;i++)
    {
        for(int j=0;j<FWarp[0].rows;j++)
        {
            //double pix =(FWarp[0].at<cv::Vec3b>(j, i)[0]+FWarp[0].at<cv::Vec3b>(j, i)[1]+FWarp[0].at<cv::Vec3b>(j, i)[2])/3;

            if(pow(pow(i-FSWarp[0].cols/2,2)+pow(j-FSWarp[0].rows/2,2),0.5)>FSWarp[0].rows/100*position)
            {
                FSCWarp[0].at<cv::Vec3b>(j,i)[0] = 0;
                FSCWarp[0].at<cv::Vec3b>(j,i)[1] = 0;
                FSCWarp[0].at<cv::Vec3b>(j,i)[2] = 0;
            }
            else
            {
                FSCWarp[0].at<cv::Vec3b>(j,i)[0] = FSWarp[0].at<cv::Vec3b>(j,i)[0];
                FSCWarp[0].at<cv::Vec3b>(j,i)[1] = FSWarp[0].at<cv::Vec3b>(j,i)[1];
                FSCWarp[0].at<cv::Vec3b>(j,i)[2] = FSWarp[0].at<cv::Vec3b>(j,i)[2];
            }


        }
    }
    QImage qimage1=QImage((const unsigned char*)FSCWarp[0].data,FSCWarp[0].cols,FSCWarp[0].rows,FSCWarp[0].step,QImage::Format_RGB888);
    ui->labelaffect1->clear();
    ui->labelaffect1->setPixmap(QPixmap::fromImage(qimage1.scaled(ui->labelaffect1->width(),ui->labelaffect1->height(),Qt::KeepAspectRatio)));
    ui->labelaffect1->show();
}

void MainWindow::on_Filter3_sliderMoved(int position)
{
    //FSWarp[3] = FWarp[3].clone();
    //QTemp1 = frame1.clone();
    for(int i = 0;i<FWarp[2].cols;i++)
    {
        for(int j=0;j<FWarp[2].rows;j++)
        {
            //double pix =(FWarp[0].at<cv::Vec3b>(j, i)[0]+FWarp[0].at<cv::Vec3b>(j, i)[1]+FWarp[0].at<cv::Vec3b>(j, i)[2])/3;

            if(pow(pow(i-FSWarp[2].cols/2,2)+pow(j-FSWarp[2].rows/2,2),0.5)>FSWarp[2].rows/100*position)
            {
                FSCWarp[2].at<cv::Vec3b>(j,i)[0] = 0;
                FSCWarp[2].at<cv::Vec3b>(j,i)[1] = 0;
                FSCWarp[2].at<cv::Vec3b>(j,i)[2] = 0;
            }
            else
            {
                FSCWarp[2].at<cv::Vec3b>(j,i)[0] = FSWarp[2].at<cv::Vec3b>(j,i)[0];
                FSCWarp[2].at<cv::Vec3b>(j,i)[1] = FSWarp[2].at<cv::Vec3b>(j,i)[1];
                FSCWarp[2].at<cv::Vec3b>(j,i)[2] = FSWarp[2].at<cv::Vec3b>(j,i)[2];
            }
        }
    }
    QImage qimage2=QImage((const unsigned char*)FSCWarp[2].data,FSCWarp[2].cols,FSCWarp[2].rows,FSCWarp[2].step,QImage::Format_RGB888);
    ui->labelaffect3->clear();
    ui->labelaffect3->setPixmap(QPixmap::fromImage(qimage2.scaled(ui->labelaffect3->width(),ui->labelaffect3->height(),Qt::KeepAspectRatio)));
    ui->labelaffect3->show();
}

void MainWindow::on_Filter4_sliderMoved(int position)
{
    for(int i = 0;i<FWarp[3].cols;i++)
    {
        for(int j=0;j<FWarp[3].rows;j++)
        {
            //double pix =(FWarp[0].at<cv::Vec3b>(j, i)[0]+FWarp[0].at<cv::Vec3b>(j, i)[1]+FWarp[0].at<cv::Vec3b>(j, i)[2])/3;

            if(pow(pow(i-FSWarp[3].cols/2,2)+pow(j-FSWarp[3].rows/2,2),0.5)>FSWarp[3].rows/100*position)
            {
                FSCWarp[3].at<cv::Vec3b>(j,i)[0] = 0;
                FSCWarp[3].at<cv::Vec3b>(j,i)[1] = 0;
                FSCWarp[3].at<cv::Vec3b>(j,i)[2] = 0;
            }
            else
            {
                FSCWarp[3].at<cv::Vec3b>(j,i)[0] = FSWarp[3].at<cv::Vec3b>(j,i)[0];
                FSCWarp[3].at<cv::Vec3b>(j,i)[1] = FSWarp[3].at<cv::Vec3b>(j,i)[1];
                FSCWarp[3].at<cv::Vec3b>(j,i)[2] = FSWarp[3].at<cv::Vec3b>(j,i)[2];
            }
        }
    }
    QImage qimage2=QImage((const unsigned char*)FSCWarp[3].data,FSCWarp[3].cols,FSCWarp[3].rows,FSCWarp[3].step,QImage::Format_RGB888);
    ui->labelaffect4->clear();
    ui->labelaffect4->setPixmap(QPixmap::fromImage(qimage2.scaled(ui->labelaffect4->width(),ui->labelaffect4->height(),Qt::KeepAspectRatio)));
    ui->labelaffect4->show();
}
