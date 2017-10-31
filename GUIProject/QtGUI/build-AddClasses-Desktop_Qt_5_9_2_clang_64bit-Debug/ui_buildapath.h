/********************************************************************************
** Form generated from reading UI file 'buildapath.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDAPATH_H
#define UI_BUILDAPATH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildAPath
{
public:
    QAction *actionAdd_Folder;
    QAction *actionAdd_Class;
    QAction *actionEdit_Folders;
    QAction *actionEdit_Classes;
    QAction *actionMy_Classes;
    QAction *actionMy_Notes;
    QWidget *centralwidget;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *line_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QFrame *line_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QFrame *line;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QGroupBox *group_addClasses;
    QFormLayout *formLayout;
    QLabel *label_addClasses;
    QLabel *label_10;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BuildAPath)
    {
        if (BuildAPath->objectName().isEmpty())
            BuildAPath->setObjectName(QStringLiteral("BuildAPath"));
        BuildAPath->resize(800, 667);
        BuildAPath->setCursor(QCursor(Qt::ArrowCursor));
        BuildAPath->setWindowOpacity(1);
        actionAdd_Folder = new QAction(BuildAPath);
        actionAdd_Folder->setObjectName(QStringLiteral("actionAdd_Folder"));
        actionAdd_Class = new QAction(BuildAPath);
        actionAdd_Class->setObjectName(QStringLiteral("actionAdd_Class"));
        actionEdit_Folders = new QAction(BuildAPath);
        actionEdit_Folders->setObjectName(QStringLiteral("actionEdit_Folders"));
        actionEdit_Classes = new QAction(BuildAPath);
        actionEdit_Classes->setObjectName(QStringLiteral("actionEdit_Classes"));
        actionMy_Classes = new QAction(BuildAPath);
        actionMy_Classes->setObjectName(QStringLiteral("actionMy_Classes"));
        actionMy_Notes = new QAction(BuildAPath);
        actionMy_Notes->setObjectName(QStringLiteral("actionMy_Notes"));
        centralwidget = new QWidget(BuildAPath);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 571, 51));
        QFont font;
        font.setFamily(QStringLiteral("Damascus"));
        font.setPointSize(26);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 360, 133, 109));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_6->setFont(font1);

        verticalLayout_5->addWidget(label_6);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        checkBox_5 = new QCheckBox(layoutWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        verticalLayout_6->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(layoutWidget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        verticalLayout_6->addWidget(checkBox_6);

        checkBox_7 = new QCheckBox(layoutWidget);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        verticalLayout_6->addWidget(checkBox_7);

        checkBox_8 = new QCheckBox(layoutWidget);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        verticalLayout_6->addWidget(checkBox_8);


        verticalLayout_5->addLayout(verticalLayout_6);

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(300, 360, 177, 114));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);

        verticalLayout_8->addWidget(label_8);

        checkBox_12 = new QCheckBox(layoutWidget_2);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        verticalLayout_8->addWidget(checkBox_12);

        checkBox_13 = new QCheckBox(layoutWidget_2);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));

        verticalLayout_8->addWidget(checkBox_13);

        checkBox_14 = new QCheckBox(layoutWidget_2);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));

        verticalLayout_8->addWidget(checkBox_14);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);

        lineEdit_2 = new QLineEdit(layoutWidget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout_8->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(540, 250, 112, 32));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(540, 450, 112, 32));
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 500, 691, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(60, 290, 571, 59));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("font-style: italic;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Times New Roman\" serif;"));

        verticalLayout->addWidget(label_3);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(60, 90, 581, 59));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("font-style: italic;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Times New Roman\" serif;\n"
""));

        verticalLayout_2->addWidget(label_2);

        line = new QFrame(widget1);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(60, 160, 133, 109));
        verticalLayout_4 = new QVBoxLayout(widget2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        verticalLayout_4->addWidget(label_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        checkBox = new QCheckBox(widget2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_3->addWidget(checkBox);

        checkBox_2 = new QCheckBox(widget2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_3->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(widget2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_3->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(widget2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout_3->addWidget(checkBox_4);


        verticalLayout_4->addLayout(verticalLayout_3);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(300, 160, 177, 114));
        verticalLayout_7 = new QVBoxLayout(widget3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        verticalLayout_7->addWidget(label_5);

        checkBox_9 = new QCheckBox(widget3);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        verticalLayout_7->addWidget(checkBox_9);

        checkBox_10 = new QCheckBox(widget3);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        verticalLayout_7->addWidget(checkBox_10);

        checkBox_11 = new QCheckBox(widget3);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        verticalLayout_7->addWidget(checkBox_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_7 = new QLabel(widget3);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout->addWidget(label_7);

        lineEdit = new QLineEdit(widget3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_7->addLayout(horizontalLayout);

        group_addClasses = new QGroupBox(centralwidget);
        group_addClasses->setObjectName(QStringLiteral("group_addClasses"));
        group_addClasses->setGeometry(QRect(40, 530, 231, 61));
        group_addClasses->setCursor(QCursor(Qt::PointingHandCursor));
        group_addClasses->setAlignment(Qt::AlignCenter);
        formLayout = new QFormLayout(group_addClasses);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_addClasses = new QLabel(group_addClasses);
        label_addClasses->setObjectName(QStringLiteral("label_addClasses"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_addClasses);

        label_10 = new QLabel(group_addClasses);
        label_10->setObjectName(QStringLiteral("label_10"));
        QFont font2;
        font2.setPointSize(20);
        label_10->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, label_10);

        BuildAPath->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BuildAPath);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        BuildAPath->setMenuBar(menubar);
        statusbar = new QStatusBar(BuildAPath);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        BuildAPath->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionAdd_Folder);
        menuFile->addAction(actionAdd_Class);
        menuEdit->addAction(actionEdit_Folders);
        menuEdit->addAction(actionEdit_Classes);
        menuView->addAction(actionMy_Classes);
        menuView->addAction(actionMy_Notes);

        retranslateUi(BuildAPath);

        QMetaObject::connectSlotsByName(BuildAPath);
    } // setupUi

    void retranslateUi(QMainWindow *BuildAPath)
    {
        BuildAPath->setWindowTitle(QApplication::translate("BuildAPath", "MainWindow", Q_NULLPTR));
        actionAdd_Folder->setText(QApplication::translate("BuildAPath", "Add Folder", Q_NULLPTR));
        actionAdd_Class->setText(QApplication::translate("BuildAPath", "Add Class", Q_NULLPTR));
        actionEdit_Folders->setText(QApplication::translate("BuildAPath", "Edit Folders", Q_NULLPTR));
        actionEdit_Classes->setText(QApplication::translate("BuildAPath", "Edit Classes", Q_NULLPTR));
        actionMy_Classes->setText(QApplication::translate("BuildAPath", "My Classes", Q_NULLPTR));
        actionMy_Notes->setText(QApplication::translate("BuildAPath", "My Notes", Q_NULLPTR));
        label->setText(QApplication::translate("BuildAPath", "Configure Classes", Q_NULLPTR));
        label_6->setText(QApplication::translate("BuildAPath", "Course Components", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("BuildAPath", "Lecture Notes", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("BuildAPath", "Assignments", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("BuildAPath", "Tutorials", Q_NULLPTR));
        checkBox_8->setText(QApplication::translate("BuildAPath", "Labs", Q_NULLPTR));
        label_8->setText(QApplication::translate("BuildAPath", "Extensions", Q_NULLPTR));
        checkBox_12->setText(QApplication::translate("BuildAPath", ".pdf", Q_NULLPTR));
        checkBox_13->setText(QApplication::translate("BuildAPath", ".pptx", Q_NULLPTR));
        checkBox_14->setText(QApplication::translate("BuildAPath", ".word", Q_NULLPTR));
        label_9->setText(QApplication::translate("BuildAPath", "other", Q_NULLPTR));
        pushButton->setText(QApplication::translate("BuildAPath", "Save", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("BuildAPath", "Save", Q_NULLPTR));
        label_3->setText(QApplication::translate("BuildAPath", "ELEC 270", Q_NULLPTR));
        label_2->setText(QApplication::translate("BuildAPath", "CISC 320", Q_NULLPTR));
        label_4->setText(QApplication::translate("BuildAPath", "Course Components", Q_NULLPTR));
        checkBox->setText(QApplication::translate("BuildAPath", "Lecture Notes", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("BuildAPath", "Assignments", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("BuildAPath", "Tutorials", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("BuildAPath", "Labs", Q_NULLPTR));
        label_5->setText(QApplication::translate("BuildAPath", "Extensions", Q_NULLPTR));
        checkBox_9->setText(QApplication::translate("BuildAPath", ".pdf", Q_NULLPTR));
        checkBox_10->setText(QApplication::translate("BuildAPath", ".pptx", Q_NULLPTR));
        checkBox_11->setText(QApplication::translate("BuildAPath", ".word", Q_NULLPTR));
        label_7->setText(QApplication::translate("BuildAPath", "other", Q_NULLPTR));
        label_addClasses->setText(QApplication::translate("BuildAPath", "TextLabel", Q_NULLPTR));
        label_10->setText(QApplication::translate("BuildAPath", "Add Classes", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("BuildAPath", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("BuildAPath", "Edit", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("BuildAPath", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuildAPath: public Ui_BuildAPath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDAPATH_H
