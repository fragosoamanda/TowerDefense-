#include "Enemy.h"
#include <QPixmap>
#include <QGraphicsScene>

Enemy::Enemy(const QList<QPointF> &path, QGraphicsItem *parent)             // enemy é o contrutor da classe enemy, que possui uma lista de pontos que pode seguir. o QgraphicsItem cria hierarquia  entre os objetos graficos.Caminho(path) guarda o caminho passado como atributo
    : QGraphicsPixmapItem(parent), caminho(path), indiceAtual(0)            // recebe um caminho
{
    setPixmap(QPixmap(":/imagens/Enemy.png"));                               // imagem do inimigo
    setPos(caminho[0]);                                                     // coloca o inimigo no primeiro ponto do caminho

    connect(&timerMovimento, &QTimer::timeout, this, &Enemy::mover);        // conecta o timer a função de movimento
    timerMovimento.start(50);                                               // inicia o timer com intervalo de 50ms ( velocidade do inimigo)
}

void Enemy::setCallbackOnFinish(std::function<void()> callback)             // define a função de callback que é chamada quando o inimigo chegar ao final do caminho
{
    callbackFim = callback;
}

void Enemy::mover()                                                         // função chamada a cada intervalo de tempo para mover o inimigo ao longo do caminho
{
    if (indiceAtual + 1 >= caminho.size()) {                                // verifica se o inimigo chegou ao final do caminho
        timerMovimento.stop();                                              // se chegou, para o movimento (timer)
        if (callbackFim) callbackFim();                                     // chama a função callback de fim do caminho
        return;                                                             // sai da função
    }

    QPointF destino = caminho[indiceAtual + 1];                             //  pega o proximo ponto do caminho  e a posição atual  do inimigo
    QPointF posAtual = pos();


    const qreal passo = 5.0;                                                // movimento em linha reta com passo fixo

    qreal dx = destino.x() - posAtual.x();
    qreal dy = destino.y() - posAtual.y();                                  // Calcula a distância entre a posição atual e o próximo ponto.

    qreal distancia = std::sqrt(dx*dx + dy*dy);                             // distancia ate o proximo ponto

    if (distancia <= passo) {                                               // Leva o inimigo direto ao ponto de destino
        setPos(destino);
        indiceAtual++;                                                      // avança para o proximo ponto do caminho
    } else {
        qreal nx = posAtual.x() + passo * dx / distancia;                   //move-se na direção do destino com passo constante(para x)
        qreal ny = posAtual.y() + passo * dy / distancia;                   //      // (para y)
        setPos(nx, ny);
    }
}
void Enemy::sofrerDano(int dano) {                                          // chama a função quando o inimigo sofre dano
    vida -= dano;                                                           // reduz a vida do inimgo
  qDebug()<<" Um inimigo sofreu" <<dano<< "de dano";                        // avisa quando o inimigo levar dano mostrando no console
    if (vida <= 0) {                                                        // se a vida chegar a 0 o inimigo morre

        if (onMorte) onMorte();
        if (scene()) scene()->removeItem(this);                             // remove o inimigo da cena
        delete this;                                                        // deleta o objeto

    }
}
