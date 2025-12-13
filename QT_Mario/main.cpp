#include <QApplication>
#include "mainwindow.h"
#include "logindialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow window;
        window.setWindowTitle("Super Mario - Player: " + login.getUsername());
        window.show();
        return app.exec();
    }
    
    return 0;
}
