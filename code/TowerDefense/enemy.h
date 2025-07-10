#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <QPointF>                                                               // Representa coordenadas (x, y) no plano 2D
#include <functional>                                                            // Permite o uso de funções lambda e callbacks


class Enemy : public QObject, public QGraphicsPixmapItem                        // QgraphicsPixmapItem permite que o inimigo seja exibido como uma imagem
{
    Q_OBJECT

private:
    QList<QPointF> caminho;                                                     // lista de pontos que define o caminho do inimigo
    int indiceAtual;                                                            // Índice do ponto atual no caminho
    QTimer timerMovimento;                                                      // timer para controlar o movimento do inimigo
    std::function<void()> callbackFim;                                          // Callback chamado ao fim do caminho
    int vida = 30;                                                              // Vida inicial do inimigo
    void mover();                                                               // slot chamado  pelo timer para mover o inimigo

public:

    Enemy(const QList<QPointF> &path, QGraphicsItem *parent = nullptr);         //construtor que recebe um caminho a ser seguido pelo inimigo
    void setCallbackOnFinish(std::function<void()> callback);                   //define uma função de callback que será chamada ao fim do trajeto
    void sofrerDano(int dano);                                                  // para dar dano ao inimigo
    std::function<void()> onMorte;                                              // função callback chamada quando o inimigo morre

};

#endif // ENEMY_H
