#include "robotwidget.h"
#include <QPainter>
#include <QMouseEvent>

RobotWidget::RobotWidget(QWidget* parent)
    : QWidget(parent), dragging(false)
{
    setFixedSize(150, 150);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void RobotWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw robot body
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRoundedRect(10, 30, 130, 110, 20, 20);

    // Draw robot head
    painter.setBrush(QBrush(Qt::gray));
    painter.drawRoundedRect(40, 0, 70, 60, 10, 10);

    // Draw robot eyes
    painter.setBrush(QBrush(Qt::white));
    painter.drawEllipse(55, 20, 10, 10);
    painter.drawEllipse(85, 20, 10, 10);

    painter.setBrush(QBrush(Qt::black));
    painter.drawEllipse(58, 23, 4, 4);
    painter.drawEllipse(88, 23, 4, 4);

    // Draw robot mouth
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(65, 40, 20, 5);
}

void RobotWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragStartPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void RobotWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (dragging) {
        move(event->globalPosition().toPoint() - dragStartPosition);
        event->accept();
    }
}

void RobotWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        event->accept();
    }
}
