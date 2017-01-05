/********************************************************************************
** Form generated from reading ui file 'gui.ui'
**
** Created: Wed Apr 13 21:10:44 2016
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gui
{
public:
    QWidget *centralWidget;
    QSlider *Positon_slider;
    QPushButton *Exit_PDO;
    QPushButton *PPM_EN;
    QPushButton *Enter_PDO;
    QLabel *label;
    QPushButton *Motor_Check;
    QPushButton *PDO_test;
    QPushButton *Bootup;
    QPushButton *Send_UDP;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName(QString::fromUtf8("Gui"));
        Gui->resize(800, 480);
        centralWidget = new QWidget(Gui);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Positon_slider = new QSlider(centralWidget);
        Positon_slider->setObjectName(QString::fromUtf8("Positon_slider"));
        Positon_slider->setGeometry(QRect(110, 160, 421, 16));
        Positon_slider->setMinimum(-1000);
        Positon_slider->setMaximum(1000);
        Positon_slider->setPageStep(1);
        Positon_slider->setOrientation(Qt::Horizontal);
        Positon_slider->setInvertedAppearance(false);
        Positon_slider->setTickPosition(QSlider::TicksBothSides);
        Exit_PDO = new QPushButton(centralWidget);
        Exit_PDO->setObjectName(QString::fromUtf8("Exit_PDO"));
        Exit_PDO->setGeometry(QRect(610, 300, 121, 61));
        Exit_PDO->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        PPM_EN = new QPushButton(centralWidget);
        PPM_EN->setObjectName(QString::fromUtf8("PPM_EN"));
        PPM_EN->setGeometry(QRect(610, 110, 121, 61));
        PPM_EN->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        Enter_PDO = new QPushButton(centralWidget);
        Enter_PDO->setObjectName(QString::fromUtf8("Enter_PDO"));
        Enter_PDO->setGeometry(QRect(610, 210, 121, 61));
        Enter_PDO->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 160, 61, 15));
        Motor_Check = new QPushButton(centralWidget);
        Motor_Check->setObjectName(QString::fromUtf8("Motor_Check"));
        Motor_Check->setGeometry(QRect(610, 20, 121, 61));
        Motor_Check->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        PDO_test = new QPushButton(centralWidget);
        PDO_test->setObjectName(QString::fromUtf8("PDO_test"));
        PDO_test->setGeometry(QRect(440, 300, 121, 61));
        PDO_test->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        Bootup = new QPushButton(centralWidget);
        Bootup->setObjectName(QString::fromUtf8("Bootup"));
        Bootup->setGeometry(QRect(280, 300, 121, 61));
        Bootup->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        Send_UDP = new QPushButton(centralWidget);
        Send_UDP->setObjectName(QString::fromUtf8("Send_UDP"));
        Send_UDP->setGeometry(QRect(110, 300, 121, 61));
        Send_UDP->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"border-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(192, 198, 196, 255), stop:1 rgba(255, 255, 255, 255));"));
        Gui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Gui);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        Gui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Gui);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Gui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Gui);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Gui->setStatusBar(statusBar);

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QMainWindow *Gui)
    {
        Gui->setWindowTitle(QApplication::translate("Gui", "Gui", 0, QApplication::UnicodeUTF8));
        Exit_PDO->setText(QApplication::translate("Gui", "\351\200\200\345\207\272PDO", 0, QApplication::UnicodeUTF8));
        PPM_EN->setText(QApplication::translate("Gui", "\344\275\277\350\203\275PPM", 0, QApplication::UnicodeUTF8));
        Enter_PDO->setText(QApplication::translate("Gui", "\350\277\233\345\205\245PDO", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Gui", "\344\275\215\347\275\256\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        Motor_Check->setText(QApplication::translate("Gui", "\347\224\265\346\234\272\350\207\252\346\243\200", 0, QApplication::UnicodeUTF8));
        PDO_test->setText(QApplication::translate("Gui", "PDO_test", 0, QApplication::UnicodeUTF8));
        Bootup->setText(QApplication::translate("Gui", "Boot UP", 0, QApplication::UnicodeUTF8));
        Send_UDP->setText(QApplication::translate("Gui", "UDP_Send", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Gui);
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
