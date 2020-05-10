#ifndef NITRO_SPI_PM_H_
#define NITRO_SPI_PM_H_

ENUMS_ALWAYS_INT_ON

typedef enum
{
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
} PMBackLightSwitch;

void PM_GetBackLight(PMBackLightSwitch * top, PMBackLightSwitch * bottom);

ENUMS_ALWAYS_INT_RESET

#endif //NITRO_SPI_PM_H_
