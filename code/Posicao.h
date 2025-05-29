#ifndef POSICAO_H
#define POSICAO_H   

class Posicao{
private:
    int x; // eixo horizontal
    int y; // eixo vertical 

public: 
    Posicao(int x = 0, int y = 0 ); // inicializando eles em 0 
    
    // define os valores das  coordenada 
    void setY(int y);   //define coordenada y
    void setX(int x);  //define coordenada X
     
    //obtem as coordenadas
    int getX() const;  //retorna coordenada X
    int getY() const;  // retorna coordenada Y

    bool operator==(const Posicao& other) const; // compara x deste objeto com x de outro objeto 
    float DistanciaPara(const Posicao& other) const; // calcula e retorna  a distancia  entre a posicao atual e a nova 
}; 


#endif 
