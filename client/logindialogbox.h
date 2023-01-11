#ifndef LOGINDIALOGBOX_H
#define LOGINDIALOGBOX_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

#include "mainwindow.h"

class LoginDialogBox : public QDialog
{
public:
    LoginDialogBox(MainWindow* ref, bool hideInfo = false);
    ~LoginDialogBox();

    void accept();

private:
    QLineEdit* m_LoginField;
    QLineEdit* m_PasswordField;
    QLabel* m_ErrorLabel;
    QLabel* m_Info;
    MainWindow* m_Ref;
};

#endif // LOGINDIALOGBOX_H
