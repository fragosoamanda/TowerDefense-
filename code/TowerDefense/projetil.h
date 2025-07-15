#ifndef PROJETIL_H
#define PROJETIL_H

#include <QGraphicsPixmapItem>                                    //permite exibir imagens em uma cena
#include <QObject>
#include "Enemy.h"

class Projetil : public QObject, public QGraphicsPixmapItem {   // a clase projetil herda QObjects e QGraphicsPixmapItem
    Q_OBJECT

private:
    Enemy *alvo;                                                //  armazena um ponteiro para o alvo que o projétil vai perseguir(inimigo)

public:
    Projetil(Enemy *alvo);                                      //Construtor que recebe um ponteiro para o alvo do projétil
     void move();                                               //método  para mover  o projetil  em direção ao alvo

};

#endif // PROJETIL_H
