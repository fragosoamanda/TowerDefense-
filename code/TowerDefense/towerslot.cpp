#include "towerslot.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QColor>
#include <QPen>


TowerSlot::TowerSlot(QGraphicsItem *parent)                      //  Para poder posicionar torres no mapa
    : QGraphicsRectItem(parent)                                  //  TowerSlot herda o QGraphicsRectItem. O construtor chama o construtor da classe base como parent, o que significa que TowerSlot pode ter um pai caso deseje que ele se mova junto com outro item
{
    setRect(0, 0, 50, 50);                                      // tamanho do slot
    setBrush(QBrush(QColor(0, 0, 0, 0)));                       // Slot transparente
    setPen(QPen(Qt::transparent, 2));                           // Sem borda visível
    setFlag(QGraphicsItem::ItemIsSelectable);                   // Permite que o item seja selecionado
    setAcceptedMouseButtons(Qt::LeftButton);                    // aceita apenas cliques com o botão esquerdo
}

void TowerSlot::mousePressEvent(QGraphicsSceneMouseEvent *event) //metodo chamado automaticamente sempre que o usuário clicar no slot
{
    if (!ocupado) {                                             // Se o slot ainda não tem torre, emite o sinal para que MainWindow saiba que foi clicado (bool)
        emit clicado(this);
    }
    QGraphicsRectItem::mousePressEvent(event);                  // chama a versão original do evento classe  base, caso ela não tenha um comportamento adicional
}

void TowerSlot::liberar()                                       // masca o slot como livre novamente
{
    ocupado = false;                                            // Libera o slot para uma nova torre
}
