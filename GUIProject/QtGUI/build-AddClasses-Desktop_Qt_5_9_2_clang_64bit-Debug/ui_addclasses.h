/********************************************************************************
** Form generated from reading UI file 'addclasses.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCLASSES_H
#define UI_ADDCLASSES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addClasses
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_done;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QComboBox *comboBox_classes;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QComboBox *comboBox_classNum;
    QPushButton *pushButton_add;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listOfClasses;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_viewClasses;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *addClasses)
    {
        if (addClasses->objectName().isEmpty())
            addClasses->setObjectName(QStringLiteral("addClasses"));
        addClasses->resize(800, 667);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addClasses->sizePolicy().hasHeightForWidth());
        addClasses->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(addClasses);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 80, 221, 51));
        QFont font;
        label->setFont(font);
        label->setStyleSheet(QLatin1String("font-size: 30px;\n"
"color: blue;\n"
""));
        pushButton_done = new QPushButton(centralWidget);
        pushButton_done->setObjectName(QStringLiteral("pushButton_done"));
        pushButton_done->setGeometry(QRect(570, 370, 112, 32));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 180, 235, 94));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        comboBox_classes = new QComboBox(layoutWidget);
        comboBox_classes->setObjectName(QStringLiteral("comboBox_classes"));

        verticalLayout->addWidget(comboBox_classes);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        comboBox_classNum = new QComboBox(layoutWidget);
        comboBox_classNum->setObjectName(QStringLiteral("comboBox_classNum"));

        verticalLayout_2->addWidget(comboBox_classNum);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        pushButton_add = new QPushButton(layoutWidget);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));

        verticalLayout_3->addWidget(pushButton_add);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(400, 100, 260, 262));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_5->addWidget(label_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        listOfClasses = new QListWidget(layoutWidget1);
        listOfClasses->setObjectName(QStringLiteral("listOfClasses"));

        verticalLayout_4->addWidget(listOfClasses);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_5->addLayout(verticalLayout_4);

        pushButton_viewClasses = new QPushButton(centralWidget);
        pushButton_viewClasses->setObjectName(QStringLiteral("pushButton_viewClasses"));
        pushButton_viewClasses->setGeometry(QRect(570, 10, 112, 32));
        addClasses->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(addClasses);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        addClasses->setMenuBar(menuBar);
        mainToolBar = new QToolBar(addClasses);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        addClasses->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(addClasses);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        addClasses->setStatusBar(statusBar);

        retranslateUi(addClasses);

        QMetaObject::connectSlotsByName(addClasses);
    } // setupUi

    void retranslateUi(QMainWindow *addClasses)
    {
        addClasses->setWindowTitle(QApplication::translate("addClasses", "addClasses", Q_NULLPTR));
        label->setText(QApplication::translate("addClasses", "Add Classes", Q_NULLPTR));
        pushButton_done->setText(QApplication::translate("addClasses", "Done", Q_NULLPTR));
        label_2->setText(QApplication::translate("addClasses", "Course Category", Q_NULLPTR));
        label_3->setText(QApplication::translate("addClasses", "Course Code", Q_NULLPTR));
        pushButton_add->setText(QApplication::translate("addClasses", "Add", Q_NULLPTR));
        label_4->setText(QApplication::translate("addClasses", "Classes Added", Q_NULLPTR));
        pushButton->setText(QApplication::translate("addClasses", "Remove", Q_NULLPTR));
        pushButton_viewClasses->setText(QApplication::translate("addClasses", "View Classes", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addClasses: public Ui_addClasses {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCLASSES_H
