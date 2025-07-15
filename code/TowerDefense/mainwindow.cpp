#include "mainwindow.h"
#include "Enemy.h"
#include "Tower.h"
#include "towerslot.h"

#include <QGraphicsPixmapItem>
#include <QHBoxLayout>                                     //organiza widgets em uma linha (horizontal).
#include <QVBoxLayout>                                     //organiza widgets em uma coluna (vertical).
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)                     // construtor principal da janela
    : QMainWindow(parent),
    vida(100),                                              // vida inicial do jogador
    dinheiro(90),                                           // dinheiro inicial do jogador
    numeroDaOnda(1),                                        // número da onda( começa na 1°)
    inimigosRestantesNaOnda(0),                             // inimigos vivos na onda( inicialmente nenhum)
    inimigosVivos(0),                                       // número de inimigos vivos (inicialmente nenhum)
    jogoRodando(false)                                      // jogo não esta rodando ao iniciar
{
    resize(800, 600);                                       // tamanho da janela

    scene = new QGraphicsScene(this);                       // cria uma nova janela para o jogo
    scene->setSceneRect(0, 0, 600, 600);                    // tamanho da área do jogo

    view = new QGraphicsView(scene);                        // cria um view para mostrar a cena
    view->setFixedSize(600, 600);                           // fixa o tamanho do jogo

    setupInterface();                                       // cria interface lateral

    QWidget *centralWidget = new QWidget(this);             // cria layout principal  que contém a área do jogo e a interfae lateral
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(view);
    mainLayout->addWidget(sidePanel);
    setCentralWidget(centralWidget);                      // Layout com a área do jogo + painel lateral

    atualizarHUD();                                       // atualiza a interface com vida e dinheiro
    criarMapa();                                          // desenha o mapa com os caminhos

    timerInimigos = new QTimer(this);                     // timer que gera inimigos
    connect(timerInimigos, &QTimer::timeout, this, &MainWindow::gerarInimigo); // conecta o timeout do objeto qtimer chamado timerinimigos e um slot  chamado gerarinimigos
}

MainWindow::~MainWindow() {}

void MainWindow::setupInterface()                                        // cria painel lateral  com os botões
{
    sidePanel = new QWidget;                                             // cria um painel Qwidget que servira como  interface
    QVBoxLayout *layout = new QVBoxLayout;                               // usa layout vertical  para organizar os elementos  de cima para baixo
    vidaLabel = new QLabel;                                              //exibe a quantidade de vida
    dinheiroLabel = new QLabel;                                          // exibe a quantidade dinheiro
    startButton = new QPushButton("Iniciar Onda 1");                     //exibe a quantidade  a onda que esta no botão
    comprarTorreButton = new QPushButton("Comprar Torre (R$50,00)");     //exibe a valor de torre no botão

    layout->addWidget(vidaLabel);                                       // adiciona os widgets no painel lateral
    layout->addWidget(dinheiroLabel);
    layout->addSpacing(20);
    layout->addWidget(startButton);
    layout->addWidget(comprarTorreButton);
    layout->addStretch();                                               //Empurra os widgets para o topo

    sidePanel->setLayout(layout);                                       // aplica layout no painel
    sidePanel->setFixedWidth(180);                                      // define sua largura

    connect(comprarTorreButton, &QPushButton::clicked, this, &MainWindow::on_comprarTorre_clicked); // quando comprarTorreButton for clicado  chama on_comprarTorre_clicked. Não adiciona a torre imediatamente , apenas sinaliza que o jogador quer comprar a torre
    connect(startButton, &QPushButton::clicked, this, &MainWindow::iniciarJogo);                    // quando startButton for clicado chama iniciarJogo
}

void MainWindow::atualizarHUD()
{
    vidaLabel->setText(" ❤️ Vida: " + QString::number(vida));                        // rótulos de vida e dinheiro
    dinheiroLabel->setText(" 🪙 Dinheiro: $" + QString::number(dinheiro));
}

void MainWindow::on_comprarTorre_clicked()
{
 // Apenas exibe instrução. A lógica de compra está em slotClicado.
}

