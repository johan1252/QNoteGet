/********************************************************************************
** Form generated from reading UI file 'signupform.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPFORM_H
#define UI_SIGNUPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUpForm
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QFormLayout *formLayout_4;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUpForm)
    {
        if (SignUpForm->objectName().isEmpty())
            SignUpForm->setObjectName(QStringLiteral("SignUpForm"));
        SignUpForm->resize(381, 223);
        centralwidget = new QWidget(SignUpForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(centralwidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        usernameLabel = new QLabel(centralwidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, usernameLabel);

        usernameLineEdit = new QLineEdit(centralwidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, usernameLineEdit);

        passwordLabel = new QLabel(centralwidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, passwordLineEdit);

        emailLabel = new QLabel(centralwidget);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(centralwidget);
        emailLineEdit->setObjectName(QStringLiteral("emailLineEdit"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, emailLineEdit);


        formLayout->setLayout(0, QFormLayout::FieldRole, formLayout_4);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton);

        SignUpForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignUpForm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 381, 17));
        SignUpForm->setMenuBar(menubar);
        statusbar = new QStatusBar(SignUpForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SignUpForm->setStatusBar(statusbar);

        retranslateUi(SignUpForm);

        QMetaObject::connectSlotsByName(SignUpForm);
    } // setupUi

    void retranslateUi(QMainWindow *SignUpForm)
    {
        SignUpForm->setWindowTitle(QApplication::translate("SignUpForm", "Sign Up", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("SignUpForm", "Name", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("SignUpForm", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("SignUpForm", "Password", Q_NULLPTR));
        emailLabel->setText(QApplication::translate("SignUpForm", "Email", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SignUpForm", "Sign Up", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignUpForm: public Ui_SignUpForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPFORM_H
