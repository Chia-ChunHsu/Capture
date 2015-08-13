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
    cv::VideoCapture cap1(1);
    cv::VideoCapture cap2(2);

    //    cv::Mat frame1;
    //    cv::Mat frame2;
    //    cv::Mat frame3;
    //    cv::Mat frame4;
    if(!cap1.isOpened() || !cap2.isOpened())
        return;
    //    if(!cap1.isOpened() || !cap2.isOpened() || !cap3.isOpened() || !cap4.isOpened())
    //        return;
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

    cv::VideoCapture cap3(3);
    cv::VideoCapture cap4(0);
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
    //    cv::imshow("3",frame3);
    //    cv::imshow("4",frame4);

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
    //ui->label1->resize(ui->label1->pixmap()->size());
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


void MainWindow::Stitch(cv::Mat temp)
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
     std::vector< cv::Mat > vImg;
     std::vector< cv::Mat > img_warp;
     //std::vector< cv::Mat > mask_warp;
     //std::vector<cv::Ptr<cv::detail::Blender>> blender;

     //cv::Mat fakeImg;

     vImg.push_back(QTemp1);
     vImg.push_back(QTemp2);
     vImg.push_back(QTemp3);
     vImg.push_back(QTemp4);

     std::vector<cv::Mat> nodilate_warp;


     cv::Stitch stitcher = cv::Stitch::createDefault();
     qDebug()<<"0";
     cv::Stitch::Status status = stitcher.stitch2(vImg, rImg,img_warp,nodilate_warp,dilate_mask);

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
             status = stitcher.stitch2(vImg, rImg,img_warp,nodilate_warp,dilate_mask);
             qDebug()<<"Stitching fail.";
         }
     }while(cv::Stitch::OK != status);


    cv::Mat resultTemp;


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


void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    ui->lineEdit->text();
    ui->textBrowser->append(ui->lineEdit->text());

}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked() == true)
    {
        QTextCodec *codec = QTextCodec::codecForName("Big5");
        ui->textBrowser->append(codec->toUnicode("要輸入的字"));
    }
}

void MainWindow::on_Fake_Buttom_clicked()
{
    std::vector<cv::Mat> fakeresult;
    Fake_r(TWarp,fakeresult);

}

void MainWindow::Fake_r(std::vector<cv::Mat> temp,std::vector<cv::Mat> fakeresult)
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
        cv::Mat tr;
        cv::Mat good;
        //cv::drawKeypoints(temp[0],keypoints1,tempresult,cv::Scalar::all(-1),cv::DrawMatchesFlags::DEFAULT);
        //cv::drawKeypoints(temp[number],keypoints2,tr,cv::Scalar::all(-1),cv::DrawMatchesFlags::DEFAULT);
        qDebug()<<x<<y;

        cv::drawMatches(rImg,keypoints1,temp[number],keypoints2,good_matches,good,cv::Scalar::all(-1),cv::Scalar::all(-1),cv::vector<char>(),cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        //cv::circle(tempresult,cv::Point(x,y),1,cv::Scalar(0,0,255),1,CV_AA,0);
        //cv::imshow("circle"+QString::number(number).toStdString(),tempresult);
        //cv::imshow(QString::number(number).toStdString(),tr);
        cv::imshow("good"+QString::number(number).toStdString(),good);

    }
}
