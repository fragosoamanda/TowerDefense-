#include "Tower.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>                                         // permite detectar cliques com o mouse
#include <QTimer>
#include <QDebug>
#include "enemy.h"
#include "projetil.h"

Tower::Tower() {                                                            // construtor da torre
                                                                            // Define imagem da torre
    setPixmap(QPixmap(":/imagens/Tower.png").scaled(50, 70));               // ajuda o tamanho da torre
    setOffset(0, 0);                                                        // Centraliza a torre na posição onde for adicionada na cena

    // Criar o range da torre
    range = new QGraphicsEllipseItem(this);                                 // utiliza o QGraphicsEllipseItempara criar o range em formato de elipse (objeto visual). Herda da torre, então acompanha ela
    range->setRect(-50, -50, 150, 150);                                     // Cria um raio de 75 pixels em formato de elipse
    range->setPen(QPen(Qt::DashLine));                                      // linha tracejada para a borda
    range->setBrush(QBrush(QColor(255, 192, 203, 100)));                    // define a cor do range, nesse caso rosa translúcido
    range->setVisible(false);                                               // Oculto, aparece apenas se clicar na torre

                                                                            // Criar timer de ataque
    QTimer *attackTimer = new QTimer(this);                                 // cria um timer que chama o metodo attack ( o this garante que ele ser´destruido junto com torre)
    connect(attackTimer, &QTimer::timeout, this, &Tower::attack);           // conecta o sinal timeout do canal attackTimer ao slot  attack da torre. Fazendo com que ele ataque automaticamente.
    attackTimer->start(700);                                                // Atira a cada 0.7 segundo
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event) {              // método que é chamadp sempre que o jogador clicar na torre. O QGraphicsSceneMouseEvent é um ponteiro para o evento clique que mostra onde o clique ocorreu
    range->setVisible(!range->isVisible());                                 // Alterna visibilidade do range ao clicar. Range  é o ponteiro para o item grafico que representa o alcance.
    QGraphicsPixmapItem::mousePressEvent(event);                            // chama a versao original da função base, passando como evento, para que qualquer comportamento a mais ele continue funcionando
}

void Tower::attack() {
    QList<QGraphicsItem *> collidingItemsList = range->collidingItems();    //  pede ao range todos os itens que colidem com ele, retornando uma lista de ponteiros

    if (collidingItemsList.isEmpty())                                       //Se não há nenhum item dentro do alcance, não atira
        return;

    Enemy *target = nullptr;                                                // declara um ponteiro nulo que vai guardar o primeiro inimigo

    for (QGraphicsItem *item : collidingItemsList) {                        // percorre cada item colidindo com o range e tenta fazer um dynamic_cast para o ponteiro enemy. caso for um enemy de verdada o ponteiro enemy sera difernte de nullptr e  ele vira o alvo
        Enemy *enemy = dynamic_cast<Enemy *>(item);
        if (enemy) {
            target = enemy;                                                 // pega o primeiro inimigo encontrado
            break;
        }
    }


    if (target) {

        Projetil *projetil = new Projetil(target);                          // Criar um projetil e setar o alvo
        projetil->setPos(this->pos());                                      // Ajuste de posição: projetil nasce no centro da torre

        scene()->addItem(projetil);                                         // adiciona o projetil na cena

        qDebug() << "Projetil lançado!";                                    // mostra que o projetil foi lançado no console
    }
}
