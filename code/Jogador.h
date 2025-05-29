#ifndef JOGADOR_H
#define JOGADOR
#include "Tower.h"

class Jogador{
private:
    int vida;
    Tower tower;
    
public: 
     Jogador(int vida, const Tower& tower);
     void ComprarTorres(Tower tower)
     int  getVida() const;            //retorna vida

};

#endif 