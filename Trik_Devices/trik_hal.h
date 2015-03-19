/*
 * trik_hal.h
 *
 *  Imported from driverlib: Fabruary 4, 2015
 */

#ifndef TRIK_HAL_H_
#define TRIK_HAL_H_

#define GPIO_PIN0                                                          0x01
#define GPIO_PIN1                                                          0x02
#define GPIO_PIN2                                                          0x04
#define GPIO_PIN3                                                          0x08
#define GPIO_PIN4                                                          0x10
#define GPIO_PIN5                                                          0x20
#define GPIO_PIN6                                                          0x40
#define GPIO_PIN7                                                          0x80
#define GPIO_PIN8                                                         0x100
#define GPIO_PIN9                                                         0x200
#define GPIO_PIN10                                                        0x400
#define GPIO_PIN11                                                        0x800
#define GPIO_PIN12                                                       0x1000
#define GPIO_PIN13                                                       0x2000
#define GPIO_PIN14                                                       0x4000
#define GPIO_PIN15                                                       0x8000
#define GPIO_ALL    GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
                    GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7

void _initPorts(void);
void _initClocks(uint32_t mclkFreq);


#endif /* TRIK_HAL_H_ */
