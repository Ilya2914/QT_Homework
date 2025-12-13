#include <QApplication>

#include "keyboard_window.hpp"
#include "start_dialog.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
	
    biv::StartDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        biv::KeyBoardWindow keyboard_window;
        keyboard_window.show();
        return app.exec();
    }

    return 0;
}
