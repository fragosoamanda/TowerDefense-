#ifndef ENEMY_H
#define ENEMY
#include "Posicao.h"

class Enemy{
private:
    int vida;
    float velocidade;
    Posicao posicao;    
    
public: 
    Enemy(int vida, float velocidade, const Posicao& posicao);
    bool SofrerDano(int dano); 
    void mover();                   // move pelo caminho definido 


    int getVida() const;            //retorna vida
    float getVelocidade() const;    // retorna velocidade
    Posicao getPosicao() const;     // retorna a posição 
};
#endif 