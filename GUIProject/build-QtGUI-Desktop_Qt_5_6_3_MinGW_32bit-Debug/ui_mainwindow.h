/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *HomePage;
    QFrame *frame_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QFrame *frame_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QWidget *SignUpPage;
    QFrame *frame_4;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *label_6;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_4;
    QWidget *SubscribePage;
    QFrame *frame_5;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton_2;
    QWidget *UserHome;
    QFrame *frame_6;
    QLabel *label_9;
    QLabel *label_10;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1122, 660);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 1101, 571));
        HomePage = new QWidget();
        HomePage->setObjectName(QStringLiteral("HomePage"));
        frame_2 = new QFrame(HomePage);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 10, 661, 561));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(2);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 90, 331, 118));
        QFont font;
        font.setFamily(QStringLiteral("MV Boli"));
        font.setPointSize(36);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setFrameShape(QFrame::NoFrame);
        label->setMidLineWidth(1);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(frame_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(170, 350, 331, 51));
        lineEdit->setEchoMode(QLineEdit::Password);
        lineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(240, 450, 191, 51));
        lineEdit_3 = new QLineEdit(frame_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 240, 331, 51));
        lineEdit_3->setCursorMoveStyle(Qt::VisualMoveStyle);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 271, 141));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        frame_3 = new QFrame(HomePage);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(670, 10, 431, 561));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Sunken);
        frame_3->setLineWidth(2);
        lineEdit_2 = new QLineEdit(frame_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 350, 331, 51));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        lineEdit_2->setCursorMoveStyle(Qt::VisualMoveStyle);
        lineEdit_4 = new QLineEdit(frame_3);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(50, 240, 331, 51));
        lineEdit_4->setCursorMoveStyle(Qt::VisualMoveStyle);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 90, 331, 118));
        label_2->setFont(font);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setMidLineWidth(1);
        label_2->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(120, 450, 191, 51));
        stackedWidget->addWidget(HomePage);
        SignUpPage = new QWidget();
        SignUpPage->setObjectName(QStringLiteral("SignUpPage"));
        frame_4 = new QFrame(SignUpPage);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(0, 10, 1101, 561));
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Sunken);
        frame_4->setLineWidth(2);
        label_4 = new QLabel(frame_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 0, 651, 118));
        label_4->setFont(font);
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setMidLineWidth(1);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 271, 141));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayoutWidget = new QWidget(frame_4);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 130, 581, 281));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(formLayoutWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        QFont font1;
        font1.setPointSize(14);
        nameLabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(formLayoutWidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        passwordLabel = new QLabel(formLayoutWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(formLayoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setFont(font1);

        formLayout->setWidget(4, QFormLayout::FieldRole, passwordLineEdit);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        checkBox_3 = new QCheckBox(formLayoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setFont(font1);

        formLayout->setWidget(6, QFormLayout::FieldRole, checkBox_3);

        checkBox_2 = new QCheckBox(formLayoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setFont(font1);

        formLayout->setWidget(7, QFormLayout::FieldRole, checkBox_2);

        checkBox = new QCheckBox(formLayoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setFont(font1);

        formLayout->setWidget(8, QFormLayout::FieldRole, checkBox);

        pushButton_4 = new QPushButton(frame_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(460, 450, 191, 51));
        stackedWidget->addWidget(SignUpPage);
        SubscribePage = new QWidget();
        SubscribePage->setObjectName(QStringLiteral("SubscribePage"));
        frame_5 = new QFrame(SubscribePage);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(10, 10, 1091, 561));
        sizePolicy.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy);
        frame_5->setFrameShape(QFrame::Box);
        frame_5->setFrameShadow(QFrame::Sunken);
        frame_5->setLineWidth(2);
        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(270, 0, 761, 131));
        label_7->setFont(font);
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setFrameShape(QFrame::NoFrame);
        label_7->setMidLineWidth(1);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 10, 271, 141));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        pushButton_2 = new QPushButton(frame_5);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 410, 181, 71));
        stackedWidget->addWidget(SubscribePage);
        UserHome = new QWidget();
        UserHome->setObjectName(QStringLiteral("UserHome"));
        frame_6 = new QFrame(UserHome);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setGeometry(QRect(10, 10, 1091, 561));
        sizePolicy.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy);
        frame_6->setFrameShape(QFrame::Box);
        frame_6->setFrameShadow(QFrame::Sunken);
        frame_6->setLineWidth(2);
        label_9 = new QLabel(frame_6);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(150, 0, 761, 131));
        label_9->setFont(font);
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setFrameShape(QFrame::NoFrame);
        label_9->setMidLineWidth(1);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(frame_6);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 271, 141));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        stackedWidget->addWidget(UserHome);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1122, 31));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Note-Get", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Sign-In", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Login", Q_NULLPTR));
        lineEdit_3->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/newPrefix/copy.png\"/></p></body></html>", Q_NULLPTR));
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        lineEdit_4->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Sign-Up", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Create Account", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Sign-Up Form", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/newPrefix/copy.png\"/></p></body></html>", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Courses", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("MainWindow", "CMPE/CISC 320", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "ELEC 371", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "CISC 221", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Done", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Subscribe to Content", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/newPrefix/copy.png\"/></p></body></html>", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Done Subscribe", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Your Classes", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p><img src=\":/newPrefix/copy.png\"/></p></body></html>", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
