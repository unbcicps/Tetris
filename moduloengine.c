//////ENGINE_____________________________________________________________________________________
bool tg_tick(tetris_game *obj, tetris_move move)
{
  int lines_cleared;
  handle_move(obj, move);
  lines_cleared = checa_linha(obj);
  atualiza_placar(obj, lines_cleared);
  // Fala se o jogo ira continuar ou não
  return !jogo_terminou(obj);
}

void iniciar(tetris_game *obj, int rows, int cols)
{
  obj->rows = rows;
  obj->cols = cols;
  obj->tabuleiro = malloc(rows * cols);
  memset(obj->tabuleiro, PC_EMPTY, rows * cols);
  obj->pontos = 0;
  obj->level = 0;
  obj->linhas_faltando = Linhas_por_Nivel;
  srand(time(NULL));
  nova_cair(obj);
  nova_cair(obj);
  obj->guardado.typ = -1;
  obj->guardado.ori = 0;
  obj->guardado.loc.row = 0;
  obj->proximo.loc.col = obj->cols/2 - 2;
  printf("%d", obj->cair.loc.col);
}

tetris_game *criar(int rows, int cols)
{
  tetris_game *obj = malloc(sizeof(tetris_game));
  iniciar(obj, rows, cols);
  return obj;
}

void apagar(tetris_game *obj)
{
  free(obj->tabuleiro);
}

void delete(tetris_game *obj) {
  apagar(obj);
  free(obj);
}

//Carrega o jogo de um arquivo
tetris_game *load(FILE *f)
{
  tetris_game *obj = malloc(sizeof(tetris_game));
  fread(obj, sizeof(tetris_game), 1, f);
  obj->tabuleiro = malloc(obj->rows * obj->cols);
  fread(obj->tabuleiro, sizeof(char), obj->rows * obj->cols, f);
  return obj;
}

//Salva o jogo 
void salvar(tetris_game *obj, FILE *f)
{
  fwrite(obj, sizeof(tetris_game), 1, f);
  fwrite(obj->tabuleiro, sizeof(char), obj->rows * obj->cols, f);
}

//Printa o tabuleiro
void print(tetris_game *obj, FILE *f) {
  int i, j;
  for (i = 0; i < obj->rows; i++) {
    for (j = 0; j < obj->cols; j++) {
      if (PC_IS_EMPTY(get(obj, i, j))) {
        fputs(PC_EMPTY_STR, f);
      } else {
        fputs(PC_BLOCK_STR, f);
      }
    }
    fputc('\n', f);
  }
}

//Mostra o tabuleiro no Ncurses
void mostra_tabuleiro(WINDOW *w, tetris_game *obj)
{
  int i, j;
  box(w, 0, 0);
  for (i = 0; i < obj->rows; i++) {
    wmove(w, 1 + i, 1);
    for (j = 0; j < obj->cols; j++) {
      if (PC_IS_FILLED(get(obj, i, j))) {
        ADD_BLOCK(w,get(obj, i, j));
      } else {
        ADD_EMPTY(w);
      }
    }
  }
  wnoutrefresh(w);
}

//Mostra peça
void mostra_peca(WINDOW *w, tetris_block block)
{
  int b;
  tetris_localizacao c;
  wclear(w);
  box(w, 0, 0);
  if (block.typ == -1) {
    wnoutrefresh(w);
    return;
  }
  for (b = 0; b < TETRIS; b++) {
    c = peca[block.typ][block.ori][b];
    wmove(w, c.row + 1, c.col * COLS_PER_CELL + 1);
    ADD_BLOCK(w, TYPE_TO_CELL(block.typ));
  }
  wnoutrefresh(w);
}

//Mostra a pontuação 
void mostra_pontuacao(WINDOW *w, tetris_game *tg)
{
  wclear(w);
  box(w, 0, 0);
    wprintw(w, "Score\n%d\n", tg->pontos);
   wprintw(w, "Sair:\nQ\n");
  wprintw(w, "Mover:\nSetas\n");
  wnoutrefresh(w);
}

//Salva e sai
void salva_e_sai(tetris_game *game, WINDOW *w)
{
  FILE *f;

  wclear(w);
  box(w, 0, 0); 
  wmove(w, 1, 1);
  wprintw(w, "Salvar e sair? [Y/n] ");
  wrefresh(w);
  timeout(-1);
  if (getch() == 'n') {
    timeout(0);
    return;
  }
  f = fopen("tetris.save", "w");
  salvar(game, f);
  fclose(f);
  delete(game);
  endwin();
  printf("Jogo salvo \"tetris.save\".\n");
  printf("Resume by passing the filename as an argument to this program.\n");
  exit(EXIT_SUCCESS);
}

//Inicializa as cores
void init_colors(void)
{
  start_color();
  init_pair(PC_CELLI, COLOR_CYAN, COLOR_BLACK);//Variáveis de outras peças , pois tirá-las causa bug :(;;;; 
  init_pair(PC_CELLJ, COLOR_BLUE, COLOR_BLACK);
  init_pair(PC_CELLL, COLOR_WHITE, COLOR_BLACK);
  init_pair(PC_CELLO, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PC_CELLS, COLOR_GREEN, COLOR_BLACK);
  init_pair(PC_CELLT, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(PC_CELLZ, COLOR_RED, COLOR_BLACK);
}
