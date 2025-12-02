# Batalha Naval - PIF

## Descrição

Este é um jogo de Batalha Naval em C, desenvolvido como projeto para a disciplina de PIF.
Permite jogar contra outro jogador, com posicionamento manual ou automático das frotas.

## Estrutura de arquivos

```
src/
├─ main.c          # Função principal e menu
├─ game.c / game.h  # Lógica do jogo: turnos, vitória, inicialização
├─ board.c / board.h  # Manipulação do tabuleiro
├─ fleet.c / fleet.h  # Manipulação da frota e navios
├─ io.c / io.h        # Entrada de dados do usuário
├─ rnd.c / rnd.h      # Funções de números aleatórios
Makefile             # Compilação do projeto
README.md            # Este arquivo
Relatorio_Tecnico.pdf # Relatório técnico
```

## Como compilar e executar

1. Abra o terminal na pasta do projeto:

```bash
cd "/c/Users/vivia/OneDrive/Área de Trabalho/Batalha Naval - PIF"
```

2. Compile o projeto:

```bash
make
```

3. Execute o jogo:

```bash
./batalha_naval   
```

4. Para limpar os arquivos compilados:

```bash
make clean
```

## Decisões de design

* Estrutura `Board` para armazenar células e estado do tabuleiro.
* Estrutura `Fleet` para armazenar navios e hits.
* Funções separadas por responsabilidade: tabuleiro, frota, entrada e jogo.
* Permite posicionamento manual ou automático da frota.
* Turnos alternados entre dois jogadores.
* Mensagens claras para acertos, afundamentos e erros de entrada.
