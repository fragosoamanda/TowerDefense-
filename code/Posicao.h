#ifndef POSICAO_H
#define POSICAO

class Posicao{
private:
    int x; // eixo horizontal
    int y; // eixo vertical 

public: 
    Posicao(int x, int y);

    void setY(int y);   //define coordenada y
    void setX(int x);  //define coordenada X
     
    int getX() const;  //retorna coordenada X
    int getY() const;  // retorna coordenada Y

}; 


#endif 
