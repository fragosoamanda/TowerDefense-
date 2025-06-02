#include "map.h"


Map::Map(int largura, int altura, QGraphicsScene* scene):
              largura(largura),
              altura(altura),
              scene(scene){}
void Map::start(){
     
}
void Map::update(){
       for(Enemy* enemy: inimigos){              //atualiza inimigos 
              enemy->move();
       }
       for(Projetil* projetil: projeteis){       //atualiza projeteis 
              projetil->move();
       }
}

void Map::addTower(Tower* tower){  //adiciiona torre no mapa
       torres.push_back(tower);
       scene->addItem(tower);
}
void Map::addEnemy(Enemy* enemy){    //adiciona inimigos no mapa
       inimigos.push_back(enemy);
       scene->addItem(enemy);
}
void Map::adicionarProjetil(Projetil* projetil) { //adiciona projeteis no mapa
    projeteis.push_back(projetil);
    scene->addItem(projetil);
}
int Map::getLargura(){
       return largura;
}
int Map::GetAltura(){
       return altura;
}
