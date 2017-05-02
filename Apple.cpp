#include "Apple.h"
#include <QBrush>

Apple::Apple(QGraphicsItem *parent){

    setRect(5, 5, 40, 40);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}
