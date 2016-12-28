#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"

int main(){
	mraa_i2c_context accel, gyro, mag;
	accel =accel_init(); //only thing here is the initializations and the acceleration scales and g scale and m scale
	set_accel_scale(accel, A_SCALE_2G);
	gyro =gyro_init();
	set_gyro_scale(gyro, G_SCALE_245DPS);
	mag =mag_init();
	set_mag_scale(mag, M_SCALE_2GS);

	return 0;
}
