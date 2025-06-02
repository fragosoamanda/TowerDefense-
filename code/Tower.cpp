#include "Tower.h"

#include <QGraphicsScene>
#include <QList>

Tower::Tower(int dano, float alcance, float TempRecarga, const Posicao& posicao ):
    dano(dano),
    alcance(alcance),
    TempRecarga(TempRecarga),
    posicao(posicao) {


setPos(posicao.x, posicao.y);                                           // posiciona a torre 

 timer = new Qtimer(this);                                              // cria o temporizador que vai controlar a recarga das torres 
 connect(timer, &QTimer::timeout, this, &Tower::procuraAlvo);           // conecta o temporizador ao metodo de procurar alvos 
 timer->start(static_cast<int>(TempRecarga));                           // inicia o temporizador 
}

void Tower::procuraAlvo(){                                              // procura alvo 
    QList<QGraphicsItem*>itens = scene()->itens();                      // pega os itens que estao na cena 
    for(QGraphicsItem* item: itens ){                                   // varre cada um dos itens 
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if(enemy){                                                      // caso ache um inimigo valido 
            float distancia = distancia(posicao, enemy->getPosicao());  // calcula distancia da torre ate o inimigo
            if (distancia <= alcance){                                  // se estiver no alcance, ataca 
                atacar(enemy);
                break; 
            }
        }
    }
}
void Tower::ataca(Enemy* enemy){
    enemy->recebeDano(dano);                                             //aplica dano no inimigo 
}

float Tower::distancia(const Posicao& p1, const Posicao& p2){
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return qSqrt(dx*dx + dy*dy);
}
