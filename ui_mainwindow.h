/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *StartButton;
    QPushButton *closeButton;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *labelresult;
    QPushButton *pushButton_2;
    QPushButton *LF1Button;
    QPushButton *LF2Button;
    QPushButton *LF3Button;
    QPushButton *LF4Button;
    QPushButton *Save1Button;
    QPushButton *Save2Button;
    QPushButton *Save3Button;
    QPushButton *Save4Button;
    QPushButton *LoadButton;
    QPushButton *Merger_2Buttom;
    QSlider *horizontalSlider_frame1;
    QSlider *horizontalSlider_frame2;
    QSlider *horizontalSlider_frame3;
    QSlider *horizontalSlider_frame4;
    QLabel *labelwarp1;
    QLabel *labelwarp2;
    QLabel *labelwarp3;
    QLabel *labelwarp4;
    QLabel *label_fakeResult;
    QLabel *labelaffect1;
    QLabel *labelaffect2;
    QLabel *labelaffect3;
    QLabel *labelaffect4;
    QPushButton *Fake_Buttom;
    QProgressBar *progressBar_Merge;
    QPushButton *ShowButton;
    QPushButton *TempDataButtom;
    QPushButton *CalibrationButton;
    QPushButton *CalButton;
    QPushButton *mergeButton;
    QPushButton *pushButton;
    QSlider *RSlider1;
    QSlider *RSlider2;
    QSlider *RSlider3;
    QSlider *RSlider4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1074, 763);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        StartButton = new QPushButton(centralWidget);
        StartButton->setObjectName(QStringLiteral("StartButton"));
        StartButton->setGeometry(QRect(20, 320, 311, 41));
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(370, 550, 171, 61));
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setGeometry(QRect(20, 10, 160, 120));
        label1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setGeometry(QRect(190, 10, 160, 120));
        label2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label3 = new QLabel(centralWidget);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setGeometry(QRect(20, 160, 160, 120));
        label3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label4 = new QLabel(centralWidget);
        label4->setObjectName(QStringLiteral("label4"));
        label4->setGeometry(QRect(190, 160, 160, 120));
        label4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelresult = new QLabel(centralWidget);
        labelresult->setObjectName(QStringLiteral("labelresult"));
        labelresult->setGeometry(QRect(380, 20, 320, 240));
        labelresult->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 470, 151, 21));
        LF1Button = new QPushButton(centralWidget);
        LF1Button->setObjectName(QStringLiteral("LF1Button"));
        LF1Button->setGeometry(QRect(20, 360, 75, 51));
        LF2Button = new QPushButton(centralWidget);
        LF2Button->setObjectName(QStringLiteral("LF2Button"));
        LF2Button->setGeometry(QRect(100, 360, 75, 51));
        LF3Button = new QPushButton(centralWidget);
        LF3Button->setObjectName(QStringLiteral("LF3Button"));
        LF3Button->setGeometry(QRect(180, 360, 75, 51));
        LF4Button = new QPushButton(centralWidget);
        LF4Button->setObjectName(QStringLiteral("LF4Button"));
        LF4Button->setGeometry(QRect(260, 360, 75, 51));
        Save1Button = new QPushButton(centralWidget);
        Save1Button->setObjectName(QStringLiteral("Save1Button"));
        Save1Button->setGeometry(QRect(20, 410, 75, 51));
        Save2Button = new QPushButton(centralWidget);
        Save2Button->setObjectName(QStringLiteral("Save2Button"));
        Save2Button->setGeometry(QRect(100, 410, 75, 51));
        Save3Button = new QPushButton(centralWidget);
        Save3Button->setObjectName(QStringLiteral("Save3Button"));
        Save3Button->setGeometry(QRect(180, 410, 75, 51));
        Save4Button = new QPushButton(centralWidget);
        Save4Button->setObjectName(QStringLiteral("Save4Button"));
        Save4Button->setGeometry(QRect(260, 410, 75, 51));
        LoadButton = new QPushButton(centralWidget);
        LoadButton->setObjectName(QStringLiteral("LoadButton"));
        LoadButton->setGeometry(QRect(20, 490, 151, 61));
        Merger_2Buttom = new QPushButton(centralWidget);
        Merger_2Buttom->setObjectName(QStringLiteral("Merger_2Buttom"));
        Merger_2Buttom->setGeometry(QRect(180, 490, 151, 61));
        horizontalSlider_frame1 = new QSlider(centralWidget);
        horizontalSlider_frame1->setObjectName(QStringLiteral("horizontalSlider_frame1"));
        horizontalSlider_frame1->setGeometry(QRect(20, 140, 160, 19));
        horizontalSlider_frame1->setMaximum(255);
        horizontalSlider_frame1->setOrientation(Qt::Horizontal);
        horizontalSlider_frame2 = new QSlider(centralWidget);
        horizontalSlider_frame2->setObjectName(QStringLiteral("horizontalSlider_frame2"));
        horizontalSlider_frame2->setGeometry(QRect(190, 140, 160, 19));
        horizontalSlider_frame2->setMaximum(255);
        horizontalSlider_frame2->setOrientation(Qt::Horizontal);
        horizontalSlider_frame3 = new QSlider(centralWidget);
        horizontalSlider_frame3->setObjectName(QStringLiteral("horizontalSlider_frame3"));
        horizontalSlider_frame3->setGeometry(QRect(20, 290, 160, 19));
        horizontalSlider_frame3->setMaximum(255);
        horizontalSlider_frame3->setOrientation(Qt::Horizontal);
        horizontalSlider_frame4 = new QSlider(centralWidget);
        horizontalSlider_frame4->setObjectName(QStringLiteral("horizontalSlider_frame4"));
        horizontalSlider_frame4->setGeometry(QRect(190, 290, 160, 19));
        horizontalSlider_frame4->setMaximum(255);
        horizontalSlider_frame4->setOrientation(Qt::Horizontal);
        labelwarp1 = new QLabel(centralWidget);
        labelwarp1->setObjectName(QStringLiteral("labelwarp1"));
        labelwarp1->setGeometry(QRect(370, 280, 160, 120));
        labelwarp1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelwarp2 = new QLabel(centralWidget);
        labelwarp2->setObjectName(QStringLiteral("labelwarp2"));
        labelwarp2->setGeometry(QRect(550, 280, 160, 120));
        labelwarp2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelwarp3 = new QLabel(centralWidget);
        labelwarp3->setObjectName(QStringLiteral("labelwarp3"));
        labelwarp3->setGeometry(QRect(370, 410, 160, 120));
        labelwarp3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelwarp4 = new QLabel(centralWidget);
        labelwarp4->setObjectName(QStringLiteral("labelwarp4"));
        labelwarp4->setGeometry(QRect(550, 410, 160, 120));
        labelwarp4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_fakeResult = new QLabel(centralWidget);
        label_fakeResult->setObjectName(QStringLiteral("label_fakeResult"));
        label_fakeResult->setGeometry(QRect(730, 20, 320, 240));
        label_fakeResult->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelaffect1 = new QLabel(centralWidget);
        labelaffect1->setObjectName(QStringLiteral("labelaffect1"));
        labelaffect1->setGeometry(QRect(730, 280, 160, 120));
        labelaffect1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelaffect2 = new QLabel(centralWidget);
        labelaffect2->setObjectName(QStringLiteral("labelaffect2"));
        labelaffect2->setGeometry(QRect(900, 280, 160, 120));
        labelaffect2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelaffect3 = new QLabel(centralWidget);
        labelaffect3->setObjectName(QStringLiteral("labelaffect3"));
        labelaffect3->setGeometry(QRect(730, 410, 160, 120));
        labelaffect3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelaffect4 = new QLabel(centralWidget);
        labelaffect4->setObjectName(QStringLiteral("labelaffect4"));
        labelaffect4->setGeometry(QRect(900, 410, 160, 120));
        labelaffect4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        Fake_Buttom = new QPushButton(centralWidget);
        Fake_Buttom->setObjectName(QStringLiteral("Fake_Buttom"));
        Fake_Buttom->setGeometry(QRect(20, 560, 311, 51));
        progressBar_Merge = new QProgressBar(centralWidget);
        progressBar_Merge->setObjectName(QStringLiteral("progressBar_Merge"));
        progressBar_Merge->setGeometry(QRect(20, 630, 311, 23));
        progressBar_Merge->setValue(0);
        ShowButton = new QPushButton(centralWidget);
        ShowButton->setObjectName(QStringLiteral("ShowButton"));
        ShowButton->setGeometry(QRect(550, 550, 161, 61));
        TempDataButtom = new QPushButton(centralWidget);
        TempDataButtom->setObjectName(QStringLiteral("TempDataButtom"));
        TempDataButtom->setGeometry(QRect(910, 640, 121, 41));
        CalibrationButton = new QPushButton(centralWidget);
        CalibrationButton->setObjectName(QStringLiteral("CalibrationButton"));
        CalibrationButton->setGeometry(QRect(370, 620, 171, 51));
        CalButton = new QPushButton(centralWidget);
        CalButton->setObjectName(QStringLiteral("CalButton"));
        CalButton->setGeometry(QRect(550, 620, 161, 51));
        mergeButton = new QPushButton(centralWidget);
        mergeButton->setObjectName(QStringLiteral("mergeButton"));
        mergeButton->setGeometry(QRect(210, 670, 75, 41));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 460, 151, 23));
        RSlider1 = new QSlider(centralWidget);
        RSlider1->setObjectName(QStringLiteral("RSlider1"));
        RSlider1->setGeometry(QRect(730, 390, 160, 22));
        RSlider1->setMaximum(255);
        RSlider1->setOrientation(Qt::Horizontal);
        RSlider2 = new QSlider(centralWidget);
        RSlider2->setObjectName(QStringLiteral("RSlider2"));
        RSlider2->setGeometry(QRect(900, 390, 160, 22));
        RSlider2->setMaximum(255);
        RSlider2->setOrientation(Qt::Horizontal);
        RSlider3 = new QSlider(centralWidget);
        RSlider3->setObjectName(QStringLiteral("RSlider3"));
        RSlider3->setGeometry(QRect(730, 520, 161, 22));
        RSlider3->setMaximum(255);
        RSlider3->setOrientation(Qt::Horizontal);
        RSlider4 = new QSlider(centralWidget);
        RSlider4->setObjectName(QStringLiteral("RSlider4"));
        RSlider4->setGeometry(QRect(900, 520, 160, 22));
        RSlider4->setMaximum(255);
        RSlider4->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1074, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        StartButton->setText(QApplication::translate("MainWindow", "Start", 0));
        closeButton->setText(QApplication::translate("MainWindow", "Close", 0));
        label1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label4->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelresult->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Merge", 0));
        LF1Button->setText(QApplication::translate("MainWindow", "Load Frame1", 0));
        LF2Button->setText(QApplication::translate("MainWindow", "Load Frame2", 0));
        LF3Button->setText(QApplication::translate("MainWindow", "Load Fraem3", 0));
        LF4Button->setText(QApplication::translate("MainWindow", "Load Frame4", 0));
        Save1Button->setText(QApplication::translate("MainWindow", "Save 1", 0));
        Save2Button->setText(QApplication::translate("MainWindow", "Save 2", 0));
        Save3Button->setText(QApplication::translate("MainWindow", "Save 3", 0));
        Save4Button->setText(QApplication::translate("MainWindow", "Save 4", 0));
        LoadButton->setText(QApplication::translate("MainWindow", "Load", 0));
        Merger_2Buttom->setText(QApplication::translate("MainWindow", "Merge2", 0));
        labelwarp1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelwarp2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelwarp3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelwarp4->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_fakeResult->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelaffect1->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelaffect2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelaffect3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        labelaffect4->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        Fake_Buttom->setText(QApplication::translate("MainWindow", "Fake", 0));
        ShowButton->setText(QApplication::translate("MainWindow", "Show", 0));
        TempDataButtom->setText(QApplication::translate("MainWindow", "Load_temp_data", 0));
        CalibrationButton->setText(QApplication::translate("MainWindow", "Calibration", 0));
        CalButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        mergeButton->setText(QApplication::translate("MainWindow", "Merge3", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Load QTemp", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
