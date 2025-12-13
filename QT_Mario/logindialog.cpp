#include "logindialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFormLayout>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Super Mario Login");
    setFixedSize(300, 150);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Enter your name");
    
    formLayout->addRow("Username:", usernameEdit);
    
    mainLayout->addLayout(formLayout);

    QPushButton *loginButton = new QPushButton("Start Game", this);
    mainLayout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}

void LoginDialog::onLoginClicked() {
    if (usernameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter a valid username.");
        return;
    }
    accept(); 
}

QString LoginDialog::getUsername() const {
    return usernameEdit->text();
}
