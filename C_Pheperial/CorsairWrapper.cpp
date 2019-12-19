/**
	CPeripheral
	CorsairWrapper.cpp
	Purpose: Wrapping Corsair ICUE SDKs for my program.

	@author Gooday2die(Isu Kim)
	@version 0.1 19/19/12
*/

#include <iostream>
#include <Windows.h>
#include <CUESDK.h>
#include <stdlib.h>
#include <string.h>


class Corsair {
public:

	/**
	A structure for saving the index of connected devices
	*/
	struct Device_ID_Index_Info {
		int keyboard;
		int mouse;
		int headset;
		int headsetstand;
		int mousemat;
		int commanderpro;
		int lightingnodepro;
		int memorymodule;
		int cooler;
	};

	int device_counts;
	bool debug = false;
	CorsairDeviceInfo** device_info_array;
	Device_ID_Index_Info device_id_index;


	/**
	A constructor member function for Corsair class.
	
	@param void
	@return void
	*/

	Corsair() {
		init();
		device_counts = CorsairGetDeviceCount();
		get_device_info();
		if (device_counts == -1) {
			std::cout << "[CPeripheral] Failed to initialize Corsair ICUE." << std::endl;
			exit(0);
		}
		else {
			std::cout << "[CPeripheral] Succesfully initalized Corsair ICUE." << std::endl;
		}
		set_device_id_index();
	}

	/**
	A function for setting debug mode on
	
	@param void
	@return void
	*/

	void debug_on(void) {
		debug = true;
		return;
	}

	/**
	A function for setting debug mode off

	@param void
	@return void
	*/

	void debug_off(void) {
		debug = false;
		return;
	}

	/**
	A function for printing out list of connected devices.

	@param void
	@return void
	*/

	void print_device_info(void) {
		/* A method for printing connected Corsair devices.*/
		std::cout << "[CPeripheral] Connected Corsair Devices." << std::endl;
		for (int i = 0; i < device_counts; i++) {
			std::cout << "Index " << i << " : " << device_info_array[i]->model << std::endl;
		}
		return;
	}

	/**
	A function for getting device information

	@param void
	@return CorsairDeviceInfo**
	*/

	CorsairDeviceInfo** get_device_info(void) {
		static bool this_function_is_already_called = false; // For checking if this function was called before. 

		if (!this_function_is_already_called) {  // If method is not called before, do a init process.
			device_info_array = NULL;
			device_info_array = (CorsairDeviceInfo * *)malloc(sizeof(CorsairDeviceInfo*) * device_counts);

			if (device_info_array == NULL) {
				std::cout << "[CPeripheral] Failed to make corsair_device_info_array." << std::endl;
				exit(0);
			}

			for (int i = 0; i < device_counts; i++) {
				device_info_array[i] = CorsairGetDeviceInfo(i);
				if (device_info_array[i] == NULL) {
					std::cout << "[CPeripheral] Failed to get device information from CUESDK : Check if you have executed corsair_init()." << std::endl;
					exit(0);
				}
			}
			this_function_is_already_called = true;
		}

		else {  // If this method is called before, there is no need to init.
			for (int i = 0; i < device_counts; i++) {
				std::cout << "Index " << i << " : " << device_info_array[i]->model << std::endl;
			}
		}
		return device_info_array;
	}

	/**
	A function for getting a device id of a specific connected device type
	
	@param CorsairDeviceType
	@return int
	*/

	int get_device_id_index(CorsairDeviceType requested) {
			for (int i = 0; i < device_counts; i++) {
				if (requested == device_info_array[i]->type) return i;
			}
		return 100; // This case means that the device does not exist.
	}

	/**
	A function for filling up all the device indexes.

	@param void
	@return void
	*/

	void set_device_id_index(void) {
		/* Sets all the id indexs. */
		device_id_index.keyboard = get_device_id_index(CDT_Keyboard);
		device_id_index.mouse = get_device_id_index(CDT_Mouse);
		device_id_index.mousemat = get_device_id_index(CDT_MouseMat);
		device_id_index.headset = get_device_id_index(CDT_Headset);
		device_id_index.headsetstand = get_device_id_index(CDT_HeadsetStand);
		device_id_index.cooler = get_device_id_index(CDT_Cooler);
		device_id_index.commanderpro = get_device_id_index(CDT_CommanderPro);
		device_id_index.lightingnodepro = get_device_id_index(CDT_LightingNodePro);
		device_id_index.memorymodule = get_device_id_index(CDT_MemoryModule);
		return;
	}

	/**
	A function for initializing Corsair ICUE SDK. Does ProtocolHandshake and Request Control
	
	@param void
	@return void
	*/

	void init(void) {
		CorsairPerformProtocolHandshake();
		CorsairRequestControl(CAM_ExclusiveLightingControl);
		return;
	}

	/**
	A function for setting device to a specific color

	@param {CorsairDeviceType} device_type the type of LED device. Check {enum} CorsairDeviceType 
		   located at Corsair official document page 33.
	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@param {CorsairLedId} key_id the LED id for the LED to be set. check {enum} CorsairLedId 
		   located at Corsair official document page 31.
	@return void
	*/

	void set_device_color(CorsairDeviceType device_type, unsigned char r, unsigned char g, unsigned char b, CorsairLedId key_id) {
		CorsairLedColor corsair_led_color;
		bool result;
		char device_id = get_device_id_index(device_type);
		corsair_led_color.r = r;
		corsair_led_color.b = b;
		corsair_led_color.g = g;
		corsair_led_color.ledId = key_id;

		result = CorsairSetLedsColorsBufferByDeviceIndex(device_id, 1, &corsair_led_color); // Returns true if executed successfully.
		CorsairSetLedsColorsFlushBuffer(); // Needs to flush buffer in order to effect.

		if (debug) {
			if (!result) std::cout << "[CPeripheral] Failed to set color " << (int)r << (int)g << (int)b << " to Corsair " << (CorsairLedId)key_id << std::endl;
			else std::cout << "[CPeripheral] Set color " << (int)r << " , " << (int)g << " , " << (int)b << " to Corsair " << (CorsairLedId)key_id << std::endl;
		}

		return;
	}

	/**
	A function for setting all Corsair device into a specific color.

	@param {unsigned char} r value of Red for the LED device
	@param {unsigned char} g value of Green for the LED device
	@param {unsigned char} b value of Blue for the LED devie
	@return void
	*/

	void set_all_color(unsigned char r, unsigned char g, unsigned char b) {
		CorsairLedColor corsair_led_color;
		corsair_led_color.r = r;
		corsair_led_color.b = b;
		corsair_led_color.g = g;

		if (debug) std::cout << "[CPeripheral] Set color " << (int)r << " , " << (int)g << " , " << (int)b << " to All Corsair Devices" << std::endl;

		for (int i = 0; i < 500; i++) {
			corsair_led_color.ledId = (CorsairLedId)i;
			CorsairSetLedsColors(1, &corsair_led_color);
		}
		return;
	}

	/**
	A function for releasing Corsair ICUE SDK control back.

	@param void
	@return void	
	*/

	void stop(void) {
		/* A Method for releasing CUE SDK controls. */
		CorsairReleaseControl(CAM_ExclusiveLightingControl);
		return;
	}
};

