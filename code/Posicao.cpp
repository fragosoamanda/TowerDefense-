#include "Posicao.h"
#include <cmath> 


Posicao::Posicao(int x, int y) : x(x), y(y) {} // inicializa x e y 

int Posicao::getX() const {     // retorna x
    return x;
}

int Posicao::getY() const {     // retorna y 
    return y;
}


void Posicao::setX(int novoX) {    // altera valor de x 
    x = novoX;
}

void Posicao::setY(int novoY) { // altera valor de y 
    y = novoY;
}

bool Posicao::operator==(const Posicao& other) const {  // compara se duas  posições possuem as mesmas coordenadas 
    return x == other.x && y == other.y; // retorna true se x e y forem iguais 
}

float Posicao::DistanciaPara(const Posicao& other) const { // calcula a distancias entre duas posições 
    int dx = other.x - x;            // calcula a diferença nas coordenadas x
    int dy = other.y - y;            // calcula a diferença das coordenadas y
    return std::sqrt(dx*dx + dy*dy); //aplica fórmula da distância 
}