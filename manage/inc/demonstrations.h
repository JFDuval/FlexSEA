#ifndef DEMOS_H_
#define DEMOS_H_

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 2 / 3)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)
#define RGB_ON_TICKS (BLINK_ON_TICKS/2)

//Prototypes
void demo_1(void);
void demo_2(void);
void demo_3(void);
void demo_4(void);
void demo_spi_rx(void);
void demo_spi_rx_2(void);
void demo_spi_rx_3(void);

// ----------------------------------------------------------------------------

#endif // DEMOS_H_
