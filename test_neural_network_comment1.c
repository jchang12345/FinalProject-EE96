//#include <unistd.h>
//#include <mraa/aio.h>
//#include <stdio.h>
#include "floatfann.h"
#include <stdio.h>
#include <unistd.h>
#include <mraa/i2c.h>
#include "LSM9DS0.h"
#include <math.h>
float calculate_magnitude(data_t data)
{
    return sqrt(data.x*data.x+data.y*data.y+data.z*data.z);
}
// the basic idea is, you give an array input[] (in our case, 6 variables from 9Dof to the machine learning object fann)
// and the maching learning program returns you an array output[] (in our case, 3 variable for each output)
// the right output has a value bigger than the integer <max>

int main()
{
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
   int i;
    int temp0, temp1, temp2,temp3, temp4, temp5, location;
    // location to output data, we need 6 temporary data
    uint16_t value0, value1, value2, value3, value4, value5;
    // the variable to store the refined input data, later put into the input[]
    float max;             // I guess the right output(decided) by the machine learning has value > max
    //max helps us determine which motion is being represented.
    fann_type *calc_out;  // create a machine learning object pointer fann *calc_out
    fann_type input[6];  // in our case, we have 6 input variables, fann_type input[3];
    struct fann *ann; // I guess <ann> is a pointer to the Fann object
   // mraa_aio_context lightsensor0, lightsensor1, lightsensor2;
    
    ann = fann_create_from_file("MOTION_TEST.net");

  //  lightsensor0 = mraa_aio_init(0); // from here we should substitute by 9dof ignit
   // lightsensor1 = mraa_aio_init(1);
   // lightsensor2 = mraa_aio_init(2); // to here

    while (1) {
        temp0 = 0;
        temp1 = 0;
        temp2 = 0;
        temp3 = 0;
        temp4 = 0;
        temp5 = 0;
        
        max = -100;

        for (i = 0; i < 50; i++) {
            temp0 += mraa_aio_read(lightsensor0); // from here, we should substitute by 9dof
            temp1 += mraa_aio_read(lightsensor1);
            temp2 += mraa_aio_read(lightsensor2);  // to here
            usleep(10000); // DELAY
        }

        value0 = temp0 / 50;
        value1 = temp1 / 50;
        value2 = temp2 / 50;
        value3 = temp3 / 50;
        value4 = temp4 / 50;
        value5 = temp5 / 50;

        input[0] = (float) value0 / 1000; // collect refined (average)input data, store them into the input array
        input[1] = (float) value1 / 1000;
        input[2] = (float) value2 / 1000;
        input[3] = (float) value3 / 1000;
        inout[4] = (float) value4 / 1000;
        input[5] = (float) value5 / 1000;
        
        calc_out = fann_run(ann, input);
        // pass the refined input data to the machine learning object fann, and let it decide what is the output,
        // store the output into calc_out pointer,actually it's an array

        for (i = 0; i < 5; i++) {
            if (calc_out[i] > max) {
                max = calc_out[i];
                location = i; // the right output has calc_out value bigger than max
            }
        }
//we want to print out all the readings and then make a determination of the 
//type of motion based on the readings and how it is grouped.
	printf("Light sensor values: %d, %d, %d -> location is %d\n", value0, value1, value2, location);
        sleep(1);
    }
    fann_destroy(ann);
    return 0;
}
