#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QtMath>
#include "Enemy.h"
#include "Posicao.h"

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private:
    int dano;
    float alcance;
    float tempRecarga;  // tempo entre ataques em ms
    Posicao posicao;

    QTimer* timer;      // temporizador para ataques

public:
    Tower(int dano, float alcance, float tempRecarga, const Posicao& posicao);

    void procurarAlvo();               // verifica se há inimigos no alcance
    void atacar(Enemy* enemy);         // ataca um inimigo

    float distancia(const Posicao& p1, const Posicao& p2);
    Posicao getPosicao() const;

signals:
    void disparou();

};

#endif // TOWER_H
