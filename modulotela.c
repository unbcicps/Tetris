////TELA______________________________________________________________________________________
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>  
int main(int argc, char **argv)
{
  tetris_game *tg;
  tetris_move move = none;
  bool running = true;
  WINDOW *board, *next, *hold, *score;
 
  
 if (argc >= 2) {
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("tetris");
      exit(EXIT_FAILURE);
    }
    tg = load(f);
    fclose(f);
  } else {
    tg = criar(22, 10);
  }
  
  board = newwin(tg->rows + 2, 2 * tg->cols + 2, 0, 0);
  initscr();      
  cbreak();    
  noecho();              
  keypad(stdscr, TRUE);  
  timeout(0);            
  curs_set(0);           
  init_colors();        
  board = newwin(tg->rows + 2, 2 * tg->cols + 2, 0, 0);
  next  = newwin(6, 10, 0, 2 * (tg->cols + 1) + 1);
  hold  = newwin(6, 10, 7, 2 * (tg->cols + 1) + 1);
  score = newwin(6, 10, 14, 2 * (tg->cols + 1 ) + 1);
  
  while (running) {
    running = tg_tick(tg, move);
    mostra_tabuleiro(board, tg);
    mostra_peca(next, tg->proximo);
    mostra_peca(hold, tg->guardado);
    mostra_pontuacao(score, tg);
    doupdate();
    sleep_milli(10);
    switch (getch()) {
    case KEY_LEFT:
      move = esquerda;
      break;
    case KEY_RIGHT:
      move = direita;
      break;
    case KEY_DOWN:
      move = soltar;
      break;
      case 's':
      salva_e_sai(tg, board);
      move = none;
      break;
    case 'q':
      running = false;
      move = none;
      break;
    case 'p':
      wclear(board);
      box(board, 0, 0);
      wmove(board, tg->rows/2, (tg->cols*COLS_PER_CELL-6)/2);
      wprintw(board, "PAUSED");
      wrefresh(board);
      timeout(-1);
      getch();
      timeout(0);
      move = none;
      break;
        
    case ' ':
      move = segurar;
      break;
    default:
      move = none;
    }
  }

  wclear(stdscr);
  endwin();

 
  printf("Game over!\n");
  printf("Você fez %d pontos e no  level %d.\n", tg->pontos, tg->level);

  delete(tg);
  return 0;
}
