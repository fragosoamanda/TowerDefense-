#ifndef TOWERSLOT_H
#define TOWERSLOT_H

#include <QGraphicsRectItem>                                                    // permite que o slot seja exibido como um retangulo
#include <QObject>

class TowerSlot : public QObject, public QGraphicsRectItem                      // Classe TowerSlot herda o metodo QObject e QGraphicRectItem
{
    Q_OBJECT
private:
    bool ocupado = false;                                                       // indica se o slot já possui uma torre
    void mousePressEvent(QGraphicsSceneMouseEvent *event);                      // metodo sobrescrito que responde ao clique do mouse.

public:
    TowerSlot(QGraphicsItem *parent = nullptr);                                 // Construtor que aceita um item pai opcional. Nullptr é um ponteiro nulo
    bool estaOcupado() const {
        return ocupado;
    }                                                                           //retorna se o slot está ocupado ou não
    void ocupar() {
        ocupado = true;
    }                                                                            //marca o slot como ocupado  quando ja tiver torre
    void liberar();                                                             // slot livre( quando jogo reinicia)

signals:
    void clicado(TowerSlot* slot);                                              // Sinal emitido quando o slot é clicado. Passa o proprio slot como parametro de identificação. Permite que os ooutros componentes do jogo reajam ao clique


};

#endif // TOWERSLOT_H
