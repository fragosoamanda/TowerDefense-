#include "Projetil.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <qmath.h>
#include "Enemy.h"

Projetil::Projetil(Enemy *alvo) {
    setPixmap(QPixmap(":/imagens/projetil.png").scaled(60, 60));    //define a imagem do projétil  e o tamanho
    this->alvo = alvo;                                              // armazena o ponteiro para o inimigo que será o alvo

    QTimer *moveTimer = new QTimer(this);                           //cria um timer para mover o projétil
    connect(moveTimer, &QTimer::timeout, this, &Projetil::move);
    moveTimer->start(50);                                           // define o intervalo de tempo
}

void Projetil::move() {
    if (!alvo || !scene()->items().contains(alvo)) {                // se o alvo sair de cena, o projétil tambem  sai
        scene()->removeItem(this);                                  // remove da cena
        delete this;
        return;
    }


    qreal dx = alvo->x() - x();                                     // Calcular direção do projetil
    qreal dy = alvo->y() - y();
    qreal distancia = qSqrt(dx * dx + dy * dy);                     // distância euclidiana

    if (distancia < 10) {                                           // Se chegou perto o suficiente
        alvo->sofrerDano(10);                                       // dano do projetil de 10
        scene()->removeItem(this);                                  // remove o projétil da cena
        delete this;
        return;
    }


    int velocidade = 10;
    setPos(x() + velocidade * dx / distancia, y() + velocidade * dy / distancia); //move o projétil em direção ao alvo, mantendo a mesma direção
}