void MainWindow::criarMapa()
{
    int larguraBloco = 50;                                                      // tamanho de cada bloco do  mapa
    int linhas = 15;
    int colunas = 15;

    QPixmap terrenoImg(":/imagens/grama.png");                                   // define o fundo do mapa(lugar onde as torres são posicionadas)
    QPixmap caminhoImg(":/imagens/caminho3.png");                                // define o fundo do mapa(lugar onde os inimigos vão passar)

    for (int i = 0; i < linhas; ++i) {                                          // para criar visualmente o mapa
        for (int j = 0; j < colunas; ++j) {
            QGraphicsPixmapItem *bloco;

            bool isCaminhoHorizontal = (i == 3 && j <= 9);                         // define caminho dos inimigos( em formato de L invertido)
            bool isCaminhoVertical = (j == 9 && i >= 3);

            if (isCaminhoHorizontal || isCaminhoVertical) {                     //define qual imagem desenha aquele bloco
                bloco = new QGraphicsPixmapItem(caminhoImg);
            } else {
                bloco = new QGraphicsPixmapItem(terrenoImg);
            }

            bloco->setPos(j * larguraBloco, i * larguraBloco);                  // define a posição do bloco na cena
            scene->addItem(bloco);                                              // adiciona o bloco na cena
        }
    }

    caminho.clear();                                                             // cria o caminho que os inimigos vão andar
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

    QList<QPointF> posicoesSlots = {                                            // define a posição  validas para colocar aas torres
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

    for (const QPointF &pos : posicoesSlots) {                                  // adiciona os slots validos  para colocar as torres no mapa
        TowerSlot *slot = new TowerSlot();
        slot->setPos(pos);
        connect(slot, &TowerSlot::clicado, this, &MainWindow::slotClicado);     // conecta o sinal de clique do slot á função slotclicado()
        scene->addItem(slot);
        listaSlots.append(slot);                                                 // armazena o slot clicado na lista de slot
    }
}

void MainWindow::slotClicado(TowerSlot *slot)
{
    if (dinheiro >= 50 && !slot->estaOcupado()) {                               // verifica se há dinheiro suficiente e se o slot esta vazio para comprar uma torre

        Tower *torre = new Tower();                                             // cria uma nova torre

        QRectF torreRect = torre->boundingRect();                               // retângulo da torre para ajuste de posição
        QPointF posSlot = slot->pos();
        QPointF ajuste(                                                         // calcula  o deslocamento para centralizar  a torre no slot
            (50 - torreRect.width()) / 2,
            (50 - torreRect.height()) / 2
            );

        torre->setPos(posSlot + ajuste);                                        // posiciona a torre no centro do slot
        scene->addItem(torre);                                                  // adiciona a torre
        listaTorres.append(torre);                                              // adiciona a lista de torres ativas

        slot->ocupar();                                                         // marca o slot como ocupado
        dinheiro -= 50;                                                         // desconta o valor quando a torre for comprada do valor disponivel da torre
        atualizarHUD();                                                         // atualiza a interface
    }
}

void MainWindow::removerTodasAsTorres()                                         // Remove todas as torres e libera os slots
{
    for (Tower *torre : listaTorres) {
        scene->removeItem(torre);
        delete torre;
    }
    listaTorres.clear();

    for (TowerSlot *slot : listaSlots) {                                        // libera slots ocupados pelas torres 
        slot->liberar();
    }
}

void MainWindow::iniciarJogo()
{
    if (jogoRodando)                                                            // evita iniciar o jogo novamente, se ja estiver rodando 
        return;

    jogoRodando = true;
    startButton->setEnabled(false);                                             // desabilita botões enquanto jogo em andamento 
    startButton->setText("Jogo em andamento");                                  // mostra no botão jogo em andamento

    iniciarOnda();
}

void MainWindow::reiniciarJogo()                                                // reseta o jogo para o inicio
{
    vida = 100;
    dinheiro = 90;                                                              // volta para as configurações primárias
    numeroDaOnda = 1;

    atualizarHUD();                                                             // atualiza a interface
    removerTodasAsTorres();                                                     // remove todas as torres

    jogoRodando = false;

    disconnect(startButton, nullptr, nullptr, nullptr);                                 // desconectar e reconectar o botão  para reiniciar 
    connect(startButton, &QPushButton::clicked, this, &MainWindow::iniciarJogo);

    startButton->setEnabled(true);
    startButton->setText("Iniciar Onda 1");                                              // aparece no botão a mensagem de qual onda esta
}

void MainWindow::iniciarOnda()
{
    if (vida <= 0)                                                          
        return;

    inimigosRestantesNaOnda = numeroDaOnda * numeroDaOnda;                          //número de inimigos por onda aumenta(1) com o número da onda
    inimigosVivos = 0;
    timerInimigos->start(1000);                                                     // gera inimigos a cada 1s
}

void MainWindow::gerarInimigo()
{
    if (inimigosRestantesNaOnda <= 0) {                                         // Verifica se ainda há inimigos para gerar  na onda
        timerInimigos->stop();                                                  // para o temporizador de geração do inimigos
        return;                                                                 //Encerra a função se todos ja forem gerados
    }

    Enemy *enemy = new Enemy(caminho);                                          //Cria  um novo inimigo e define o caminho
    enemy->setScale(0.3);                                                       // define a escala do inimigo

    inimigosRestantesNaOnda--;                                                 // atualiza  os contadores  de inimigos restante   e vivos
    inimigosVivos++;

    enemy->setCallbackOnFinish([this, enemy]() {                               // define o que acontece quando o inimigo chega ao fim do caminho
        inimigosVivos--;                                                       // diminui o número  de inimigos vivos
        inimigoChegouAoFim();                                                  // trata a perda de vida do jogador

        scene->removeItem(enemy);                                              // remove o inimigo da cena
        enemy->deleteLater();

        verificarFimOnda();                                                     // verifica se a onda atual terminou
    });

    enemy->onMorte = [this, enemy]() {                                         // define o que acontece  quando o inimigo  é morto  por uma torre
        inimigosVivos--;                                                        // define o número  de inimigos vivos
        dinheiro += 10;                                                         // recompensa com 10 de dinheiro
        atualizarHUD();                                                         // atualiza a interface

        scene->removeItem(enemy);                                               // remove o inimigo da cena
        enemy->deleteLater();

        verificarFimOnda();                                                     //Verifica se a onda atual terminou
    };

    scene->addItem(enemy);                                                      // adiciona  o inimigo  na cena para  ele aparecer no jogo
}

void MainWindow::verificarFimOnda()                                             //se todos os inimigos chegarem no fim do mapa inicia proxima onda
{
    if (inimigosRestantesNaOnda == 0 && inimigosVivos == 0 && vida > 0) {
        jogoRodando = false;                                                    //sem onda em andamento
        startButton->setEnabled(true);                                          // habilita o botão  de iniciar  e atualizar  o texto para a proxima nda
        startButton->setText(QString("Iniciar Onda %1").arg(++numeroDaOnda));
    }
}

void MainWindow::inimigoChegouAoFim()                                           // função chamada quando um inimigo  chega ao fim do caminho
{
    vida -= 10;                                                                 // reduz a vida se o inimigo chegar ao fim
    atualizarHUD();                                                             // atualiza  a interface

    if (vida <= 0) {                                                            // se a vida do jogador chegar a zero o jogo termina
        QMessageBox::information(this, "Derrota", "Você perdeu!");              // exibe a mensagem de derrota
        timerInimigos->stop();                                                  // para a geração de novos inimigos
        jogoRodando = false;                                                    // marca  o jogo como encerrado

        disconnect(startButton, nullptr, nullptr, nullptr);                     //desconecta as conexão anterior do botão  de início
        connect(startButton, &QPushButton::clicked, this, &MainWindow::reiniciarJogo);  // conecta  o botão  ao slot  de reiniciar  o jogo

        startButton->setEnabled(true);                                          //habilita o botão  para permitir  o clique
        startButton->setText("Reiniciar Jogo");                                 //atualiza o texto do botão
    }
}
