#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "towerslot.h"
#include "Tower.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    int vida;
    int dinheiro;
    int numeroDaOnda;
    int inimigosRestantesNaOnda;
    int inimigosVivos;
    bool jogoRodando;                   // indica se o jogo esta rodando

    void setupInterface();              // configura a interface grafica
    void atualizarHUD();                // atualiza as informações da inteface(vida e dinheiro)
    void criarMapa();                   // cria o mapa
    void verificarFimOnda();            // verifica se os inimigos chegaram ao fim do mapa
    void removerTodasAsTorres();        // remove todas as torres ao reiniciar o jogo
    void reiniciarJogo();               // reinica o jogo
    void on_comprarTorre_clicked();     // slot  chamado  ao clicar em comprar torre
    void slotClicado(TowerSlot *slot);

    void iniciarJogo();                 //inicia o jogo
    void iniciarOnda();                 //inicia uma nova onda de inimigos
    void gerarInimigo();                // cria inimigo na cena
    void inimigoChegouAoFim();          // inimigo chegou ao fim do mapa

    QGraphicsScene *scene;              // onde os elementos do jogo são desenhados
    QGraphicsView *view;
    QWidget *sidePanel;                 // interface lateral
    QLabel *vidaLabel;                  // exibe vida na interface
    QLabel *dinheiroLabel;              // exibe dinheiro na interface
    QPushButton *startButton;           // botão para iniciar o jogo
    QPushButton *comprarTorreButton;    // botão para comprar torre
    QTimer *timerInimigos;              // gera os inimigos em intervalos de tempo
    QList<TowerSlot*> listaSlots;       // slots disponiveis para colocar  torres
    QList<Tower*> listaTorres;          // lista de torres colocada no mapa
    QList<QPointF> caminho;             //caminho que os inimigos percorrem



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
