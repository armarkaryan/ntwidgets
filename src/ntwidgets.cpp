#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#include "nttypes.h"
#include "ntobject.h"
#include "ntlabel.h"


#include <sstream>  // для ostringstream
#include <iomanip>  // для setw, setfill

int _hour = 0;
int _min = 0;
int _sec = 0;
std::mutex localtime_mutex;  // Мьютекс для синхронизации доступа к времени
std::atomic<int> ch;

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
	NTLabel Label1(0, "Label1", "Hello World!", 15, 5, {100, 200, 100}, {0, 0, 0}, false);


// Exity programm
	int x=0;

	while(ch != ' '){

		const auto now = std::chrono::system_clock::now();
		const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm;

		// Используем локальное время вместо GMT с фиксированным смещением
		now_tm = *std::localtime(&now_time);

		_hour = now_tm.tm_hour;
		_min = now_tm.tm_min;
		_sec = now_tm.tm_sec;

		{
			std::lock_guard<std::mutex> lock(localtime_mutex);

			/*Label1.setx(x);
			if(x<100)x++;else x=0;*/

			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << _hour << ":"
				<< std::setw(2) << std::setfill('0') << _min << ":"
				<< std::setw(2) << std::setfill('0') << _sec;
			std::string timeString = oss.str();
			Label1.setText(timeString);

			if(Label1.isChanged())Label1.draw();

			//
			ch = getch();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	endwin();

	std::cout << "Program finished." << std::endl;
	return EXIT_SUCCESS;
}
