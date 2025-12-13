#include "mainwindow.h"
#include <QPainter>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(80 * scale, 25 * scale);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer->start(15); 
}

MainWindow::~MainWindow() {
}

void MainWindow::gameLoop() {
    game.update();
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        game.handleInput(0, true);
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        game.handleInput(1, true);
    } else if (event->key() == Qt::Key_Space) {
        game.handleInput(2, true);
    } else if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        game.handleInput(0, false);
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        game.handleInput(1, false);
    } else if (event->key() == Qt::Key_Space) {
        game.handleInput(2, false);
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    QColor bgColor, fgColor;
    int level = game.getLevel();
    
    if (level == 1) {
        bgColor = Qt::blue;
        fgColor = Qt::white;
    } else if (level == 2) {
        bgColor = Qt::red;
        fgColor = Qt::yellow;
    } else {
        bgColor = Qt::green;
        fgColor = Qt::black;
    }
    
    painter.fillRect(rect(), bgColor);
    
    painter.setPen(Qt::NoPen);
    painter.setBrush(fgColor);
    
    auto drawObject = [&](const TObject& obj) {
        QRectF rect(obj.x * scale, obj.y * scale, obj.width * scale, obj.height * scale);
        
        if (obj.cType == '@') { 
            painter.setBrush(Qt::magenta); 
        } else if (obj.cType == 'o') { 
            painter.setBrush(Qt::darkMagenta);
        } else if (obj.cType == '$') { 
            painter.setBrush(Qt::yellow);
        } else if (obj.cType == '+') { 
            painter.setBrush(Qt::cyan);
        } else {
            painter.setBrush(fgColor);
        }
        
        painter.drawRect(rect);
        
        painter.setPen(Qt::black);
        painter.drawText(rect, Qt::AlignCenter, QString(obj.cType));
        painter.setPen(Qt::NoPen);
    };
    
    for (const auto& brick : game.getBricks()) {
        drawObject(brick);
    }
    
    for (const auto& moving : game.getMovings()) {
        drawObject(moving);
    }
    
    drawObject(game.getMario());
    
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(10, 30, QString("Score: %1  Level: %2").arg(game.getScore()).arg(game.getLevel()));
}
