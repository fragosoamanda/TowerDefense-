#include "Tower.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "enemy.h"
#include "projetil.h"

Tower::Tower() {
    // Define imagem da torre
    setPixmap(QPixmap(":/imagens/Tower.png").scaled(50, 70));   // ajuda o tamanho da torre
    setOffset(0, 0);                                            // Centraliza a torre na posição onde for adicionada na cena

    // Criar o range da torre
    range = new QGraphicsEllipseItem(this);
    range->setRect(-50, -50, 150, 150);                         // Raio de 75 pixels
    range->setPen(QPen(Qt::DashLine));                          // linha tracejada para a borda
    range->setBrush(QBrush(QColor(255, 192, 203, 100)));        // define a cor do range, nesse caso rosa translúcido
    range->setVisible(false);                                   // Oculto, aparece apenas se clicar na torre

    // Criar timer de ataque
    QTimer *attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, &Tower::attack);
    attackTimer->start(1000);                                   // Atira a cada 1 segundo
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    range->setVisible(!range->isVisible());                     // Alterna visibilidade do range ao clicar
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Tower::attack() {
    QList<QGraphicsItem *> collidingItemsList = range->collidingItems(); // obtém todos os itens que colidem com o range da torre

    if (collidingItemsList.isEmpty())                           //Se não há nenhum item dentro do alcance, não atira
        return;

    Enemy *target = nullptr;


    for (QGraphicsItem *item : collidingItemsList) {            // Encontrar o primeiro inimigo no range
        Enemy *enemy = dynamic_cast<Enemy *>(item);
        if (enemy) {
            target = enemy;                                      // pega o primeiro inimigo encontrado
            break;
        }
    }


    if (target) {

        Projetil *projetil = new Projetil(target);  // Criar um projetil e setar o alvo
        projetil->setPos(this->pos());              // Ajuste de posição: projetil nasce no centro da torre

        scene()->addItem(projetil);                 // adiciona o projetil na cena

        qDebug() << "Projetil lançado!";            // mostra que o projetil foi lançado
    }
}
