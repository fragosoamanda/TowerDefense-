#ifndef TOWER_H
#define TOWER 
#include "Posicao.h"
#include "Enemy.h"
#include <time.h>

class Tower{
private:
    int dano;
    float alcance;
    float TempRecarga;  //tempo entre 2 ataques consecutivos
    float UltimoAtck;   //ultimo ataque para controlar a recarga
    Posicao posicao;    //posição no mapa
    
public: 
    Tower(int dano, float alcance, float TempRecarga, const Posicao& posicao);
    bool podeAtacar();              // verifica se pode atacar 
    
    void atacar(Enemy& Enemy);  // ataca o inimigo se estiver no range
    float distancia(const Posicao& p1, const Posicao& p2); // calcula a distancia entre dois pontos para saber se o inimigo esta no range
    Posicao getPosicao() const;     // retorna a posição 
};
#endif 