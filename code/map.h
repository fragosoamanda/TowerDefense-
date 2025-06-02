#ifndef MAP_H
#define MAP_H
#include "Enemy.h"
#include "Tower.h"
#include "Projetil.h"
#include <vector>
#include <QGraphicsScene>

class Map{
private:
     int largura;
     int altura;
    QGraphicsScene* scene; 

    std::vector<Enemy*> inimigos;       // lista de inimigos
    std::vector<Tower*> torres;         // lista de torres
    std::vector<Projetil*> projeteis;   // lista de projeteis
public:

    Map(int largura, int altura, QGraphicsScene* scene);

    void start ();
    void update();

    int GetLargura();
    int GetAltura();

    void addTower(Tower* tower);
    void addEnemy(Enemy* enemy);
    void addProjetil(Projetil* projetil);

    
};
#endif 