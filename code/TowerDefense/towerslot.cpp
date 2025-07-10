#include "towerslot.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QColor>
#include <QPen>


TowerSlot::TowerSlot(QGraphicsItem *parent) // Para poder posicionar torres no mapa
    : QGraphicsRectItem(parent)             // herda o QGraphicsRectItem
{
    setRect(0, 0, 50, 50);                       // tamanho do slot
    setBrush(QBrush(QColor(0, 0, 0, 0)));        // Slot transparente
    setPen(QPen(Qt::transparent, 2));            // Sem borda visível
    setFlag(QGraphicsItem::ItemIsSelectable);   // Permite que o item seja selecionado
    setAcceptedMouseButtons(Qt::LeftButton);    // aceita apenas cliques com o botão esquerdo
}

void TowerSlot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!ocupado) {                                 // Se o slot ainda não tem torre, emite o sinal para que MainWindow saiba que foi clicado
        emit clicado(this);
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void TowerSlot::liberar()
{
    ocupado = false;                                // Libera o slot para uma nova torre
}
