#ifndef JOGADOR_H
#define JOGADOR
#include "Tower.h"

class Jogador{
private:
    int vida;
    Tower tower;
    
public:

     Jogador(int vida);             // define vida inicial 
     void ComprarTorres(Tower tower);
     int getVida() const;             //retorna vida do jogador 

};

#endif 