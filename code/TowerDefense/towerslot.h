#ifndef TOWERSLOT_H
#define TOWERSLOT_H

#include <QGraphicsRectItem>
#include <QObject>

class TowerSlot : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool ocupado = false;                                                       // indica se o slot já possui uma torre
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;             //chama quando  clica com o mouse no slot

public:
    TowerSlot(QGraphicsItem *parent = nullptr);
    bool estaOcupado() const { return ocupado; }                                //retorna se o slot está ocupado ou não
    void ocupar() { ocupado = true; }                                           //marca o slot como ocupado  quando ja tiver torre
    void liberar();                                                             // slot livre( quando jogo reinicia)

signals:
    void clicado(TowerSlot* slot);                                              // Sinal emitido quando o slot é clicado


};

#endif // TOWERSLOT_H
