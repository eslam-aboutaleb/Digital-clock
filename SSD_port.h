/* ////////////////////////////////////////////////////////////////////////////
/ Author :Eslam Aboutaleb
/
/
/////////////////////////////////////////////////////////////////////////// */

#ifndef SSD_PORT_H
#define SSD_PORT_H

/* SSD */
#define SSD_DATA_PORT_DR        (GPIOA)
#define SSD_DATA_PORT_CR        (GPIOA)


/*SSD pins*/
#define SSD_PIN_1               (GPIO_PIN_0)
#define SSD_PIN_2               (GPIO_PIN_1)
#define SSD_PIN_3               (GPIO_PIN_2)
#define SSD_PIN_4               (GPIO_PIN_3)
#define SSD_PIN_5               (GPIO_PIN_4)
#define SSD_PIN_6               (GPIO_PIN_5)
#define SSD_PIN_7               (GPIO_PIN_6)
#define SSD_PIN_8               (GPIO_PIN_7)



#define SSD_HOURS_TENS_DR       (GPIOB)
#define SSD_HOURS_TENS_CR       (GPIOB)
#define SSD_HOURS_TENS_PIN      (GPIO_PIN_7)

#define SSD_HOURS_UNITS_DR      (GPIOB)
#define SSD_HOURS_UNITS_CR      (GPIOB)
#define SSD_HOURS_UNITS_PIN     (GPIO_PIN_6)

#define SSD_MINUTES_TENS_DR     (GPIOB)
#define SSD_MINUTES_TENS_CR     (GPIOB)
#define SSD_MINUTES_TENS_PIN    (GPIO_PIN_5)

#define SSD_MINUTES_UNITS_DR    (GPIOB)
#define SSD_MINUTES_UNITS_CR    (GPIOB)
#define SSD_MINUTES_UNITS_PIN   (GPIO_PIN_4)



#endif

