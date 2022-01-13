#include <stdio.h>
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 6
#define I2C_PORT i2c0

#define LSM6DSOX_ADDRESS            0x6A

#define LSM6DSOX_WHO_AM_I_REG       0X0F
#define LSM6DSOX_CTRL1_XL           0X10
#define LSM6DSOX_CTRL2_G            0X11

#define LSM6DSOX_STATUS_REG         0X1E

#define LSM6DSOX_CTRL6_C            0X15
#define LSM6DSOX_CTRL7_G            0X16
#define LSM6DSOX_CTRL8_XL           0X17

#define LSM6DSOX_OUTX_L_G           0X22
#define LSM6DSOX_OUTX_H_G           0X23
#define LSM6DSOX_OUTY_L_G           0X24
#define LSM6DSOX_OUTY_H_G           0X25
#define LSM6DSOX_OUTZ_L_G           0X26
#define LSM6DSOX_OUTZ_H_G           0X27

#define LSM6DSOX_OUTX_L_XL          0X28
#define LSM6DSOX_OUTX_H_XL          0X29
#define LSM6DSOX_OUTY_L_XL          0X2A
#define LSM6DSOX_OUTY_H_XL          0X2B
#define LSM6DSOX_OUTZ_L_XL          0X2C
#define LSM6DSOX_OUTZ_H_XL          0X2D

void init_LSM6(){
    //Init
    sleep_ms(1000);
    uint8_t reg = LSM6DSOX_WHO_AM_I_REG;
    uint8_t chipID[1];
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, LSM6DSOX_ADDRESS, chipID, 1, false);
    if(chipID[0] != 0x6C){
        printf("Incorrect chip ID");
    }

    uint8_t conf[2];
    conf[0] = LSM6DSOX_CTRL2_G;
    conf[1] = 0x4C;
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, conf, 2, false);

    conf[0] = LSM6DSOX_CTRL1_XL;
    conf[1] = 0x4A;
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, conf, 2, false);

    conf[0] = LSM6DSOX_CTRL7_G;
    conf[1] = 0x00;
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, conf, 2, false);

    conf[0] = LSM6DSOX_CTRL8_XL;
    conf[1] = 0x09;
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, conf, 2, false);


}

int readAcceleration()
{
    int16_t data[3];
    uint8_t reg = LSM6DSOX_OUTX_L_XL;
    i2c_write_blocking(I2C_PORT, LSM6DSOX_ADDRESS, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, LSM6DSOX_ADDRESS, (uint8_t*)data, sizeof(data), false);
    float x,y,z;
    x = data[0] * 4.0 / 32768.0;
    y = data[1] * 4.0 / 32768.0;
    z = data[2] * 4.0 / 32768.0;
    printf("X: %6.2f  Y: %6.2f  Z: %6.2f", x, y, z);
    return 0;
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(12, GPIO_FUNC_I2C);
    gpio_set_function(13, GPIO_FUNC_I2C);
    gpio_pull_up(12);
    gpio_pull_up(13);

    init_LSM6();





  while (true){
    gpio_put(LED_PIN, GPIO_ON);
    printf("LED ON\n");
    readAcceleration();
    sleep_ms(2000);
    gpio_put(LED_PIN, GPIO_OFF);
      printf("LED OFF\n");
    sleep_ms(2000);
  }
}
