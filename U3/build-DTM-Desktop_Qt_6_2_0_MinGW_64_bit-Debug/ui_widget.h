/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <draw.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_LoadPoints;
    QSpacerItem *verticalSpacer_3;
    QComboBox *comboBox;
    QLineEdit *lineEdit_NumberOfPoints;
    QPushButton *pushButton_Generate;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_createDT;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_drawContours;
    QPushButton *pushButton_mcLabels;
    QPushButton *pushButton_clearContours;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_4;
    QComboBox *comboBox_slope;
    QPushButton *pushButton_drawSlope;
    QLabel *label_5;
    QComboBox *comboBox_exp;
    QPushButton *pushButton_Exposition;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_clearPoints;
    QPushButton *pushButton_cleardt;
    QPushButton *pushButton_ClearAll;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1210, 799);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(Widget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_LoadPoints = new QPushButton(Widget);
        pushButton_LoadPoints->setObjectName(QString::fromUtf8("pushButton_LoadPoints"));

        verticalLayout->addWidget(pushButton_LoadPoints);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        lineEdit_NumberOfPoints = new QLineEdit(Widget);
        lineEdit_NumberOfPoints->setObjectName(QString::fromUtf8("lineEdit_NumberOfPoints"));

        verticalLayout->addWidget(lineEdit_NumberOfPoints);

        pushButton_Generate = new QPushButton(Widget);
        pushButton_Generate->setObjectName(QString::fromUtf8("pushButton_Generate"));

        verticalLayout->addWidget(pushButton_Generate);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_createDT = new QPushButton(Widget);
        pushButton_createDT->setObjectName(QString::fromUtf8("pushButton_createDT"));

        verticalLayout->addWidget(pushButton_createDT);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_3 = new QLineEdit(Widget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        pushButton_drawContours = new QPushButton(Widget);
        pushButton_drawContours->setObjectName(QString::fromUtf8("pushButton_drawContours"));

        verticalLayout->addWidget(pushButton_drawContours);

        pushButton_mcLabels = new QPushButton(Widget);
        pushButton_mcLabels->setObjectName(QString::fromUtf8("pushButton_mcLabels"));

        verticalLayout->addWidget(pushButton_mcLabels);

        pushButton_clearContours = new QPushButton(Widget);
        pushButton_clearContours->setObjectName(QString::fromUtf8("pushButton_clearContours"));

        verticalLayout->addWidget(pushButton_clearContours);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        comboBox_slope = new QComboBox(Widget);
        comboBox_slope->addItem(QString());
        comboBox_slope->addItem(QString());
        comboBox_slope->setObjectName(QString::fromUtf8("comboBox_slope"));

        verticalLayout->addWidget(comboBox_slope);

        pushButton_drawSlope = new QPushButton(Widget);
        pushButton_drawSlope->setObjectName(QString::fromUtf8("pushButton_drawSlope"));

        verticalLayout->addWidget(pushButton_drawSlope);

        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        comboBox_exp = new QComboBox(Widget);
        comboBox_exp->addItem(QString());
        comboBox_exp->addItem(QString());
        comboBox_exp->setObjectName(QString::fromUtf8("comboBox_exp"));

        verticalLayout->addWidget(comboBox_exp);

        pushButton_Exposition = new QPushButton(Widget);
        pushButton_Exposition->setObjectName(QString::fromUtf8("pushButton_Exposition"));

        verticalLayout->addWidget(pushButton_Exposition);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_clearPoints = new QPushButton(Widget);
        pushButton_clearPoints->setObjectName(QString::fromUtf8("pushButton_clearPoints"));

        verticalLayout->addWidget(pushButton_clearPoints);

        pushButton_cleardt = new QPushButton(Widget);
        pushButton_cleardt->setObjectName(QString::fromUtf8("pushButton_cleardt"));

        verticalLayout->addWidget(pushButton_cleardt);

        pushButton_ClearAll = new QPushButton(Widget);
        pushButton_ClearAll->setObjectName(QString::fromUtf8("pushButton_ClearAll"));

        verticalLayout->addWidget(pushButton_ClearAll);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "DTM", nullptr));
        pushButton_LoadPoints->setText(QCoreApplication::translate("Widget", "Load points", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "Random points", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "Pile", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "Saddle", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "Ridge", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Widget", "Valley", nullptr));

        lineEdit_NumberOfPoints->setText(QCoreApplication::translate("Widget", "100", nullptr));
        pushButton_Generate->setText(QCoreApplication::translate("Widget", "Generate", nullptr));
        pushButton_createDT->setText(QCoreApplication::translate("Widget", "Create DT", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Z_min:", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Z_max:", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "dZ:", nullptr));
        pushButton_drawContours->setText(QCoreApplication::translate("Widget", "Draw Contours", nullptr));
        pushButton_mcLabels->setText(QCoreApplication::translate("Widget", "Draw Main Contour Labels", nullptr));
        pushButton_clearContours->setText(QCoreApplication::translate("Widget", "Clear Contours", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "Select slope color palette:", nullptr));
        comboBox_slope->setItemText(0, QCoreApplication::translate("Widget", "Grayscale", nullptr));
        comboBox_slope->setItemText(1, QCoreApplication::translate("Widget", "Yellow to Red", nullptr));

        pushButton_drawSlope->setText(QCoreApplication::translate("Widget", "Draw Slope", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "Select Exposition color palette:", nullptr));
        comboBox_exp->setItemText(0, QCoreApplication::translate("Widget", "KM", nullptr));
        comboBox_exp->setItemText(1, QCoreApplication::translate("Widget", "Esri ", nullptr));

        pushButton_Exposition->setText(QCoreApplication::translate("Widget", "Draw Exposition", nullptr));
        pushButton_clearPoints->setText(QCoreApplication::translate("Widget", "Clear Points", nullptr));
        pushButton_cleardt->setText(QCoreApplication::translate("Widget", "Clear DT", nullptr));
        pushButton_ClearAll->setText(QCoreApplication::translate("Widget", " Clear All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
