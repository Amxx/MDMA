/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created: Fri Nov 9 12:13:35 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configwindow
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *cameraLabel;
    QComboBox *cameraComboBox;
    QComboBox *midiPortComboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *configwindow)
    {
        if (configwindow->objectName().isEmpty())
            configwindow->setObjectName(QString::fromUtf8("configwindow"));
        configwindow->resize(320, 420);
        formLayoutWidget = new QWidget(configwindow);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 301, 381));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        cameraLabel = new QLabel(formLayoutWidget);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, cameraLabel);

        cameraComboBox = new QComboBox(formLayoutWidget);
        cameraComboBox->setObjectName(QString::fromUtf8("cameraComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cameraComboBox);

        midiPortComboBox = new QComboBox(formLayoutWidget);
        midiPortComboBox->setObjectName(QString::fromUtf8("midiPortComboBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, midiPortComboBox);

        pushButton = new QPushButton(configwindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 390, 100, 27));
        pushButton_2 = new QPushButton(configwindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 390, 100, 27));

        retranslateUi(configwindow);

        QMetaObject::connectSlotsByName(configwindow);
    } // setupUi

    void retranslateUi(QDialog *configwindow)
    {
        configwindow->setWindowTitle(QApplication::translate("configwindow", "Configuration", 0, QApplication::UnicodeUTF8));
        cameraLabel->setText(QApplication::translate("configwindow", "Camera", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("configwindow", "Save", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("configwindow", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class configwindow: public Ui_configwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
