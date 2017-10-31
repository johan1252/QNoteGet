/********************************************************************************
** Form generated from reading UI file 'viewclasses.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWCLASSES_H
#define UI_VIEWCLASSES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewClasses
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton_addClasses;
    QSplitter *splitter;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QListWidget *listWidget_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewClasses)
    {
        if (ViewClasses->objectName().isEmpty())
            ViewClasses->setObjectName(QStringLiteral("ViewClasses"));
        ViewClasses->resize(800, 600);
        centralwidget = new QWidget(ViewClasses);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 301, 41));
        QFont font;
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        pushButton_addClasses = new QPushButton(centralwidget);
        pushButton_addClasses->setObjectName(QStringLiteral("pushButton_addClasses"));
        pushButton_addClasses->setGeometry(QRect(30, 340, 112, 32));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 110, 768, 192));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(0);
        listWidget = new QListWidget(splitter);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        splitter->addWidget(listWidget);
        listWidget_2 = new QListWidget(splitter);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        splitter->addWidget(listWidget_2);
        listWidget_3 = new QListWidget(splitter);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        splitter->addWidget(listWidget_3);
        ViewClasses->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewClasses);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        ViewClasses->setMenuBar(menubar);
        statusbar = new QStatusBar(ViewClasses);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ViewClasses->setStatusBar(statusbar);

        retranslateUi(ViewClasses);

        QMetaObject::connectSlotsByName(ViewClasses);
    } // setupUi

    void retranslateUi(QMainWindow *ViewClasses)
    {
        ViewClasses->setWindowTitle(QApplication::translate("ViewClasses", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("ViewClasses", "View Classes", Q_NULLPTR));
        pushButton_addClasses->setText(QApplication::translate("ViewClasses", "Add Classes", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewClasses: public Ui_ViewClasses {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWCLASSES_H
