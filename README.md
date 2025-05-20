# Projeto de Programação Imperativa e Funcional - 2025.1 (PIF) - Cesar School

Jogo desenvolvido em C para a disciplina de Programação Imperativa e Funcional utilizando a biblioteca CLI.lib

## BlockFall

O Blockfall é um jogo inspirado no famoso e nostálgico Tetris, onde peças de diversas formas caem de cima do tabuleiro. O jogador deve encaixá-las para completar fileiras de blocos. Quando uma fileira é formada, ela é removida e o jogador ganha pontos. O objetivo é conquistar a maior pontuação possível sem deixar as peças alcançarem o topo do tabuleiro.

---

## 🎮 Controles

| Tecla | Ação                  |
|-------|-----------------------|
| A     | Mover para Esquerda   |
| D     | Mover para Direita    |
| W     | Rotacionar peça       |
| S     | Aumentar velocidade   |
| Espaço| Queda rápida          |

---

## ⚙️ Como Jogar

### Requerimentos para rodar o jogo
Esse jogo usa uma biblioteca compatível com os seguintes Sistemas Operacionais:
- Linux (Ubuntu, etc)
- MacOS

**É necessário ter o GCC instalado.**

### ▶️ Como rodar no seu Computador
1. Navegue até o diretório raiz do projeto
2. Execute no terminal:
```gcc -I include src/main.c src/screen.c src/keyboard.c src/timer.c src/tetris.c src/txt.c -o build/blockfall```
3. Em seguida, execute:
```./build/blockfall```

### 🏆 Sistema de Ranking
O jogo mantém um ranking das 10 melhores pontuações

Ao final de cada partida, sua pontuação é comparada com o top 10

O ranking é salvo automaticamente no arquivo ranking.txt

### 👥 Contribuidores
Nome - Email - GitHub
João Neri	- jgsn@cesar.school	- JoaoNerii
Pedro Pessoa	- ppb2@cesar.school -	Pedropbastos
Lucas Canto	- lcss@cesar.school	- Lucascs88
