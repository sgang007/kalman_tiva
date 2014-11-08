
//http://www.linushelgesson.se/2012/04/pitch-and-roll-estimating-kalman-filter-for-stabilizing-quadrocopters/

#include "kalman.h"
 
// Structs for containing filter data
kalman_data pitch_data;
kalman_data roll_data;

void setup()
{
    kalman_init(&pitch_data);
    kalman_init(&roll_data);
}

void read_accelerometer(float* acc_x, float* acc_y, float* acc_z){

}
void read_gyro(float* gyr_x, float* gyr_y, float* gyr_z){

}

void loop()
{
  // put your main code here, to run repeatedly:
  	float acc_x, acc_y, acc_z;
        float gyr_x, gyr_y, gyr_z;
        float acc_pitch, acc_roll;
        float pitch, roll;
    
        // Read sensor
        read_accelerometer(&acc_x, &acc_y, &acc_z);
        read_gyro(&gyr_x, &gyr_y, &gyr_z);
 
        // Calculate pitch and roll based only on acceleration.
        acc_pitch = atan2(acc_x, -acc_z);
        acc_roll = -atan2(acc_y, -acc_z);
 
        // Perform filtering
        kalman_innovate(&pitch_data, acc_pitch, gyr_x);
        kalman_innovate(&roll_data, acc_roll, gyr_y);
 
        // The angle is stored in state 1
        pitch = pitch_data.x1;
        roll = roll_data.x1;
       
 
        //100hz=10ms
        delay(10);
}


