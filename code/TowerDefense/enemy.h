#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>                                                  // permite exibir imagens em uma cena
#include <QTimer>                                                               // controla o tempo para a animação
#include <QList>                                                                // armazena pontos do caminho
#include <QPointF>                                                              // Representa coordenadas (x, y) no plano 2D
#include <functional>                                                           // Permite o uso de funções lambda e callbacks


class Enemy : public QObject, public QGraphicsPixmapItem                       // a clase enemy herda QObjects e QGraphicsPixmapItem
{
    Q_OBJECT                                                                   // necessario para usar o sistema de objetos do QT

private:
    QList<QPointF> caminho;                                                     // lista de pontos que define o caminho do inimigo
    QTimer timerMovimento;                                                      // timer para controlar o movimento do inimigo
    std::function<void()> callbackFim;                                          // Callback chamado ao fim do caminho, quando ele chegar ao fim
    int vida = 30;                                                              // Vida inicial do inimigo
    int indiceAtual;                                                            // Índice do ponto atual no caminho
    void mover();                                                               // slot chamado  pelo timer para mover o inimigo

public:

    Enemy(const QList<QPointF> &path, QGraphicsItem *parent = nullptr);         //Construtor Enemy, que  recebe o path: caminho para o item deve seguir, e  parent: item grafico pai. ele inicia a posição , configura o timer e começa o movimento
    void setCallbackOnFinish(std::function<void()> callback);                   //define qual  função  deve ser executada quando o inimigo chega no final do caminho (callback)
    void sofrerDano(int dano);                                                  // para dar dano ao inimigo
    std::function<void()> onMorte;                                              // função chamada quando o inimigo morre.Armazena qualque tipo de função(aumenta dinheiro, atualiza interface...)

};

#endif // ENEMY_H
