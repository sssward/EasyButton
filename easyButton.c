#include "easyButton.h"

void buttonInit(Button *button, uint8_t level, uint16_t doublePressTH, uint16_t longPressTH, uint8_t (*getButtonVal)(void))
{
    button->level = level;
    button->doublePressTH = doublePressTH;
    button->longPressTH = longPressTH;
    button->getButtonVal = getButtonVal;
    button->val = level;
    button->valPre = level;
    button->ticks = 0;
    button->state = FREE;
    button->F[SINGLE_CLICK] = NULL;
    button->F[DOUBLE_CLICK] = NULL;
    button->F[LONG_PRESS]   = NULL;
}

void buttonLink(Button *button, ButtonEvent event, void (*eventHandler)(void))
{
    button->F[event] = eventHandler;
}

void buttonScan(Button *button)
{
    button->val = button->getButtonVal();
    switch (button->state)
    {
        case FREE:
        {
            if((button->val != button->level) && (button->valPre == button->level))
            button->state = FIRST_PRESS;
            break;
        }
        case FIRST_PRESS:
        {
            if(button->val == button->valPre)
            {
                button->ticks++;
                if(button->ticks >= button->longPressTH)
                {
                    button->ticks = 0;
                    button->state = FREE;
                    if(button->F[LONG_PRESS] != NULL)
                    button->F[LONG_PRESS]();
                }               
            }
            else
            {
                button->ticks = 0;
                button->state = FIRST_RELEASE;
            }
            break;
        }
        case FIRST_RELEASE:
        {
            if(button->val == button->valPre)
            {
                button->ticks++;
                if(button->ticks >= button->doublePressTH)
                {
                    button->ticks = 0;
                    button->state = FREE;
                    if(button->F[SINGLE_CLICK] != NULL)
                    button->F[SINGLE_CLICK]();
                }
            }
            else
            {
                button->ticks = 0;
                button->state = SECOND_PRESS;
            }
            break;
        }
        case SECOND_PRESS:
        {
            if(button->val != button->valPre)
            {
				button->state = FREE;
				if(button->F[DOUBLE_CLICK] != NULL)
				button->F[DOUBLE_CLICK]();
            }
            break;
        }
        default:
            break;
    }
    button->valPre = button->val;
}

