#include <QDialogButtonBox>
#include <QVBoxLayout>

#include "logindialogbox.h"
#include "mainwindow.h"

LoginDialogBox::LoginDialogBox(MainWindow* ref, bool hideInfo) : m_Ref(ref)
{
    setWindowTitle("Login");
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    m_Info = new QLabel("You must login to see information about this book");
    m_LoginField = new QLineEdit();
    m_PasswordField = new QLineEdit();
    m_ErrorLabel = new QLabel();
    m_ErrorLabel->setStyleSheet("color: red;");
    m_ErrorLabel->hide();
    if(hideInfo) {
        m_Info->hide();
    }

    m_LoginField->setMaximumHeight(30);
    m_PasswordField->setMaximumHeight(30);

    m_LoginField->setPlaceholderText("Username");
    m_PasswordField->setPlaceholderText("Password");
    m_PasswordField->setEchoMode(QLineEdit::Password);


    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    mainLayout->addWidget(m_Info);
    mainLayout->addWidget(m_ErrorLabel);
    mainLayout->addWidget(m_LoginField);
    mainLayout->addWidget(m_PasswordField);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    exec();
}

LoginDialogBox::~LoginDialogBox() {
    delete m_LoginField;
    delete m_PasswordField;
    delete m_ErrorLabel;
    delete m_Info;
}

void LoginDialogBox::accept() {
    if(m_LoginField->text() == "" || m_PasswordField->text() == "") {
        m_ErrorLabel->setText("You must fill all fields");
        m_ErrorLabel->show();
        return;
    }
    if(MainWindow::client.GetUser().GetId() == -1) {
        MainWindow::client.Login(m_LoginField->text().toStdString(), m_PasswordField->text().toStdString());
    }
    if(MainWindow::client.GetUser().GetId() == -1) {
        m_ErrorLabel->setText("Username or password are wrong");
        m_ErrorLabel->show();
        return;
    }
    m_Ref->Populate();
    QDialog::accept();
}
