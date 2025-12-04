#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QTextEdit();
	display->setMinimumHeight(200);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setText("Помоги мне заработать лучше...");

	keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}

int normalize_key(int key) {
    switch (key) {
        case 1049: return Qt::Key_Q; // Й
        case 1062: return Qt::Key_W; // Ц
        case 1059: return Qt::Key_E; // У
        case 1050: return Qt::Key_R; // К
        case 1045: return Qt::Key_T; // Е
        case 1053: return Qt::Key_Y; // Н
        case 1043: return Qt::Key_U; // Г
        case 1064: return Qt::Key_I; // Ш
        case 1065: return Qt::Key_O; // Щ
        case 1047: return Qt::Key_P; // З
        case 1061: return Qt::Key_BracketLeft; // Х
        case 1066: return Qt::Key_BracketRight; // Ъ
        case 1060: return Qt::Key_A; // Ф
        case 1067: return Qt::Key_S; // Ы
        case 1042: return Qt::Key_D; // В
        case 1040: return Qt::Key_F; // А
        case 1055: return Qt::Key_G; // П
        case 1056: return Qt::Key_H; // Р
        case 1054: return Qt::Key_J; // О
        case 1051: return Qt::Key_K; // Л
        case 1044: return Qt::Key_L; // Д
        case 1046: return Qt::Key_Semicolon; // Ж
        case 1069: return Qt::Key_Apostrophe; // Э
        case 1071: return Qt::Key_Z; // Я
        case 1063: return Qt::Key_X; // Ч
        case 1057: return Qt::Key_C; // С
        case 1052: return Qt::Key_V; // М
        case 1048: return Qt::Key_B; // И
        case 1058: return Qt::Key_N; // Т
        case 1068: return Qt::Key_M; // Ь
        case 1041: return Qt::Key_Comma; // Б
        case 1070: return Qt::Key_Period; // Ю
        case 1025: return Qt::Key_QuoteLeft; // Ё
        default: return key;
    }
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	const int key = normalize_key(event->key());
	
	if (keyboard->is_key_allowed(key) || key == Qt::Key_Delete) {
		if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
			QString text = display->toPlainText();
			text.chop(1);
			display->setText(text);
			display->moveCursor(QTextCursor::End);
			keyboard->animate_button(Qt::Key_Backspace);
		} else if (key == Qt::Key_Space) {
			display->setText(display->toPlainText() + " ");
			display->moveCursor(QTextCursor::End);
			keyboard->animate_button(key);
		} else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
			display->setText(display->toPlainText() + "\n");
			display->moveCursor(QTextCursor::End);
			keyboard->animate_button(key);
		} else {
			QString text = keyboard->get_key_text(key);
			const QString sys_text = event->text();

			if (!sys_text.isEmpty() && (sys_text == sys_text.toUpper() && sys_text != sys_text.toLower())) {
			} else {
				text = text.toLower();
			}

			display->setText(display->toPlainText() + text);
			display->moveCursor(QTextCursor::End);
			keyboard->animate_button(key);
		}
	}
}
