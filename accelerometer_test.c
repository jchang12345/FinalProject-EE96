#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
#include <math.h>

float calculate_magnitude(data_t data)
{
		return sqrt(data.x*data.x+data.y*data.y+data.z*data.z);
}

int main() {
		mraa_i2c_context accel, gyro, mag;
		float a_res, g_res, m_res;
		accel_scale_t a_scale;
		gyro_scale_t g_scale;
		mag_scale_t m_scale;
		data_t ad, gd, md; //Accel Data, Gyro Data, Mag Data	
		data_t Go; //Gyro Offset
		a_scale = A_SCALE_2G;
		g_scale	= G_SCALE_245DPS;
		m_scale = M_SCALE_2GS;

												accel =	accel_init();	
												set_accel_scale(accel, a_scale);
		set_accel_ODR(accel, A_ODR_100);
		a_res = calc_accel_res(a_scale);	
		gyro = gyro_init();			
		set_gyro_scale(gyro, g_scale);
		set_gyro_ODR(gyro, G_ODR_190_BW_70);
		g_res = calc_gyro_res(g_scale);	
		mag = mag_init();	
		set_mag_scale(mag, m_scale);
		set_gyro_ODR(gyro, G_ODR_190_BW_70);	
		m_res = calc_mag_res(m_scale);
		//Go = calc_gyro_offset(gyro, g_res);
		while (1) {
		ad = read_accel(accel, a_res);
		gd = read_gyro(gyro, g_res);
		md = read_mag(mag, m_res);		
		gd.x = gd.x - Go.x;
		gd.y = gd.y - Go.y;
		gd.z = gd.z - Go.z;	
		printf("Current Data:\n");	
		printf("\tAccelerometer:\t|: %f\n gs",/*ad.x, ad.y, ad.z,*/ calculate_magnitude(ad));
		if (ad.z>0)
			printf("UP\n");
		else printf("DOWN\n");
		usleep(250000);
		}
		return 0;
	}
