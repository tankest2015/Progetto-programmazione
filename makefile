all: main

main: main.o class_menu.o game_engine.o salvataggio_punteggio/write_lead.o tetramini.o board.o style_game.o pause.o options.o
	g++ main.o class_menu.o game_engine.o salvataggio_punteggio/write_lead.o tetramini.o board.o style_game.o pause.o options.o -o main -lncurses

main.o: main.cpp class_menu.h game_engine.h salvataggio_punteggio/write_lead.h
	g++ -c main.cpp

class_menu.o: class_menu.cpp class_menu.h
	g++ -c class_menu.cpp

game_engine.o: game_engine.cpp game_engine.h tetramini.h board.h style_game.h pause.h salvataggio_punteggio/write_lead.h options.h
	g++ -c game_engine.cpp

write_lead.o: salvataggio_punteggio/write_lead.cpp salvataggio_punteggio/write_lead.h
	g++ -c salvataggio_punteggio/write_lead.cpp

tetramini.o: tetramini.cpp tetramini.h board.h style_game.h
	g++ -c tetramini.cpp

board.o: board.cpp board.h tetramini.h style_game.h
	g++ -c board.cpp

style_game.o: style_game.cpp style_game.h board.h tetramini.h
	g++ -c style_game.cpp

pause.o: pause.cpp pause.h
	g++ -c pause.cpp

options.o: options.cpp options.h
	g++ -c options.cpp

clean:
	rm -f main *.o salvataggio_punteggio/*.o
