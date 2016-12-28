#include <unistd.h>
#include <mraa/aio.h>
#include <stdio.h>
#include "floatfann.h"
//goal is to input 6 values , we have an array of 6 values as input
//next step is to have an array output of 3 values, 1 for each thing we classify and ultimate goal is to see which one is closest to the correct classification of a certain type of motion.
int main()
{
    int i;
    int temp0, temp1, temp2,temp3, temp4, temp5, location;
    uint16_t value0, value1, value2, value3, value4, value5;
    float max; //
    fann_type *calc_out;//object
    fann_type input[6];//#of inputs 
    struct fann *ann;
    mraa_aio_context lightsensor0, lightsensor1, lightsensor2;
    
    ann = fann_create_from_file("TEST.net");

    lightsensor0 = mraa_aio_init(0);
    lightsensor1 = mraa_aio_init(1);
    lightsensor2 = mraa_aio_init(2);

    while (1) {
        temp0 = 0;
        temp1 = 0;
        temp2 = 0;
        max = -100;

        for (i = 0; i < 50; i++) {
            temp0 += mraa_aio_read(lightsensor0);
            temp1 += mraa_aio_read(lightsensor1);
            temp2 += mraa_aio_read(lightsensor2);
            usleep(10000);
        }

        value0 = temp0 / 50;
        value1 = temp1 / 50;
        value2 = temp2 / 50;

        input[0] = (float) value0 / 1000;
        input[1] = (float) value1 / 1000;
        input[2] = (float) value2 / 1000;
        calc_out = fann_run(ann, input);

        for (i = 0; i < 5; i++) {
            if (calc_out[i] > max) { //if the location is a specific input of brightness at this location, we "max" and say that is the location, for ever change in max. In other words, max is our way of identifying where our location is in the light sensor case, for the weight lifting, max will determine which type of motion we are closer to: curl or press.
                max = calc_out[i];
                location = i;
            }
        }
//find max value for the light sensors
	printf("Light sensor values: %d, %d, %d -> location is %d\n", value0, value1, value2, location);
        sleep(1);
    }
 return 0;
 
