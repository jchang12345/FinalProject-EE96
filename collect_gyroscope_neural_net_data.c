#include <stdio.h>
#include <unistd.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
#include <math.h>
float calculate_magnitude(data_t data)
{
	return sqrt(data.x*data.x+data.y*data.y+data.z*data.z);
}
int main() 
{
	int i, k, j, success_flag;
	int location;
	int output[3] = { -1, -1, -1 };
	float gyro_tempX, gyro_tempY, gyro_tempZ, accel_tempX, accel_tempY, accel_tempZ;
	float gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ;
	mraa_i2c_context gyro, accel;
	float g_res, a_res;
	accel_scale_t a_scale = A_SCALE_2G;
	gyro_scale_t g_scale = G_SCALE_245DPS;
	uint16_t value;
	data_t gd, ad;
	data_t Go;
	
	accel = accel_init();
	set_accel_scale(accel, a_scale);
	set_accel_ODR(accel, A_ODR_100);
	a_res=calc_accel_res(a_scale);
	gyro = gyro_init();
	set_gyro_scale(gyro, g_scale);
	set_gyro_ODR(gyro, G_ODR_190_BW_70);
	g_res = calc_gyro_res(g_scale);

	Go = calc_gyro_offset(gyro, g_res);
	printf("Done with offset.\n");
	for (;;)
	{
		do {
			success_flag = getchar();
		} while (success_flag != '\n');
		success_flag = '\0';
		i = 0;
		gyro_tempX = 0;
		gyro_tempY = 0;
		gyro_tempZ = 0;
		accel_tempX = 0;
		accel_tempY = 0;
		accel_tempZ = 0;
		gyro_valX = 0;
		gyro_valY = 0;
		gyro_valZ = 0;
		accel_valX = 0;
		accel_valY = 0;
		accel_valZ = 0;
		
		/*do {
			success_flag = getchar();
		//gd = read_gyro(gyro, g_res);
			ad = read_accel(accel, a_res);
			i++;
			gyro_tempX = gd.x - Go.x;
			gyro_tempY = gd.y - Go.y;
			gyro_tempZ = gd.z - Go.z;
			accel_tempX = ad.x;
			accel_tempY = ad.y;
			accel_tempZ = ad.z;
			printf("TEMP %f %f %f %f %f %f\n", gyro_tempX, gyro_tempY, gyro_tempZ, accel_tempX, accel_tempY, accel_tempZ);
			if (gyro_tempX > gyro_valX || gyro_tempX < (-1*gyro_valX))
				gyro_valX = gyro_tempX;
			if (gyro_tempY > gyro_valY || gyro_tempY < (-1*gyro_valY))
				gyro_valY = gyro_tempY;
			if (gyro_tempZ > gyro_valZ || gyro_tempZ < (-1*gyro_valZ))
				gyro_valZ = gyro_tempZ;
			if (accel_tempX > accel_valX || accel_tempX < (-1*accel_valX))
				accel_valX = accel_tempX;
			if (accel_tempY > accel_valY || accel_tempY < (-1 * accel_valY))
				accel_valY = accel_tempY;
			if (accel_tempZ > accel_valZ || accel_tempZ < (-1 * accel_valZ))
				accel_valZ = accel_tempZ;
			printf("VAL %f %f %f %f %f %f\n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ);
		} while (success_flag != '\n');
	}*/


	// train data store to test_data.txt
	FILE *fp;
	fp = fopen("./motion_test_data.txt", "wb");
	fprintf(fp, "9\t6\t3\n");

	// generate the test_data.txt output
	for (k = 0; k < 50; k++)
	{
		printf("Hit enter, then do one curl and hit enter.\n");
		do {
			success_flag = getchar();
		} while (success_flag != '\n');
		success_flag = '\0';
		i = 0;
		gyro_tempX = 0;
		gyro_tempY = 0;
		gyro_tempZ = 0;
		accel_tempX = 0;
		accel_tempY = 0;
		accel_tempZ = 0;
		gyro_valX = 0;
		gyro_valY = 0;
		gyro_valZ = 0;
		accel_valX = 0;
		accel_valY = 0;
		accel_valZ = 0;
		do {
			success_flag = getchar();
			gd = read_gyro(gyro, g_res);
			ad = read_accel(accel, a_res);
			i++;
			gyro_tempX = gd.x - Go.x;
			gyro_tempY = gd.y - Go.y;
			gyro_tempZ = gd.z - Go.z;
			accel_tempX = ad.x;
			accel_tempY = ad.y;
			accel_tempZ = ad.z;
			if (gyro_tempX > gyro_valX || (gyro_tempX < (-1*gyro_valX && gyro_tempX < 0)))
				gyro_valX = gyro_tempX;
			if (gyro_tempY > gyro_valY || (gyro_tempY < (-1*gyro_valY && gyro_tempY < 0)))
				gyro_valY = gyro_tempY;
			if (gyro_tempZ > gyro_valZ || (gyro_tempZ < (-1*gyro_valZ && gyro_tempZ < 0)))
				gyro_valZ = gyro_tempZ;
			if (accel_tempX > accel_valX || (accel_tempX < (-1*accel_valX && accel_tempX < 0)))
				accel_valX = accel_tempX;
			if (accel_tempY > accel_valY || (accel_tempY < (-1 * accel_valY && accel_tempY < 0)))
				accel_valY = accel_tempY;
			if (accel_tempZ > accel_valZ || (accel_tempZ < (-1 * accel_valZ && accel_tempZ < 0)))
				accel_valZ = accel_tempZ;
		} while (success_flag != '\n');

		printf("%f\t%f\t%f\t%+f\t%+f\t%+f\n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ);

		//Set values 0-1.
		//gyro_valX = gyro_valX / 300;
		//gyro_valY = gyro_valY / 300;
		//gyro_valZ = gyro_valZ / 300;
		//accel_valX = accel_valX / 3;
		//accel_valY = accel_valY / 3;
		//accel_valZ = accel_valZ / 3;

		output[0] = 1;
		//write input, output to test_data.txt as training file format
		fprintf(fp, "%5f\t%5f\t%5f\t%5f\t%5f\t%5f\n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ); //Change this variable after scaling it properly.
		fprintf(fp, "%d\t%d\n", output[0], output[1], output[2]);
	}
	output[0] = -1;
	// generate the test_data.txt output
	for (k = 0; k < 50; k++)
	{
		printf("Hit enter, then do one shoulder press and hit enter.\n");
		do {
			success_flag = getchar();
		} while (success_flag != '\n');
		success_flag = '\0';
		i = 0;
		gyro_tempX = 0;
		gyro_tempY = 0;
		gyro_tempZ = 0;
		accel_tempX = 0;
		accel_tempY = 0;
		accel_tempZ = 0;
		gyro_valX = 0;
		gyro_valY = 0;
		gyro_valZ = 0;
		accel_valX = 0;
		accel_valY = 0;
		accel_valZ = 0;
		do {
			success_flag = getchar();
			gd = read_gyro(gyro, g_res);
			ad = read_accel(accel, a_res);
			i++;
			gyro_tempX = gd.x - Go.x;
			gyro_tempY = gd.y - Go.y;
			gyro_tempZ = gd.z - Go.z;
			accel_tempX = ad.x;
			accel_tempY = ad.y;
			accel_tempZ = ad.z;
			if (gyro_tempX > gyro_valX || (gyro_tempX < (-1*gyro_valX && gyro_tempX < 0)))
				gyro_valX = gyro_tempX;
			if (gyro_tempY > gyro_valY || (gyro_tempY < (-1*gyro_valY && gyro_tempY < 0)))
				gyro_valY = gyro_tempY;
			if (gyro_tempZ > gyro_valZ || (gyro_tempZ < (-1*gyro_valZ && gyro_tempZ < 0)))
				gyro_valZ = gyro_tempZ;
			if (accel_tempX > accel_valX || (accel_tempX < (-1*accel_valX && accel_tempX < 0)))
				accel_valX = accel_tempX;
			if (accel_tempY > accel_valY || (accel_tempY < (-1 * accel_valY && accel_tempY < 0)))
				accel_valY = accel_tempY;
			if (accel_tempZ > accel_valZ || (accel_tempZ < (-1 * accel_valZ && accel_tempZ < 0)))
				accel_valZ = accel_tempZ;
		} while (success_flag != '\n');

		printf("%+f\t%+f\t%+f\t%+f\t%+f\t%+f\n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ);

		//Set values 0-1.
		//gyro_valX = gyro_valX / 300;
		//gyro_valY = gyro_valY / 300;
		//gyro_valZ = gyro_valZ / 300;
		//accel_valX = accel_valX / 3;
		//accel_valY = accel_valY / 3;
		//accel_valZ = accel_valZ / 3;

		output[1] = 1;
		//write input, output to test_data.txt as training file format
		fprintf(fp, "%f\t%f\t%f\t%f\t%f\t%f\n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ); //Change this variable after scaling it properly.
		fprintf(fp, "%d\t%d\n", output[0], output[1], output[2]);
	}
	output[1] = -1;

	// close everything
	fclose(fp);
	
	return 0;
}
}
