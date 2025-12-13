#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;

private slots:
    void onLoginClicked();

private:
    QLineEdit *usernameEdit;
};

#endif
