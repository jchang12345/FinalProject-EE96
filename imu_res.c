#include <stdio.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"

int main(){
	mraa_i2c_context accel, gyro, mag;
	float a_res, g_res, m_res;
	accel_scale_t a_scale;
	gyro_scale_t g_scale;
	mag_scale_t m_scale;

	a_scale= A_SCALE_2G;
	g_scale= G_SCALE_245DPS;
	m_scale=M_SCALE_2GS;

	accel =accel_init();
	set_accel_ODR(accel, A_ODR_100);
	set_accel_scale(accel, a_scale);
	a_res= calc_accel_res(a_scale);

	gyro =gyro_init();
	set_gyro_ODR(gyro, G_ODR_190_BW_70);
	set_gyro_scale(gyro, g_scale);
	g_res=calc_gyro_res(g_scale);

	mag =mag_init();
	set_mag_ODR(mag, M_ODR_125);
	set_mag_scale(mag, m_scale);
	m_res=calc_mag_res(m_scale);

	return 0;
}
