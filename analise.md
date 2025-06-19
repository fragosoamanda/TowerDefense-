# Análise orientada a objeto

## PROJETO FINAL - Tower Defense
## Descrição geral 
O objetivo deste jogo é enfrentar sucessivas ondas de inimigos que percorrem um caminho pré-definido até o final do mapa.
Para impedi-los, o jogador deve posicionar estrategicamente torres de defesa ao longo desse trajeto, eliminando os inimigos antes que alcancem o destino final.

Os inimigos são controlados pelo computador e surgem em ondas. Cada onda possui uma quantidade definida de inimigos com características específicas, como velocidade e pontos de vida. Com o avanço do jogo, as ondas se tornam mais difícil, com mais inimigos.

Os inimigos seguem um trajeto fixo, da entrada até a saída do mapa. Cada inimigo que chega ao final reduz a vida do jogador.O jogador é responsável pelo posicionamento das torres de defesa, que atacam automaticamente os inimigos dentro de seu alcance. Ao derrotar um inimigo, o jogador recebe uma quantia de dinheiro, que pode ser usada para construir novas torres. O posicionamento deve ser feito de forma estratégica para resistir às ondas.

A interface do jogo exibe ao jogador informações importantes, como a quantidade de vidas restantes e o dinheiro disponível. Há também dois botões principais: um para iniciar o jogo e outro para comprar torres.

Uma vez iniciado, o jogo não pode ser pausado. Isso significa que, após o começo da partida, o jogador não poderá mais posicionar novas torres ou fazer alterações. Se todas as vidas forem perdidas, o jogo é encerrado.

## Elementos do Jogo 

**Torres de Defesa**: As torres são estruturas fixas que o jogador pode posicionar ao longo do caminho dos inimigos. Cada torre possui características específicas como alcance, dano e velocidade de ataque. 

**Inimigos**: Os inimigos surgem em ondas e percorrem um caminho fixo até um objetivo. Cada inimigo possui quantidades de vida  e velocidade.

**Recursos**: O jogador inicia a partida com uma quantidade fixa de moedas, que podem ser utilizadas para construir torres de defesa. Ao eliminar inimigos, o jogador ganha mais moedas, o que permite construir novas torres.

**Fases/Ondas**: O jogo é dividido em fases ou ondas de ataque. Cada nova onda traz  mais inimigos, aumentando o desafio do jogador.

**Objetivo**: Impedir que os inimigos cheguem ao ponto final do caminho. O jogo termina quando o jogador deixa passar um número máximo de inimigos, ou quando todas as ondas forem vencidas com sucesso.
 
 ## Requesitos do Jogo  
 - O jogador deve ser capaz de posicionar torres ao longo do caminho pré-definido antes do início do jogo.
 - As torres devem atacar automaticamente os inimigos que estiverem dentro do seu alcance.
 - O jogo deve gerar as ondas de inimigos que percorrem o caminho desde o ponto de entrada até a base do jogador.
 - Os inimigos devem causar dano à base do jogador ao chegarem ao final do caminho.
 - O jogador deve perder vidas cada vez que um inimigo alcançar a base. O jogo termina quando todas as vidas forem perdidas.
 - O jogador deve perder vidas cada vez que um inimigo alcançar a base. O jogo termina quando todas as vidas forem perdidas.

 - O jogador deve perder vidas cada vez que um inimigo alcançar a base. O jogo termina quando todas as vidas forem perdidas.
- A interface do jogo deve exibir, em tempo real, a quantidade de vidas restantes e o dinheiro disponível.
- Após o início da partida, o jogador não poderá mais alterar a posição ou quantidade de torres.



 - [Diagrama de Classe](./dc.md)
 - [Diagrama de Caso de Uso](./dcu.md)
 - [Diagrama de Sequência](./ds.md)
 - [Código](./code.md)

<div align="center">

[Retroceder](README.md) | [Avançar](./dc.md)

</div>