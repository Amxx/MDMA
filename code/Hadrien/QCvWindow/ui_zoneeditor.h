/********************************************************************************
** Form generated from reading UI file 'zoneeditor.ui'
**
** Created: Fri Nov 9 12:32:59 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZONEEDITOR_H
#define UI_ZONEEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zoneEditor
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_x2;
    QLineEdit *lineEdit_y2;
    QLineEdit *lineEdit_x1;
    QLineEdit *lineEdit_y1;
    QLabel *label_name;
    QTabWidget *tabWidget_type;
    QWidget *tab_Fader;
    QLabel *label_axex;
    QLabel *label_axey;
    QSpinBox *spinBox_axex_2;
    QSpinBox *spinBox_axex_1;
    QComboBox *comboBox_axex_0;
    QComboBox *comboBox_axey_0;
    QSpinBox *spinBox_axey_1;
    QSpinBox *spinBox_axey_2;
    QWidget *tab_Pad;
    QLabel *label_enter;
    QLabel *label_exit;
    QLabel *label_open;
    QLabel *label_close;
    QLabel *label_shock;
    QSpinBox *spinBox_enter_1;
    QComboBox *comboBox_enter;
    QSpinBox *spinBox_exit_1;
    QSpinBox *spinBox_open_1;
    QSpinBox *spinBox_close_1;
    QSpinBox *spinBox_shock_1;
    QSpinBox *spinBox_enter_2;
    QSpinBox *spinBox_exit_2;
    QSpinBox *spinBox_open_2;
    QSpinBox *spinBox_close_2;
    QSpinBox *spinBox_shock_2;
    QSpinBox *spinBox_enter_3;
    QSpinBox *spinBox_exit_3;
    QSpinBox *spinBox_open_3;
    QSpinBox *spinBox_close_3;
    QSpinBox *spinBox_shock_3;
    QComboBox *comboBox_exit;
    QComboBox *comboBox_open;
    QComboBox *comboBox_close;
    QComboBox *comboBox_shock;
    QWidget *tab_Segment;
    QLabel *label_coords;
    QLineEdit *lineEdit_name;
    QComboBox *comboBox_tab;

    void setupUi(QDialog *zoneEditor)
    {
        if (zoneEditor->objectName().isEmpty())
            zoneEditor->setObjectName(QString::fromUtf8("zoneEditor"));
        zoneEditor->resize(320, 320);
        zoneEditor->setMinimumSize(QSize(320, 320));
        zoneEditor->setMaximumSize(QSize(320, 320));
        buttonBox = new QDialogButtonBox(zoneEditor);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(5, 285, 310, 30));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit_x2 = new QLineEdit(zoneEditor);
        lineEdit_x2->setObjectName(QString::fromUtf8("lineEdit_x2"));
        lineEdit_x2->setGeometry(QRect(200, 35, 60, 30));
        lineEdit_y2 = new QLineEdit(zoneEditor);
        lineEdit_y2->setObjectName(QString::fromUtf8("lineEdit_y2"));
        lineEdit_y2->setGeometry(QRect(260, 35, 60, 30));
        lineEdit_x1 = new QLineEdit(zoneEditor);
        lineEdit_x1->setObjectName(QString::fromUtf8("lineEdit_x1"));
        lineEdit_x1->setGeometry(QRect(80, 35, 60, 30));
        lineEdit_y1 = new QLineEdit(zoneEditor);
        lineEdit_y1->setObjectName(QString::fromUtf8("lineEdit_y1"));
        lineEdit_y1->setGeometry(QRect(140, 35, 60, 30));
        label_name = new QLabel(zoneEditor);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(5, 0, 81, 35));
        tabWidget_type = new QTabWidget(zoneEditor);
        tabWidget_type->setObjectName(QString::fromUtf8("tabWidget_type"));
        tabWidget_type->setGeometry(QRect(5, 70, 310, 215));
        tabWidget_type->setTabPosition(QTabWidget::North);
        tabWidget_type->setTabShape(QTabWidget::Rounded);
        tab_Fader = new QWidget();
        tab_Fader->setObjectName(QString::fromUtf8("tab_Fader"));
        label_axex = new QLabel(tab_Fader);
        label_axex->setObjectName(QString::fromUtf8("label_axex"));
        label_axex->setGeometry(QRect(130, 20, 40, 20));
        label_axey = new QLabel(tab_Fader);
        label_axey->setObjectName(QString::fromUtf8("label_axey"));
        label_axey->setGeometry(QRect(130, 100, 40, 20));
        spinBox_axex_2 = new QSpinBox(tab_Fader);
        spinBox_axex_2->setObjectName(QString::fromUtf8("spinBox_axex_2"));
        spinBox_axex_2->setEnabled(false);
        spinBox_axex_2->setGeometry(QRect(220, 50, 80, 30));
        spinBox_axex_2->setMaximum(127);
        spinBox_axex_2->setValue(0);
        spinBox_axex_1 = new QSpinBox(tab_Fader);
        spinBox_axex_1->setObjectName(QString::fromUtf8("spinBox_axex_1"));
        spinBox_axex_1->setEnabled(false);
        spinBox_axex_1->setGeometry(QRect(160, 50, 60, 30));
        spinBox_axex_1->setMaximum(15);
        spinBox_axex_1->setValue(0);
        comboBox_axex_0 = new QComboBox(tab_Fader);
        comboBox_axex_0->setObjectName(QString::fromUtf8("comboBox_axex_0"));
        comboBox_axex_0->setGeometry(QRect(5, 50, 151, 30));
        comboBox_axey_0 = new QComboBox(tab_Fader);
        comboBox_axey_0->setObjectName(QString::fromUtf8("comboBox_axey_0"));
        comboBox_axey_0->setEnabled(true);
        comboBox_axey_0->setGeometry(QRect(5, 130, 151, 30));
        spinBox_axey_1 = new QSpinBox(tab_Fader);
        spinBox_axey_1->setObjectName(QString::fromUtf8("spinBox_axey_1"));
        spinBox_axey_1->setEnabled(false);
        spinBox_axey_1->setGeometry(QRect(160, 130, 60, 30));
        spinBox_axey_1->setMaximum(15);
        spinBox_axey_2 = new QSpinBox(tab_Fader);
        spinBox_axey_2->setObjectName(QString::fromUtf8("spinBox_axey_2"));
        spinBox_axey_2->setEnabled(false);
        spinBox_axey_2->setGeometry(QRect(220, 130, 80, 30));
        spinBox_axey_2->setMaximum(127);
        tabWidget_type->addTab(tab_Fader, QString());
        tab_Pad = new QWidget();
        tab_Pad->setObjectName(QString::fromUtf8("tab_Pad"));
        label_enter = new QLabel(tab_Pad);
        label_enter->setObjectName(QString::fromUtf8("label_enter"));
        label_enter->setGeometry(QRect(10, 10, 66, 32));
        label_exit = new QLabel(tab_Pad);
        label_exit->setObjectName(QString::fromUtf8("label_exit"));
        label_exit->setGeometry(QRect(10, 42, 66, 32));
        label_open = new QLabel(tab_Pad);
        label_open->setObjectName(QString::fromUtf8("label_open"));
        label_open->setGeometry(QRect(10, 74, 66, 32));
        label_close = new QLabel(tab_Pad);
        label_close->setObjectName(QString::fromUtf8("label_close"));
        label_close->setGeometry(QRect(10, 106, 66, 32));
        label_shock = new QLabel(tab_Pad);
        label_shock->setObjectName(QString::fromUtf8("label_shock"));
        label_shock->setGeometry(QRect(10, 138, 66, 32));
        spinBox_enter_1 = new QSpinBox(tab_Pad);
        spinBox_enter_1->setObjectName(QString::fromUtf8("spinBox_enter_1"));
        spinBox_enter_1->setEnabled(false);
        spinBox_enter_1->setGeometry(QRect(169, 10, 40, 32));
        spinBox_enter_1->setMaximum(15);
        spinBox_enter_1->setValue(0);
        comboBox_enter = new QComboBox(tab_Pad);
        comboBox_enter->setObjectName(QString::fromUtf8("comboBox_enter"));
        comboBox_enter->setGeometry(QRect(50, 10, 119, 32));
        spinBox_exit_1 = new QSpinBox(tab_Pad);
        spinBox_exit_1->setObjectName(QString::fromUtf8("spinBox_exit_1"));
        spinBox_exit_1->setEnabled(false);
        spinBox_exit_1->setGeometry(QRect(169, 42, 40, 32));
        spinBox_exit_1->setMaximum(15);
        spinBox_open_1 = new QSpinBox(tab_Pad);
        spinBox_open_1->setObjectName(QString::fromUtf8("spinBox_open_1"));
        spinBox_open_1->setEnabled(false);
        spinBox_open_1->setGeometry(QRect(169, 74, 40, 32));
        spinBox_open_1->setMaximum(15);
        spinBox_close_1 = new QSpinBox(tab_Pad);
        spinBox_close_1->setObjectName(QString::fromUtf8("spinBox_close_1"));
        spinBox_close_1->setEnabled(false);
        spinBox_close_1->setGeometry(QRect(169, 106, 40, 32));
        spinBox_close_1->setMaximum(15);
        spinBox_shock_1 = new QSpinBox(tab_Pad);
        spinBox_shock_1->setObjectName(QString::fromUtf8("spinBox_shock_1"));
        spinBox_shock_1->setEnabled(false);
        spinBox_shock_1->setGeometry(QRect(169, 138, 40, 32));
        spinBox_shock_1->setMaximum(15);
        spinBox_enter_2 = new QSpinBox(tab_Pad);
        spinBox_enter_2->setObjectName(QString::fromUtf8("spinBox_enter_2"));
        spinBox_enter_2->setEnabled(false);
        spinBox_enter_2->setGeometry(QRect(209, 10, 49, 32));
        spinBox_enter_2->setMaximum(127);
        spinBox_enter_2->setValue(0);
        spinBox_exit_2 = new QSpinBox(tab_Pad);
        spinBox_exit_2->setObjectName(QString::fromUtf8("spinBox_exit_2"));
        spinBox_exit_2->setEnabled(false);
        spinBox_exit_2->setGeometry(QRect(209, 42, 49, 32));
        spinBox_exit_2->setMaximum(127);
        spinBox_open_2 = new QSpinBox(tab_Pad);
        spinBox_open_2->setObjectName(QString::fromUtf8("spinBox_open_2"));
        spinBox_open_2->setEnabled(false);
        spinBox_open_2->setGeometry(QRect(209, 74, 49, 32));
        spinBox_open_2->setMaximum(127);
        spinBox_close_2 = new QSpinBox(tab_Pad);
        spinBox_close_2->setObjectName(QString::fromUtf8("spinBox_close_2"));
        spinBox_close_2->setEnabled(false);
        spinBox_close_2->setGeometry(QRect(209, 106, 49, 32));
        spinBox_close_2->setMaximum(127);
        spinBox_shock_2 = new QSpinBox(tab_Pad);
        spinBox_shock_2->setObjectName(QString::fromUtf8("spinBox_shock_2"));
        spinBox_shock_2->setEnabled(false);
        spinBox_shock_2->setGeometry(QRect(209, 138, 49, 32));
        spinBox_shock_2->setMaximum(127);
        spinBox_enter_3 = new QSpinBox(tab_Pad);
        spinBox_enter_3->setObjectName(QString::fromUtf8("spinBox_enter_3"));
        spinBox_enter_3->setEnabled(false);
        spinBox_enter_3->setGeometry(QRect(258, 10, 49, 32));
        spinBox_enter_3->setMaximum(127);
        spinBox_exit_3 = new QSpinBox(tab_Pad);
        spinBox_exit_3->setObjectName(QString::fromUtf8("spinBox_exit_3"));
        spinBox_exit_3->setEnabled(false);
        spinBox_exit_3->setGeometry(QRect(258, 42, 49, 32));
        spinBox_exit_3->setMaximum(127);
        spinBox_open_3 = new QSpinBox(tab_Pad);
        spinBox_open_3->setObjectName(QString::fromUtf8("spinBox_open_3"));
        spinBox_open_3->setEnabled(false);
        spinBox_open_3->setGeometry(QRect(258, 74, 49, 32));
        spinBox_open_3->setMaximum(127);
        spinBox_close_3 = new QSpinBox(tab_Pad);
        spinBox_close_3->setObjectName(QString::fromUtf8("spinBox_close_3"));
        spinBox_close_3->setEnabled(false);
        spinBox_close_3->setGeometry(QRect(258, 106, 49, 32));
        spinBox_close_3->setMaximum(127);
        spinBox_shock_3 = new QSpinBox(tab_Pad);
        spinBox_shock_3->setObjectName(QString::fromUtf8("spinBox_shock_3"));
        spinBox_shock_3->setEnabled(false);
        spinBox_shock_3->setGeometry(QRect(258, 138, 49, 32));
        spinBox_shock_3->setMaximum(127);
        comboBox_exit = new QComboBox(tab_Pad);
        comboBox_exit->setObjectName(QString::fromUtf8("comboBox_exit"));
        comboBox_exit->setGeometry(QRect(50, 40, 119, 32));
        comboBox_open = new QComboBox(tab_Pad);
        comboBox_open->setObjectName(QString::fromUtf8("comboBox_open"));
        comboBox_open->setGeometry(QRect(50, 74, 119, 32));
        comboBox_close = new QComboBox(tab_Pad);
        comboBox_close->setObjectName(QString::fromUtf8("comboBox_close"));
        comboBox_close->setGeometry(QRect(50, 106, 119, 32));
        comboBox_shock = new QComboBox(tab_Pad);
        comboBox_shock->setObjectName(QString::fromUtf8("comboBox_shock"));
        comboBox_shock->setGeometry(QRect(50, 138, 119, 32));
        tabWidget_type->addTab(tab_Pad, QString());
        tab_Segment = new QWidget();
        tab_Segment->setObjectName(QString::fromUtf8("tab_Segment"));
        tabWidget_type->addTab(tab_Segment, QString());
        label_coords = new QLabel(zoneEditor);
        label_coords->setObjectName(QString::fromUtf8("label_coords"));
        label_coords->setGeometry(QRect(5, 32, 81, 35));
        lineEdit_name = new QLineEdit(zoneEditor);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(80, 0, 170, 35));
        comboBox_tab = new QComboBox(zoneEditor);
        comboBox_tab->setObjectName(QString::fromUtf8("comboBox_tab"));
        comboBox_tab->setGeometry(QRect(250, 0, 70, 35));
        QWidget::setTabOrder(lineEdit_name, comboBox_tab);
        QWidget::setTabOrder(comboBox_tab, lineEdit_x1);
        QWidget::setTabOrder(lineEdit_x1, lineEdit_y1);
        QWidget::setTabOrder(lineEdit_y1, lineEdit_x2);
        QWidget::setTabOrder(lineEdit_x2, lineEdit_y2);
        QWidget::setTabOrder(lineEdit_y2, tabWidget_type);
        QWidget::setTabOrder(tabWidget_type, comboBox_axex_0);
        QWidget::setTabOrder(comboBox_axex_0, spinBox_axex_1);
        QWidget::setTabOrder(spinBox_axex_1, spinBox_axex_2);
        QWidget::setTabOrder(spinBox_axex_2, comboBox_axey_0);
        QWidget::setTabOrder(comboBox_axey_0, spinBox_axey_1);
        QWidget::setTabOrder(spinBox_axey_1, spinBox_axey_2);
        QWidget::setTabOrder(spinBox_axey_2, comboBox_enter);
        QWidget::setTabOrder(comboBox_enter, spinBox_enter_1);
        QWidget::setTabOrder(spinBox_enter_1, spinBox_enter_2);
        QWidget::setTabOrder(spinBox_enter_2, spinBox_enter_3);
        QWidget::setTabOrder(spinBox_enter_3, comboBox_exit);
        QWidget::setTabOrder(comboBox_exit, spinBox_exit_1);
        QWidget::setTabOrder(spinBox_exit_1, spinBox_exit_2);
        QWidget::setTabOrder(spinBox_exit_2, spinBox_exit_3);
        QWidget::setTabOrder(spinBox_exit_3, comboBox_open);
        QWidget::setTabOrder(comboBox_open, spinBox_open_1);
        QWidget::setTabOrder(spinBox_open_1, spinBox_open_2);
        QWidget::setTabOrder(spinBox_open_2, spinBox_open_3);
        QWidget::setTabOrder(spinBox_open_3, comboBox_close);
        QWidget::setTabOrder(comboBox_close, spinBox_close_1);
        QWidget::setTabOrder(spinBox_close_1, spinBox_close_2);
        QWidget::setTabOrder(spinBox_close_2, spinBox_close_3);
        QWidget::setTabOrder(spinBox_close_3, comboBox_shock);
        QWidget::setTabOrder(comboBox_shock, spinBox_shock_1);
        QWidget::setTabOrder(spinBox_shock_1, spinBox_shock_2);
        QWidget::setTabOrder(spinBox_shock_2, spinBox_shock_3);
        QWidget::setTabOrder(spinBox_shock_3, buttonBox);

        retranslateUi(zoneEditor);
        QObject::connect(buttonBox, SIGNAL(accepted()), zoneEditor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), zoneEditor, SLOT(reject()));

        tabWidget_type->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(zoneEditor);
    } // setupUi

    void retranslateUi(QDialog *zoneEditor)
    {
        zoneEditor->setWindowTitle(QApplication::translate("zoneEditor", "Editeur de zone", 0, QApplication::UnicodeUTF8));
        label_name->setText(QApplication::translate("zoneEditor", "Name", 0, QApplication::UnicodeUTF8));
        label_axex->setText(QApplication::translate("zoneEditor", "Axe X", 0, QApplication::UnicodeUTF8));
        label_axey->setText(QApplication::translate("zoneEditor", "Axe Y", 0, QApplication::UnicodeUTF8));
        comboBox_axex_0->clear();
        comboBox_axex_0->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
        );
        comboBox_axey_0->clear();
        comboBox_axey_0->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
        );
        tabWidget_type->setTabText(tabWidget_type->indexOf(tab_Fader), QApplication::translate("zoneEditor", "Fader", 0, QApplication::UnicodeUTF8));
        label_enter->setText(QApplication::translate("zoneEditor", "Enter", 0, QApplication::UnicodeUTF8));
        label_exit->setText(QApplication::translate("zoneEditor", "Exit", 0, QApplication::UnicodeUTF8));
        label_open->setText(QApplication::translate("zoneEditor", "Open", 0, QApplication::UnicodeUTF8));
        label_close->setText(QApplication::translate("zoneEditor", "Close", 0, QApplication::UnicodeUTF8));
        label_shock->setText(QApplication::translate("zoneEditor", "Shock", 0, QApplication::UnicodeUTF8));
        comboBox_enter->clear();
        comboBox_enter->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_exit->clear();
        comboBox_exit->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_open->clear();
        comboBox_open->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_close->clear();
        comboBox_close->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_shock->clear();
        comboBox_shock->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("zoneEditor", "note off", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "note on", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "polyfonic aftertouch", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "channel pressure", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "program change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "control change", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "pitch bending", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "system", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "goto tab 3", 0, QApplication::UnicodeUTF8)
        );
        tabWidget_type->setTabText(tabWidget_type->indexOf(tab_Pad), QApplication::translate("zoneEditor", "Pad", 0, QApplication::UnicodeUTF8));
        tabWidget_type->setTabText(tabWidget_type->indexOf(tab_Segment), QApplication::translate("zoneEditor", "Segment", 0, QApplication::UnicodeUTF8));
        label_coords->setText(QApplication::translate("zoneEditor", "Position", 0, QApplication::UnicodeUTF8));
        lineEdit_name->setText(QApplication::translate("zoneEditor", "New zone", 0, QApplication::UnicodeUTF8));
        comboBox_tab->clear();
        comboBox_tab->insertItems(0, QStringList()
         << QApplication::translate("zoneEditor", "Tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "Tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("zoneEditor", "Tab 3", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class zoneEditor: public Ui_zoneEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZONEEDITOR_H
