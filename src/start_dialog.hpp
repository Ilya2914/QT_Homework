#pragma once

#include <QDialog>

namespace biv {
    class StartDialog : public QDialog {
        Q_OBJECT
    public:
        StartDialog(QWidget *parent = nullptr);
    };
}
