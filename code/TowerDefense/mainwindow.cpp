#include "mainwindow.h"
#include "Enemy.h"
#include "Tower.h"
#include "towerslot.h"

#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    vida(100),
    dinheiro(50),
    numeroDaOnda(1),
    inimigosRestantesNaOnda(0),
    inimigosVivos(0),
    jogoRodando(false)
{
    resize(800, 600);                                       // tamanho da janela

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 600, 600);                    // tamanho da área do jogo

    view = new QGraphicsView(scene);
    view->setFixedSize(600, 600);                           // fixa o tamanho do jogo

    setupInterface();                                       // cria interface lateral

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(view);
    mainLayout->addWidget(sidePanel);
    setCentralWidget(centralWidget);                      // Layout com a área do jogo + painel lateral

    atualizarHUD();                                       // atualiza a interface com vida e dinheiro
    criarMapa();                                          // desenha o mapa com os caminhos

    timerInimigos = new QTimer(this);                     // timer que gera inimigos
    connect(timerInimigos, &QTimer::timeout, this, &MainWindow::gerarInimigo);
}

MainWindow::~MainWindow() {}

void MainWindow::setupInterface()
{
    sidePanel = new QWidget;                                // cria a interface lateral
    QVBoxLayout *layout = new QVBoxLayout;
    vidaLabel = new QLabel;
    dinheiroLabel = new QLabel;
    startButton = new QPushButton("Iniciar Onda 1");
    comprarTorreButton = new QPushButton("Comprar Torre");

    layout->addWidget(vidaLabel);
    layout->addWidget(dinheiroLabel);
    layout->addSpacing(20);
    layout->addWidget(startButton);
    layout->addWidget(comprarTorreButton);
    layout->addStretch();                                  //Empurra os widgets para o topo

    sidePanel->setLayout(layout);
    sidePanel->setFixedWidth(180);

    connect(comprarTorreButton, &QPushButton::clicked, this, &MainWindow::on_comprarTorre_clicked);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
}

void MainWindow::atualizarHUD()
{
    vidaLabel->setText("Vida: " + QString::number(vida));               // Atualiza os rótulos de vida e dinheiro
    dinheiroLabel->setText("Dinheiro: $" + QString::number(dinheiro));
}

void MainWindow::on_comprarTorre_clicked()
{
 // Apenas exibe instrução. A lógica de compra está em slotClicado.
}

void MainWindow::criarMapa()
{
    int larguraBloco = 50; // tamanho dos quadrados do mapa
    int linhas = 15;
    int colunas = 15;

    QPixmap terrenoImg(":/imagens/grama.png");          // define o fundo do mapa
    QPixmap caminhoImg(":/imagens/caminho3.png");

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            QGraphicsPixmapItem *bloco;

            bool isCaminhoHorizontal = (i == 3 && j <= 9);    // define caminho dos inimigos
            bool isCaminhoVertical = (j == 9 && i >= 3);

            if (isCaminhoHorizontal || isCaminhoVertical) {
                bloco = new QGraphicsPixmapItem(caminhoImg);
            } else {
                bloco = new QGraphicsPixmapItem(terrenoImg);
            }

            bloco->setPos(j * larguraBloco, i * larguraBloco);
            scene->addItem(bloco);
        }
    }

    caminho.clear(); // cria o caminho que os inimigos vão andar
    caminho << QPointF(0, 150)
            << QPointF(50, 150)
            << QPointF(100, 150)
            << QPointF(150, 150)
            << QPointF(200, 150)
            << QPointF(250, 150)
            << QPointF(300, 150)
            << QPointF(350, 150)
            << QPointF(415, 150)
            << QPointF(415, 200)
            << QPointF(415, 250)
            << QPointF(415, 300)
            << QPointF(415, 350)
            << QPointF(415, 400)
            << QPointF(415, 450)
            << QPointF(415, 500)
            << QPointF(415, 550);

    QList<QPointF> posicoesSlots = { // define a posição  validas para colocar aas torres
        QPointF(0, 100),
        QPointF(50, 100),
        QPointF(100, 100),
        QPointF(150, 100),
        QPointF(200, 100),
        QPointF(250, 100),
        QPointF(300, 100),
        QPointF(350, 100),
        QPointF(400, 100),
        QPointF(450, 100),
        QPointF(500, 100),
        QPointF(500, 150),
        QPointF(500, 200),
        QPointF(500, 250),
        QPointF(500, 300),
        QPointF(500, 350),
        QPointF(500, 400),
        QPointF(500, 450),
        QPointF(500, 500),
        QPointF(500, 550),
        QPointF(0, 200),
        QPointF(50, 200),
        QPointF(100, 200),
        QPointF(150, 200),
        QPointF(200, 200),
        QPointF(250, 200),
        QPointF(300, 200),
        QPointF(350, 200),
        QPointF(400, 200),
        QPointF(400, 250),
        QPointF(400, 300),
        QPointF(400, 350),
        QPointF(400, 400),
        QPointF(400, 450),
        QPointF(400, 500),
        QPointF(400, 550)
    };

    for (const QPointF &pos : posicoesSlots) { // adiciona os slots  no mapa
        TowerSlot *slot = new TowerSlot();
        slot->setPos(pos);
        connect(slot, &TowerSlot::clicado, this, &MainWindow::slotClicado);
        scene->addItem(slot);
        listaSlots.append(slot);
    }
}

