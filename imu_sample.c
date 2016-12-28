#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
//we need to include 3 things. first thing is standard for all c codes, 2nd thing is well, some kind of library that contains 3 parameters, which are accel, gyro, mag, and the 3rd one behing some kind of library that holds most of the functions necessary to use in the sensors.
int main(){ //typical main method
	mraa_i2c_context accel, gyro, mag; //these 3 "context" are supposed to be the 3 main paramters of focus,
	accel =accel_init(); //we set acceleration to initialize a
	set_accel_scale(accel, A_SCALE_2G); //set acceleration to change to something we say a scale 2g to identify what things
	set_accel_ODR(accel, A_ODR_100); //set acceleration order to a certain orientation so that we 
	gyro =gyro_init();//set the gyro to initialize
	set_gyro_scale(gyro, G_SCALE_245DPS);//we scale it to a certain 245DPS idk what that means yet but i can looky up
	set_gyro_ODR(gyro, G_ODR_190_BW_70); //g odr, i guess order of the gyro, is supposed to do something with 190 and 70
	mag =mag_init(); //initialize the magnitude
	set_mag_scale(mag, M_SCALE_2GS);//same
	set_mag_ODR(mag, M_ODR_125);//same but ODR this time is kinda like the acceleration orientation order e

	return 0;
}
