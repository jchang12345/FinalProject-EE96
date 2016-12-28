#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
//everything actually started from here, all of the 3 initializations.
int main(){
	mraa_i2c_context accel, gyro, mag;
	accel =accel_init();
	gyro =gyro_init();
	mag =mag_init();

	return 0;
}
