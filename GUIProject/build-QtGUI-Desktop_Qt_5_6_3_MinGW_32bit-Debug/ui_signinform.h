/********************************************************************************
** Form generated from reading UI file 'signinform.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNINFORM_H
#define UI_SIGNINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignInForm
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignInForm)
    {
        if (SignInForm->objectName().isEmpty())
            SignInForm->setObjectName(QStringLiteral("SignInForm"));
        SignInForm->resize(298, 219);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SignInForm->sizePolicy().hasHeightForWidth());
        SignInForm->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(SignInForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_2);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        SignInForm->setCentralWidget(centralwidget);
        lineEdit->raise();
        lineEdit->raise();
        menubar = new QMenuBar(SignInForm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 298, 17));
        SignInForm->setMenuBar(menubar);
        statusbar = new QStatusBar(SignInForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SignInForm->setStatusBar(statusbar);

        retranslateUi(SignInForm);

        QMetaObject::connectSlotsByName(SignInForm);
    } // setupUi

    void retranslateUi(QMainWindow *SignInForm)
    {
        SignInForm->setWindowTitle(QApplication::translate("SignInForm", "Sign In", Q_NULLPTR));
        label->setText(QApplication::translate("SignInForm", "Username", Q_NULLPTR));
        label_2->setText(QApplication::translate("SignInForm", "Password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SignInForm", "Login", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SignInForm", "Forgot Password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignInForm: public Ui_SignInForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNINFORM_H
