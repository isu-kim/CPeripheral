/**
	CPeripheral
	C_Pheperial.cpp
	Purpose: Includes all the combined functions of this program

	@author Gooday2die (Isu Kim)
	@version 0.1 19/19/12
*/


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

	/**
		Initializer for Demo class.

		@param {bool} temp_debug for turning on and off debug state
		@return void
	*/

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

	/**
		Turns debug mode on for Demo class.

		@param void
		@return void
	*/

	void debug_on(void) {
		obj_corsair.debug_on();
		obj_razer.debug_on();
		return;
	}

	/**
		Turns debug mode off for Demo class.

		@param void
		@param void
	*/

	void debug_off(void) {
		obj_corsair.debug_off();
		obj_razer.debug_off();
		return;
	}

	/**
		Sets all device color.
		
		@param {unsigned char} r value of Red to be set for the devices.
		@param {unsigned char} g value of Green to be set for the devices.
		@param {unsigned char} b value of Blue to be set for the devices.
		@return void
	*/

	void set_all_device_color(unsigned char r, unsigned char g, unsigned char b) {
		obj_corsair.set_all_color(r, g, b);
		obj_razer.set_all_color(r, g, b);
	}

	/**
		Rainbow shifts all the device forever.

		@param {unsigned char} speed how fast the rainbow shift would be performed
		@return void
	*/

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

	/**
		Sets all the colors into RED forever.

		@param void
		@return void
	*/

	void set_red(void) {
		std::cout << "[CPeripheral] Demo : Set Red" << std::endl;
		while (true) set_all_device_color(255, 0, 0);
	}

	/**
		Sets all the colors breathe in a color forever.

		@param {unsigned char} r value of Red to be set for the devices.
		@param {unsigned char} g value of Green to be set for the devices.
		@param {unsigned char} b value of Blue to be set for the devices.
		@param {float} speed how fast the breathing effect should perform. Recommended value = 0.05
		@return void
	*/

	void breathing(unsigned char r, unsigned char g, unsigned char b, float speed) {
		bool temp_debug;
		temp_debug = debug;

		if (debug)std::cout << "[CPeripheral] Demo : Breathing (" << (int)r << "," << (int)g << "," << int(b) << ", Speed = " << (float)speed << ")" << std::endl;

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

/**
	Shows the menu of possible operations.

	@param {int} command number command of operation
	@return void
*/

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

/**
	Main function

	@param void
	@return {int} 0
*/

int main(void) {
	int command = false;
	std::cout << "[CPeripheral] Debug ? 0(off) , 1(on)" << std::endl;
	scanf_s("%d", &command);
	menu(command);

	return 0;
}

/*
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
*/
