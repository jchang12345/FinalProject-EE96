#include <unistd.h>
#include <mraa/i2c.h>
#include <stdio.h>
#include <string.h>
#include "LSM9DS0.h"
#include "floatfann.h"




int main()
{
    int i, success_flag;
    int motionType;
    float gyro_tempX, gyro_tempY, gyro_tempZ, accel_tempX, accel_tempY, accel_tempZ;
    float gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ;
    float g_res, a_res; // declare g_res, a_res
    accel_scale_t a_scale = A_SCALE_2G; // define a_scale, g_scale
    gyro_scale_t g_scale = G_SCALE_245DPS;
    mraa_i2c_context gyro, accel;
    
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
    
    float max;
    fann_type *calc_out;
    fann_type input[6];
    struct fann *ann;
    ann = fann_create_from_file("MOTION_TEST.net");

    while (1) {
        
        gyro_tempX = 0;
        gyro_tempY= 0;
        gyro_tempZ= 0;
        accel_tempX = 0;
        accel_tempY = 0;
        accel_tempZ = 0;
        
        gyro_valX = 0;
        gyro_valY = 0;
        gyro_valZ = 0;
        accel_valX = 0;
        accel_valY = 0;
        accel_valZ = 0;
        
        printf("Hit enter, then do one motion and hit enter.\n");
        do {
            success_flag = getchar();
        } while (success_flag != '\n');
        success_flag = '\0';
        
        max = -100;
        
        do {
            success_flag = getchar();
            gd = read_gyro(gyro, g_res);
            ad = read_accel(accel, a_res);
        
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
        
        //set input values to 0 to 1
        
        input[0] = (gyro_valX + 30) / 60;
        input[1] = (gyro_valY + 30) / 60;
        input[2] = (gyro_valZ + 30) / 60;
        input[3] = (accel_valX + 1) / 2;
        input[4] = (accel_valY + 1) / 2;
        input[5]= (accel_valZ + 1) / 2;

        // collect refined (average)input data, store them into the input array
        
        
        calc_out = fann_run(ann, input);
                for (i = 0; i < 3; i++) {
            if (calc_out[i] > max) {
                max = calc_out[i];
                motionType = i;
            }
        }
        
       char motion[100]="";
       switch (motionType) {
            case 0:
              strcpy(motion, "bicep curl");
              break;
            case 2:
              strcpy(motion, "random motion");
              break;
            case 1:
              strcpy(motion, "shoulderpress");
              break;
            default:
               strcpy(motion, "invalid motion");
    }

	printf("9DOF motion sensor: %f, %f, %f, %f, %f, %f -> motion type is %s \n", gyro_valX, gyro_valY, gyro_valZ, accel_valX, accel_valY, accel_valZ, motion);
        sleep(1);
    }
    fann_destroy(ann);
    return 0;
}
