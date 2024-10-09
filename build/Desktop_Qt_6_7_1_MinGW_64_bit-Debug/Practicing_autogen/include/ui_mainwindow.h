/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_OpenFile;
    QPushButton *btn_ExportFile;
    QComboBox *cb_SampleRate;
    QComboBox *cb_BitDepth;
    QLabel *lbl_SampleRate;
    QLabel *lbl_BitDepth;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1051, 654);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btn_OpenFile = new QPushButton(centralwidget);
        btn_OpenFile->setObjectName("btn_OpenFile");
        btn_OpenFile->setGeometry(QRect(70, 10, 161, 51));
        btn_ExportFile = new QPushButton(centralwidget);
        btn_ExportFile->setObjectName("btn_ExportFile");
        btn_ExportFile->setGeometry(QRect(70, 180, 161, 51));
        cb_SampleRate = new QComboBox(centralwidget);
        cb_SampleRate->addItem(QString());
        cb_SampleRate->addItem(QString());
        cb_SampleRate->addItem(QString());
        cb_SampleRate->addItem(QString());
        cb_SampleRate->setObjectName("cb_SampleRate");
        cb_SampleRate->setGeometry(QRect(90, 80, 121, 31));
        cb_BitDepth = new QComboBox(centralwidget);
        cb_BitDepth->addItem(QString());
        cb_BitDepth->addItem(QString());
        cb_BitDepth->addItem(QString());
        cb_BitDepth->addItem(QString());
        cb_BitDepth->setObjectName("cb_BitDepth");
        cb_BitDepth->setGeometry(QRect(90, 130, 121, 31));
        lbl_SampleRate = new QLabel(centralwidget);
        lbl_SampleRate->setObjectName("lbl_SampleRate");
        lbl_SampleRate->setGeometry(QRect(10, 90, 71, 21));
        lbl_BitDepth = new QLabel(centralwidget);
        lbl_BitDepth->setObjectName("lbl_BitDepth");
        lbl_BitDepth->setGeometry(QRect(10, 140, 71, 21));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_OpenFile->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        btn_ExportFile->setText(QCoreApplication::translate("MainWindow", "Export File", nullptr));
        cb_SampleRate->setItemText(0, QCoreApplication::translate("MainWindow", "44.1 kHz", nullptr));
        cb_SampleRate->setItemText(1, QCoreApplication::translate("MainWindow", "48 kHz", nullptr));
        cb_SampleRate->setItemText(2, QCoreApplication::translate("MainWindow", "96 kHz", nullptr));
        cb_SampleRate->setItemText(3, QCoreApplication::translate("MainWindow", "192 kHz", nullptr));

        cb_BitDepth->setItemText(0, QCoreApplication::translate("MainWindow", "8-bit", nullptr));
        cb_BitDepth->setItemText(1, QCoreApplication::translate("MainWindow", "16-bit", nullptr));
        cb_BitDepth->setItemText(2, QCoreApplication::translate("MainWindow", "24-bit", nullptr));
        cb_BitDepth->setItemText(3, QCoreApplication::translate("MainWindow", "32-bit", nullptr));

        lbl_SampleRate->setText(QCoreApplication::translate("MainWindow", "Sample Rate:", nullptr));
        lbl_BitDepth->setText(QCoreApplication::translate("MainWindow", "Bit Depth:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
