Projeto de Programação Imperativa e Funcional - 2025.1 (PIF) - Cesar School
Jogo desenvolvido em C para a disciplina de Programação Imperativa e Funciona utilizando a biblioteca CLI.lib

BlockFall
O Blockfall é um jogo inspirado no famoso e nostálgico Tetris, onde peças de diversas formas caem de cima do tabuleiro, onde o jogador tem que tentar encaixar-las, para que complete uma fileira de blocos, assim que a fileira é formada, ela é excluída e o jogador ganha pontos, o objetivo é conseguir conquistar o maior número de pontos sem deixar as peças tocarem ao topo do tabuleiro.

-Controles
Tecla	Ação
A	Mover para Esquerda
D	Mover para Direita
W	Rotacionar peça
S Aumentar velocidade da queda

-Como jogar
Requerimento para rodar o jogo
Esse jogo usa uma biblioteca que funciona com os segundos Sistemas Operacionais (OS):
Linux (Ubuntu, etc)
MacOS
É necessario ter o GCC Instalado.
Como rodar no seu Computador:
Para rodar o jogo na sua maquina, basta mudar para o diretório raiz da biblioteca e digitar o seguinte comando no terminal:

gcc -I include src/main.c src/screen.c src/keyboard.c src/timer.c src/tetris.c src/txt.c -o build/blockfall
E em seguida, digite o seguinte comando:
./build/blockfall

Contribuidores
João Neri - jgsn@cesar.school - JoaoNerii

Pedro Pessoa - ppb2@cesar.school - Pedropbastos

Lucas Canto - lcss@cesar.school - Lucascs88
