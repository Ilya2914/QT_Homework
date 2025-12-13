#include "keyboard.hpp"
#include <Qt>
#include <QTimer>
#include <unordered_set>

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
	: button_width(width / 29), QWidget(parent) {

	keyboard_data = new KeyBoardData();
	
    QGridLayout* keys_layout = new QGridLayout(this);
	keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
	
	create_buttons(keyboard_data->get_line1(), keys_layout, 0, 0);
	
	KeyBoardButton* backspace_btn = new KeyBoardButton("Удалить");
	backspace_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(backspace_btn, 0, 26, 2, 3);
	buttons[Qt::Key_Backspace] = backspace_btn;

	KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
	tab_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(tab_btn, 2, 0, 2, 5);
	buttons[Qt::Key_Tab] = tab_btn;

	create_buttons(keyboard_data->get_line2(), keys_layout, 2, 5);
	
	KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
	caps_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
	buttons[Qt::Key_CapsLock] = caps_btn;
	
	create_buttons(keyboard_data->get_line3(), keys_layout, 4, 4);
	
	KeyBoardButton* enter_btn = new KeyBoardButton("Enter");
	enter_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(enter_btn, 4, 26, 2, 3);
	buttons[Qt::Key_Return] = enter_btn;
	buttons[Qt::Key_Enter] = enter_btn;
	
	KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
	left_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
	
	create_buttons(keyboard_data->get_line4(), keys_layout, 6, 5);
	
	KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
	right_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);

	KeyBoardButton* space = new KeyBoardButton();
	space->setMinimumSize(8 * button_width, button_width);
	keys_layout->addWidget(space, 8, 7, 2, 16);
	buttons[Qt::Key_Space] = space;

	std::unordered_set<KeyBoardButton*> connected_buttons;
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		if (connected_buttons.find(it->second) == connected_buttons.end()) {
			connect(it->second, &QPushButton::clicked, [this, code = it->first]() {
				emit pressed(code);
			});
			connected_buttons.insert(it->second);
		}
	}
}

void KeyBoard::animate_button(const int code) {
	if (buttons.count(code)) {
		KeyBoardButton* btn = buttons.at(code);
		btn->setDown(true);
		QTimer::singleShot(100, btn, [btn](){
			btn->setDown(false);
		});
	}
}

QString KeyBoard::get_key_text(const int code) const {
	if (buttons.count(code)) {
		return buttons.at(code)->text();
	}
	return "";
}

bool KeyBoard::is_key_allowed(const int code) const noexcept {
	return buttons.count(code) > 0;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
void KeyBoard::create_buttons(
	const std::vector<KeyData>& data, 
	QGridLayout* layout, 
	const int line,
	const int start_position
) {
	for (int i = 0; i < data.size(); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].text);
		btn->setMinimumSize(button_width, button_width);
        
		layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
		
		buttons[data[i].code] = btn;
	}
}
