#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
#include <math.h>
//the final product of tutorial 7 and motoin sensing and detecting motions going up and down
float calculate_magnitude(data_t data)
{
	return sqrt(data.x*data.x+data.y*data.y+data.z*data.z);
}

int main(){
	mraa_i2c_context accel, gyro, mag;
	float a_res, g_res, m_res;
	accel_scale_t a_scale;
	gyro_scale_t g_scale;
	mag_scale_t m_scale;
	data_t ad, gd, md; //accel data, gyro data, mag data
	data_t Go; //gyro offset

	a_scale= A_SCALE_2G; //we have +/- 2 g or gravity
	g_scale= G_SCALE_245DPS; //+/-245 degrees per second, aka angular velocity
	m_scale=M_SCALE_2GS;// +/-2gauss magnetic fields aka jacob murrays

	accel =accel_init();//initailze acceleration
	set_accel_ODR(accel, A_ODR_100); //ORDER in terms of power down mode, and given by hertz, we chose 100 so 100Hz.
	set_accel_scale(accel, a_scale); //we can change this by changing the above b/c we declared ascale to be the 2gravity
	a_res= calc_accel_res(a_scale);

	gyro =gyro_init();//initialize the gyroscope
	set_gyro_ODR(gyro, G_ODR_190_BW_70); //giving the ODR of 190 and BW bandwith of 70 or a rate of 190Hz,70BW.
	set_gyro_scale(gyro, g_scale); //setting this to whatever we had earlier for the angular velocity of the gyroscope. The gyroscope should be set to 245 degrees per second
	g_res=calc_gyro_res(g_scale);

	mag =mag_init(); //same drill, magnetometer is initialized to detect magnetic fields
	set_mag_ODR(mag, M_ODR_125);//the ODR we give it is 125 or 12.5 Hz
	set_mag_scale(mag, m_scale);//the magnitude scale we initialized earlier was 2 gauss or 2 Gs which can change based on what we want it to be.
	m_res=calc_mag_res(m_scale); 

	Go= calc_gyro_offset(gyro, g_res);

	while(1) {
		ad= read_accel(accel, a_res);
		gd= read_gyro(gyro, g_res);
		md= read_mag(mag, m_res);
		gd.x= gd.x - Go.x;
		gd.y= gd.y- Go.y;
		gd.z= gd.z- Go.z;

		printf("Current Data:\n");
		printf("\tAccel: |(A_x: %+f A_y: %+f A_z: %+f) |: %+f g\n",ad.x, ad.y, ad.z, calculate_magnitude(ad));
if(ad.z>0)
{
	printf("DOWN");
}
if(ad.z<0)
{
printf("UP");
}


		printf("\tGyro: |(G_x: %+f G_y: %+f G_z: %+f) |: %+f dps\n",gd.x, gd.y, gd.z, calculate_magnitude(gd));
		printf("\tMag : |(M_x: %+f M_y: %+f M_z: %+f) |: %+f gauss\n",md.x, md.y, md.z, calculate_magnitude(md));
		usleep(100000);
	}

	return 0;
}
