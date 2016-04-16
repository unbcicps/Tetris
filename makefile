all :	tela.c engine.c peca.c testes.c
	gcc -I./CUnit -L./CUnit tela.c -lcunit -o tela -lncurses
	./tela

gcov :	tela.c engine.c t.c testes.c
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit tela.c -lcunit -o -lncurses tela_gcov
	./tela_gcov
limpa : 
	rm *.gcda *.gcno *.gcov