void MainWindow::slotClicado(TowerSlot *slot)
{
    if (dinheiro >= 30 && !slot->estaOcupado()) { //comprar e posicionar torre se tiver dinheiro e o slot estiver livre
        Tower *torre = new Tower();

        QRectF torreRect = torre->boundingRect();
        QPointF posSlot = slot->pos();
        QPointF ajuste(
            (50 - torreRect.width()) / 2,
            (50 - torreRect.height()) / 2
            );

        torre->setPos(posSlot + ajuste);
        scene->addItem(torre);
        listaTorres.append(torre);

        slot->ocupar();
        dinheiro -= 30;
        atualizarHUD();
    }
}

void MainWindow::removerTodasAsTorres()   // Remove todas as torres e libera os slots
{
    for (Tower *torre : listaTorres) {
        scene->removeItem(torre);
        delete torre;
    }
    listaTorres.clear();

    for (TowerSlot *slot : listaSlots) {
        slot->liberar();
    }
}

void MainWindow::iniciarJogo()
{
    if (jogoRodando)
        return;

    jogoRodando = true;
    startButton->setEnabled(false);
    startButton->setText("Jogo em andamento");

    iniciarOnda();
}

void MainWindow::reiniciarJogo() // reseta o jogo para o inicio
{
    vida = 100;
    dinheiro = 50;
    numeroDaOnda = 1;

    atualizarHUD();
    removerTodasAsTorres();

    jogoRodando = false;

    disconnect(startButton, nullptr, nullptr, nullptr);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::iniciarJogo);

    startButton->setEnabled(true);
    startButton->setText("Iniciar Onda 1");
}

void MainWindow::iniciarOnda()
{
    if (vida <= 0)
        return;

    inimigosRestantesNaOnda = numeroDaOnda + 2; //número de inimigos por onda aumenta(1) com o número da onda
    inimigosVivos = 0;
    timerInimigos->start(1000); // gera inimigos a cada 1s
}

void MainWindow::gerarInimigo()
{
    if (inimigosRestantesNaOnda <= 0) {
        timerInimigos->stop();
        return;
    }

    Enemy *enemy = new Enemy(caminho); //Cria inimigo e define callbacks de fim do caminho e morte
    enemy->setScale(0.3);

    inimigosRestantesNaOnda--;
    inimigosVivos++;

    enemy->setCallbackOnFinish([this, enemy]() {
        inimigosVivos--;
        inimigoChegouAoFim();

        scene->removeItem(enemy);
        enemy->deleteLater();

        verificarFimOnda();
    });

    enemy->onMorte = [this, enemy]() {
        inimigosVivos--;
        dinheiro += 10;
        atualizarHUD();

        scene->removeItem(enemy);
        enemy->deleteLater();

        verificarFimOnda();
    };

    scene->addItem(enemy);
}

void MainWindow::verificarFimOnda() //se todos os inimigos chegarem no fim do mapa inicia proxima onda
{
    if (inimigosRestantesNaOnda == 0 && inimigosVivos == 0 && vida > 0) {
        jogoRodando = false;
        startButton->setEnabled(true);
        startButton->setText(QString("Iniciar Onda %1").arg(++numeroDaOnda));
    }
}

void MainWindow::inimigoChegouAoFim()
{
    vida -= 30; // reduz a vida se o inimigo chegar ao fim
    atualizarHUD();

    if (vida <= 0) {
        QMessageBox::information(this, "Derrota", "Você perdeu!");
        timerInimigos->stop();
        jogoRodando = false;

        disconnect(startButton, nullptr, nullptr, nullptr);
        connect(startButton, &QPushButton::clicked, this, &MainWindow::reiniciarJogo);

        startButton->setEnabled(true);
        startButton->setText("Reiniciar Jogo");
    }
}
