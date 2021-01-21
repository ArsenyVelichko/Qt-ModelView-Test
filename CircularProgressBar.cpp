//
// Created by awesyr on 21.01.2021.
//

#include <QPainter>
#include "CircularProgressBar.h"

CircularProgressBar::CircularProgressBar(int radius, QWidget *parent) : QProgressBar(parent) {
    setFixedSize(radius, radius);
}

void CircularProgressBar::paintEvent(QPaintEvent *) {
    qreal percentage = (value() - minimum()) / (qreal) (maximum() - minimum());
    int startAngle = 90;
    int spanAngle = 360.0 * percentage;
    int penWidth = 10;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, penWidth));
    QRect paintRect = rect().adjusted(penWidth, penWidth, -penWidth, -penWidth);
    painter.drawArc(paintRect, startAngle * 16 , -spanAngle * 16);
}


