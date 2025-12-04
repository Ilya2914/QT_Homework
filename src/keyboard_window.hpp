#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	class KeyBoardWindow : public QWidget {
		private:
			QTextEdit* display;
			KeyBoard* keyboard;

		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;
	};
}
