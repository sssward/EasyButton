#ifndef _EASYBUTTON_H_
#define _EASYBUTTON_H_

#include <stdint.h>

typedef enum {
    FREE,
    FIRST_PRESS,
    FIRST_RELEASE,
	SECOND_PRESS,
}ButtonState;

typedef enum {
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS,
}ButtonEvent;

typedef void (*eventHandler)(void);

typedef struct Button {
    uint8_t val;
    uint8_t valPre;
    uint16_t ticks; 
    uint8_t level;
    uint16_t doublePressTH;
    uint16_t longPressTH; 
    ButtonState state;
    uint8_t (*getButtonVal)(void);
    eventHandler F[3];
}Button;

void buttonInit(Button *button, uint8_t level, uint16_t doublePressTH, uint16_t longPressTH, uint8_t (*getButtonVal)(void));
void buttonLink(Button *button, ButtonEvent event, void (*eventHandler)(void));
void buttonScan(Button *button);

#endif
