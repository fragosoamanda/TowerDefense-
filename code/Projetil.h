#ifndef PROJETIL_h
#define PROJETIL
#include "Enemy.h"
// #include "Tower" 

class Projetil{
private:
    int dano;
    float velocidade;
    Enemy enemy; 
  
public: 
    Projetil (int dano, float velocidade, const Enemy& enemy);
    bool AtingirAlvo(int dano); 
    void mover();                   // move pelo caminho definido 

};
#endif 