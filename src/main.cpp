#include <QApplication>

#include "keyboard_window.hpp"
#include "start_dialog.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
	
    biv::StartDialog dialog;
    
    QObject::connect(&dialog, &QDialog::accepted, [&]() {
        biv::KeyBoardWindow* keyboard_window = new biv::KeyBoardWindow();
        keyboard_window->setAttribute(Qt::WA_DeleteOnClose);
        keyboard_window->show();
    });

    dialog.show();
    return app.exec();
}
