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
			bool caps_lock_enabled = false;

		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;

		private slots:
			void process_key(int key, const QString& sys_text = "");
	};
}
