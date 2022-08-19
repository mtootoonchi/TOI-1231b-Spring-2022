#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 25

// Set Memory
absolute_time_t R1_time;
absolute_time_t R2_time;
absolute_time_t R3_time;
absolute_time_t R4_time;
bool R1 = false;
bool R2 = false;
bool R3 = false;
bool R4 = false;

void second_core_code() {

	while (true) {
		if (R1) {
			gpio_put(18, GPIO_ON);
			if (absolute_time_diff_us(R1_time, get_absolute_time()) >= 5000000) {
				R1 = false;
				gpio_put(18, GPIO_OFF);
			}
		}

		if (R2) {
			gpio_put(19, GPIO_ON);
			if (absolute_time_diff_us(R2_time, get_absolute_time()) >= 5000000) {
				R2 = false;
				gpio_put(19, GPIO_OFF);
			}
		}

		if (R3) {
			gpio_put(20, GPIO_ON);
			if (absolute_time_diff_us(R3_time, get_absolute_time()) >= 5000000) {
				R3 = false;
				gpio_put(20, GPIO_OFF);
			}
		}

		if (R4) {
			gpio_put(21, GPIO_ON);
			if (absolute_time_diff_us(R4_time, get_absolute_time()) >= 5000000) {
				R4 = false;
				gpio_put(21, GPIO_OFF);
			}
		}
	}
}

int main() {
	// Set Memory
	R1_time = get_absolute_time();
	R2_time = get_absolute_time();
	R3_time = get_absolute_time();
	R4_time = get_absolute_time();

	// Set onboard LED
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_init(18);
	gpio_set_dir(18, GPIO_OUT);
	gpio_init(19);
	gpio_set_dir(19, GPIO_OUT);
	gpio_init(20);
	gpio_set_dir(20, GPIO_OUT);
	gpio_init(21);
	gpio_set_dir(21, GPIO_OUT);

  // Set USB
	stdio_usb_init();
	gpio_put(LED_PIN, GPIO_ON);
	sleep_ms(2000);
	gpio_put(LED_PIN, GPIO_OFF);

	multicore_launch_core1(second_core_code);

	while (true) {
		char userInput = getchar();

		if (userInput == 'a')
		{
			R1_time = get_absolute_time();
			R1 = true;
			printf("R1\n");
		}
		else if (userInput == 'b') {
			R2_time = get_absolute_time();
			R2 = true;
			printf("R2\n");
		}
		else if (userInput == 'c') {
			R3_time = get_absolute_time();
			R3 = true;
			printf("R3\n");
		}
		else if (userInput == 'd') {
			R4_time = get_absolute_time();
			R4 = true;
			printf("R4\n");
		}
	}
}
