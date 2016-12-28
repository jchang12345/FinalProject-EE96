#include <stdio.h>
#include <unistd.h>
#include <mraa/aio.h>
//this one gives us the avg sensor values so we have a good idea on how to scale it down to a value between 0-1
int main() 
{
	int i;
	int temp0, temp1, temp2;
	uint16_t value0, value1, value2;
	mraa_aio_context lightsensor0, lightsensor1, lightsensor2;
//important to notice that the light sensors start off around 700 and should range from 100-500 at some point here
	lightsensor0 = mraa_aio_init(0);
	lightsensor1 = mraa_aio_init(1);
	lightsensor2 = mraa_aio_init(2);

	while(1) {

		temp0 = 0;
		temp1 = 0;
		temp2 = 0;

		for (i = 0; i < 50; i++) {
			temp0 += mraa_aio_read(lightsensor0);
			temp1 += mraa_aio_read(lightsensor1);
			temp2 += mraa_aio_read(lightsensor2);
			usleep(5000);
		}

		value0 = temp0 / 50;
		value1 = temp1 / 50;
		value2 = temp2 / 50;

		printf("Light sensor 0: %5d, Light sensor 1: %5d, Light sensor 2: %5d\n", value0, value1, value2);

		usleep(250000);
	}

	mraa_aio_close(lightsensor0);
	mraa_aio_close(lightsensor1);
	mraa_aio_close(lightsensor2);

	return 0;
}

