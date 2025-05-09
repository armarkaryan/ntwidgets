#include <iostream>
#include <thread>

#include "nttypes.h"
#include "ntobject.h"
#include "ntlabel.h"

int main(int argc, char* argv[])
{
// ncurses init
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(0);

	// Проверка поддержки цветов
	if (!has_colors()) {
		endwin();
		fprintf(stderr, "Терминал не поддерживает цвета\n");
		return EXIT_FAILURE;
	}

	start_color();
	use_default_colors();

// User render
	NTLabel Label1(0, "Label1", "Hello World!", 5, 5, {100, 100, 100}, {0, 0, 0}, false);

/*for(int i=0; i<10; i++){
	Label1.setx(i);
}
	if(Label1.isChanged())Label1.draw();*/

// Exity programm
	int x=0;
	int ch;
	while((ch = getch()) != ' '){
		if(x<100)x++;else x=0;
		Label1.setx(x);
		if(Label1.isChanged())Label1.draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	endwin();

	std::cout << "Program finished." << std::endl;
	return EXIT_SUCCESS;
}
