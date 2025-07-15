#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>                                          //permite exibir imagens em umacena grafica
#include <QGraphicsEllipseItem>                                         //desenha o range da torre como uma elipse
#include <QGraphicsSceneMouseEvent>                                     // permite utilizar o mouse
#include <QObject>

class Tower : public QObject, public QGraphicsPixmapItem {              // classe tower herda QObject e QGraphicspixmapItem
    Q_OBJECT

private:
    QGraphicsEllipseItem *range;                                        // Armazena um ponteiro para o item que representa o range da torre visualmente

public:
    Tower();                                                            // construtor padrão que inicializa a torre
    void attack();                                                      //faz a torre atacar um inimigo
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;     //metodo sobrescrito que permite interação com o mouse


};

#endif // TOWER_H
