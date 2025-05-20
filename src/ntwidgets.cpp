#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#include "nttypes.h"
#include "ntobject.h"
//#include "ntpalette.h"
#include "ntlabel.h"
#include "ntimage.h"
#include "digits_8x8.h"

#include <sstream>  // для ostringstream
#include <iomanip>  // для setw, setfill

int _hour = 0;
int _min = 0;
int _sec = 0;
std::mutex localtime_mutex;  // Мьютекс для синхронизации доступа к времени
std::atomic<int> ch;

int main(int argc, char* argv[])
{
	std::cout << "Program started." << std::endl;
// Test Color
//	NTColor Color1;
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
	printw("Color pair max count: %d\n", COLOR_PAIRS);
	use_default_colors();

// User render
	// Colors
	unsigned char color_time_id = 0;
	nt::color color_Time = nt::color({255, 0, 255});
	init_color(color_time_id, color_Time.red * 1000 / 255, color_Time.green * 1000 / 255, color_Time.blue * 1000 / 255);

	unsigned char color_bg_id = 1;
	nt::color color_bg_Time = nt::color({0, 255, 0});
	init_color(color_bg_id, color_bg_Time.red * 1000 / 255, color_bg_Time.green * 1000 / 255, color_bg_Time.blue * 1000 / 255);

	unsigned char color_pair_Time = 1;
	init_pair(color_pair_Time, color_time_id, color_bg_id);

	NTLabel Label1(0, "Label1", "Hello World!", 15, 5, color_pair_Time, A_BOLD, false);
	NTLabel Label2(0, "Label2", "Hello World!", 10, 0, color_pair_Time, 0, false);
	NTLabel Label3(0, "Label3");

	NTImage Image1(0, "hh_hi", digits_8x8[0].img, 4, 4, 0, 0, true);
	NTImage Image2(0, "hh_lo", digits_8x8[0].img, 3, 3, color_pair_Time, 0, true);

// Exit programm
	//int x=0;

	while(ch != ' '){

		{
			std::lock_guard<std::mutex> lock(localtime_mutex);

			const auto now = std::chrono::system_clock::now();
			const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
			std::tm now_tm;

			// Используем локальное время вместо GMT с фиксированным смещением
			now_tm = *std::localtime(&now_time);

			_hour = now_tm.tm_hour;
			_min = now_tm.tm_min;
			_sec = now_tm.tm_sec;
		}


			/*Label1.setx(x);
			if(x<100)x++;else x=0;*/

			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << _hour << ":"
				<< std::setw(2) << std::setfill('0') << _min << ":"
				<< std::setw(2) << std::setfill('0') << _sec;
			std::string timeString = oss.str();
			Label1.setText(timeString);

			//oss.clear();
			//oss << Image1.image().size();
			//std::string temp = oss.str();
			std::string temp = "2  0";
			Label2.setText(temp);

			// Check if neet to redraw
			if(Label1.isChanged())Label1.draw();
			//
			if(Image1.isChanged())Image1.draw();
			if(Image2.isChanged())Image2.draw();

			// Check if neet to redraw
			if(Label2.isChanged())Label2.draw();

			// Возможен Deadlock?
			ch = getch();


		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	endwin();

	std::cout << "Program finished." << std::endl;
	return EXIT_SUCCESS;
}
