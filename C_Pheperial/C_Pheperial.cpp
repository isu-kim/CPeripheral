// C_Pheperial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <CUESDK.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CorsairWrapper.cpp"
#include "RazerWrapper.cpp"
#include "MysticLightWrapper.cpp"

void menu(bool);

class  Demo{
public:
	Corsair obj_corsair = Corsair();
	Razer obj_razer = Razer(0,0);
	bool debug = false;

	Demo(bool temp_debug) {
		debug = temp_debug;
		if (debug) {
			debug_on();
			std::cout << "[CPeripheral] Debug Mode On." << std::endl;
		}
		else {
			debug_off();
			std::cout << "[CPeripheral] Debug Mode Off." << std::endl;
		}
	}

	void debug_on(void) {
		obj_corsair.debug_on();
		obj_razer.debug_on();
		return;
	}

	void debug_off(void) {
		obj_corsair.debug_off();
		obj_razer.debug_off();
		return;
	}

	void set_all_device_color(unsigned char r, unsigned char g, unsigned char b) {
		obj_corsair.set_all_color(r, g, b);
		obj_razer.set_all_color(r, g, b);
	}

	void rainbow(unsigned char speed) {
		if (debug) std::cout << "[CPeripheral] Demo : Rainbow ( Speed = " << (int)speed << " ) "<<std::endl;

		while (1) {
			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(255, i, 0);
			}

			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(255 - i, 255, 0);
			}

			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(0, 255, i);
			}

			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(0, 255 - i, 255);
			}

			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(i, 0, 255);
			}

			for (unsigned char i = 0; i < 255; i += speed) {
				set_all_device_color(255, 0, 255 - i);
			}
		}
	}

	void set_red(void) {
		std::cout << "[CPeripheral] Demo : Set Red" << std::endl;
		while (true) set_all_device_color(255, 0, 0);
	}


	void breathing(unsigned char r, unsigned char g, unsigned char b, float speed) { // 0.05 seems nice to me :b
		bool temp_debug;
		temp_debug = debug;

		if (debug)std::cout << "[CPeripheral] Demo : Breathing (" << (int)r << "," << (int)g << "," << int(b) << ", Speed = " << (float)speed << ")" << std::endl;
		debug = false;  //I am lazy so I am reusing the glow function up above. To avoid messaging, I would be turning off debug :b. 

		while (1) {

			for (float i = 0; i < 1; i += speed) {
				set_all_device_color((int)(r * i), (int)(g * i), (int)(b * i));
				Sleep(1 / speed);
			}

			for (float i = 1; i > 0; i -= speed) {
				set_all_device_color((int)(r * i), (int)(g * i), (int)(b * i));
				Sleep(1 / speed);
			}
		}

		return;

	}
};

void menu(int debug) {
	int command = 100;
	Demo D1 = Demo(debug); // True means debug is on. false means it is off

	do {
		std::cout << "[CPeripheral] Demo Script" << std::endl;
		std::cout << "Rainbow(1) , Breathing(2) , Red(3)" << std::endl;
		scanf_s("%d", &command);
	} while (command != 1 && command != 2 && command != 3);

	switch (command) {
	case 1: {
			int speed;

			std::cout << "[CPeripheral] Enter Rainbow Speed : " << std::endl;
			scanf_s("%d", &speed);

			D1.rainbow(speed);
			break;
		}



	case 2: {
		float speed;

		unsigned char r;
		unsigned char g;
		unsigned char b;

		std::cout << "[CPeripheral] Enter Glow in format" << std::endl;
		std::cout << "r,g,b,float_speed / ex) 255,255,255,0.5" << std::endl;

		scanf_s("%d,%d,%d,%f", &r, &g, &b, &speed);

		D1.breathing(r, g, b, speed);

		break;

		}
	case 3: {
		D1.set_red();
	}

	}
}



/*
int main(int argc, const char* argv[]) {
	// main.exe -debug true something like this
	int command = false;
	std::cout << "[CPeripheral] Debug ? 0(off) , 1(on)" << std::endl;
	scanf_s("%d", &command);
	menu(command);

	return 0;
}
*/

int main(void) {
	Razer r1 = Razer(0, 0);
	Corsair C1 = Corsair();
	MysticLight M1 = MysticLight();

	r1.set_all_color(255, 0, 0);
	C1.set_all_color(255, 0, 0);
	M1.init();
	M1.get_device_name();

	std::cin.ignore();
	return 0;
}
