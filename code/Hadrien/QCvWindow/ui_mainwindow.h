/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Nov 9 12:32:59 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionAbout_MDMA;
    QAction *actionSave_As;
    QAction *actionAbout_Qt;
    QWidget *central_widget;
    QPushButton *pushButton_run;
    QPushButton *pushButton_calibrate;
    QTreeWidget *treeWidget_list;
    QPushButton *pushButton_deleteAll;
    QComboBox *comboBox_tab;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_configure;
    QPushButton *pushButton_edit;
    QLabel *label_camera;
    QLabel *label_zone;
    QMenuBar *menubar;
    QMenu *menuFicher;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(905, 572);
        MainWindow->setMinimumSize(QSize(905, 572));
        MainWindow->setMaximumSize(QSize(905, 572));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setCheckable(false);
        actionAbout_MDMA = new QAction(MainWindow);
        actionAbout_MDMA->setObjectName(QString::fromUtf8("actionAbout_MDMA"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        central_widget = new QWidget(MainWindow);
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        pushButton_run = new QPushButton(central_widget);
        pushButton_run->setObjectName(QString::fromUtf8("pushButton_run"));
        pushButton_run->setGeometry(QRect(650, 5, 250, 35));
        pushButton_calibrate = new QPushButton(central_widget);
        pushButton_calibrate->setObjectName(QString::fromUtf8("pushButton_calibrate"));
        pushButton_calibrate->setGeometry(QRect(650, 40, 250, 35));
        treeWidget_list = new QTreeWidget(central_widget);
        treeWidget_list->setObjectName(QString::fromUtf8("treeWidget_list"));
        treeWidget_list->setGeometry(QRect(650, 110, 250, 328));
        pushButton_deleteAll = new QPushButton(central_widget);
        pushButton_deleteAll->setObjectName(QString::fromUtf8("pushButton_deleteAll"));
        pushButton_deleteAll->setGeometry(QRect(650, 498, 250, 27));
        comboBox_tab = new QComboBox(central_widget);
        comboBox_tab->setObjectName(QString::fromUtf8("comboBox_tab"));
        comboBox_tab->setGeometry(QRect(5, 5, 645, 35));
        pushButton_delete = new QPushButton(central_widget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(650, 471, 250, 27));
        pushButton_configure = new QPushButton(central_widget);
        pushButton_configure->setObjectName(QString::fromUtf8("pushButton_configure"));
        pushButton_configure->setGeometry(QRect(650, 75, 250, 35));
        pushButton_edit = new QPushButton(central_widget);
        pushButton_edit->setObjectName(QString::fromUtf8("pushButton_edit"));
        pushButton_edit->setGeometry(QRect(650, 444, 250, 27));
        label_camera = new QLabel(central_widget);
        label_camera->setObjectName(QString::fromUtf8("label_camera"));
        label_camera->setGeometry(QRect(5, 45, 640, 480));
        label_camera->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label_zone = new QLabel(central_widget);
        label_zone->setObjectName(QString::fromUtf8("label_zone"));
        label_zone->setGeometry(QRect(5, 45, 640, 480));
        MainWindow->setCentralWidget(central_widget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 905, 25));
        menuFicher = new QMenu(menubar);
        menuFicher->setObjectName(QString::fromUtf8("menuFicher"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(comboBox_tab, pushButton_run);
        QWidget::setTabOrder(pushButton_run, pushButton_calibrate);
        QWidget::setTabOrder(pushButton_calibrate, pushButton_configure);
        QWidget::setTabOrder(pushButton_configure, treeWidget_list);
        QWidget::setTabOrder(treeWidget_list, pushButton_edit);
        QWidget::setTabOrder(pushButton_edit, pushButton_delete);
        QWidget::setTabOrder(pushButton_delete, pushButton_deleteAll);

        menubar->addAction(menuFicher->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFicher->addAction(actionNew);
        menuFicher->addAction(actionOpen);
        menuFicher->addSeparator();
        menuFicher->addAction(actionSave);
        menuFicher->addAction(actionSave_As);
        menuFicher->addSeparator();
        menuFicher->addAction(actionQuit);
        menuHelp->addAction(actionAbout_MDMA);
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(activated()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MDMA - Motion Detection Midi Interface - Unamed configuration", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout_MDMA->setText(QApplication::translate("MainWindow", "About MDMA", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", 0, QApplication::UnicodeUTF8));
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        pushButton_run->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
        pushButton_calibrate->setText(QApplication::translate("MainWindow", "Calibrate", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_list->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Tab", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Type", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        pushButton_deleteAll->setText(QApplication::translate("MainWindow", "Delete All", 0, QApplication::UnicodeUTF8));
        comboBox_tab->clear();
        comboBox_tab->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Tab 3", 0, QApplication::UnicodeUTF8)
        );
        pushButton_delete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_configure->setText(QApplication::translate("MainWindow", "Configure", 0, QApplication::UnicodeUTF8));
        pushButton_edit->setText(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        label_camera->setText(QString());
        label_zone->setText(QString());
        menuFicher->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
