#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>                                         //desenha o range da torre como uma elipse
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    QGraphicsEllipseItem *range;                                        // representa o range da torre visualmente

public:
    Tower();
    void attack();                                                      //faz a torre atacar um inimigo
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;     // para mostrar o range


};

#endif // TOWER_H
