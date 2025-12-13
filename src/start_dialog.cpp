#include "start_dialog.hpp"

#include <QPushButton>
#include <QVBoxLayout>

namespace biv {
    StartDialog::StartDialog(QWidget *parent) : QDialog(parent) {
        setWindowTitle("Добро пожаловать");
        resize(300, 200);
        
        QVBoxLayout *layout = new QVBoxLayout(this);
        
        QPushButton *startButton = new QPushButton("Начать", this);
        QPushButton *cancelButton = new QPushButton("Отмена", this);
        
        layout->addWidget(startButton);
        layout->addWidget(cancelButton);
        
        connect(startButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    }
}
