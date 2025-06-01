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

#include <sstream>  // for ostringstream
#include <iomanip>  // for setw, setfill

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

	// Check the colors support
	if (!has_colors()) {
		endwin();
		fprintf(stderr, "Colors is not supported!\n");
		return EXIT_FAILURE;
	}

	start_color();
	printw("0________________________________\n");
	printw("1________________________________\n");
	printw("2________________________________\n");
	printw("3________________________________\n");
	printw("4________________________________\n");
	printw("5________________________________\n");
	printw("6________________________________\n");
	printw("7______________________________________________________________________________________\n");
	printw("Color pair max count: %d\n", COLOR_PAIRS);
	use_default_colors();

// User render
	// Colors
	unsigned char color_time_id = 0;
	nt::color color_Time = nt::color({255, 0, 0});
	init_color(color_time_id, color_Time.red * 1000 / 255, color_Time.green * 1000 / 255, color_Time.blue * 1000 / 255);

	unsigned char color_bg_id = 1;
	nt::color color_bg_Time = nt::color({0, 255, 0});
	init_color(color_bg_id, color_bg_Time.red * 1000 / 255, color_bg_Time.green * 1000 / 255, color_bg_Time.blue * 1000 / 255);

	unsigned char color_pair_Time = 1;
	init_pair(color_pair_Time, color_time_id, color_bg_id);

	unsigned char color_sun_id = 2;
	nt::color color_Sun = nt::color({255, 255, 0});
	init_color(color_sun_id, color_Sun.red * 1000 / 255, color_Sun.green * 1000 / 255, color_Sun.blue * 1000 / 255);

	unsigned char color_sky_id = 3;
	nt::color color_Sky = nt::color({0, 255, 255});
	init_color(color_sky_id, color_Sky.red * 1000 / 255, color_Sky.green * 1000 / 255, color_Sky.blue * 1000 / 255);

	unsigned char color_pair_Weather = 2;
	init_pair(color_pair_Weather, color_sun_id, color_sky_id);

	NTLabel Label_Time(0, "Label_Time", "Hello World!", 15, 10, color_pair_Weather, A_BOLD, NTA_NONE);

	NTLabel Label0(0, "Label0", "Hello World!", 10, 0, color_pair_Time, 0,
		NTA_NONE);
	NTLabel Label1(0, "Label1", "Hello World!", 10, 1, color_pair_Time, 0,
		NTA_SPACE_TRANSPARENT);
	NTLabel Label2(0, "Label2", "Hello World!", 10, 2, color_pair_Time, 0,
		NTA_SPACE_ATTR);
	NTLabel Label3(0, "Label3", "Hello World!", 10, 3, color_pair_Time, 0,
		NTA_SPACE_ATTR | NTA_SPACE_TRANSPARENT);
	NTLabel Label4(0, "Label4", "Hello World!", 10, 4, color_pair_Time, 0,
		NTA_TEXT_ATTR);
	NTLabel Label5(0, "Label5", "Hello World!", 10, 5, color_pair_Time, 0,
		NTA_TEXT_ATTR | NTA_SPACE_TRANSPARENT);
	NTLabel Label6(0, "Label6", "Hello World!", 10, 6, color_pair_Time, 0,
		NTA_TEXT_ATTR | NTA_SPACE_ATTR);
	NTLabel Label7(0, "Label7", "Hello World!", 10, 7, color_pair_Time, 0,
		NTA_TEXT_ATTR | NTA_SPACE_ATTR | NTA_SPACE_TRANSPARENT);

	NTLabel Label_Hello(0, "Label_Hello");

	//NTImage Image1(0, "hh_hi", digits_8x8[0].img, 4, 4, 0, 0, NTA_NONE);
	NTImage Image2(0, "hh_lo", digits_8x8[0].img, 3, 3, color_pair_Weather, 0, NTA_TEXT_ATTR | NTA_SPACE_TRANSPARENT);

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
			Label_Time.setText(timeString);

			//oss.clear();
			//oss << Image1.image().size();
			//std::string temp = oss.str();
			//std::string temp = "2  0";
			//Label2.setText(temp);

			// Check if neet to redraw
			if(Label_Hello.isChanged())Label_Hello.draw();

			if(Label0.isChanged())Label0.draw();
			if(Label1.isChanged())Label1.draw();
			if(Label2.isChanged())Label2.draw();
			if(Label3.isChanged())Label3.draw();
			if(Label4.isChanged())Label4.draw();
			if(Label5.isChanged())Label5.draw();
			if(Label6.isChanged())Label6.draw();
			if(Label7.isChanged())Label7.draw();

			//
			//if(Image1.isChanged())Image1.draw();
			if(Image2.isChanged())Image2.draw();

			if(Label_Time.isChanged())Label_Time.draw();

			// Возможен Deadlock?
			ch = getch();


		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	endwin();

	std::cout << "Program finished." << std::endl;
	return EXIT_SUCCESS;
}
