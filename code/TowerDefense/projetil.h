#ifndef PROJETIL_H
#define PROJETIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Enemy.h"

class Projetil : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    Enemy *alvo;                     // ponteiro para o alvo que o projétil vai perseguir(inimigo)

public:
    Projetil(Enemy *alvo);           //define o alvo do projétil
     void move();                    //método  para mover  o projetil  em direção ao alvo

};

#endif // PROJETIL_H
