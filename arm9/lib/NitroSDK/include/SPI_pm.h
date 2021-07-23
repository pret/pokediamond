#ifndef NITRO_SPI_PM_H_
#define NITRO_SPI_PM_H_

ENUMS_ALWAYS_INT_ON

#define PM_TRIGGER_KEY              (1 << 0)
#define PM_TRIGGER_RTC_ALARM        (1 << 1)
#define PM_TRIGGER_COVER_OPEN       (1 << 2)
#define PM_TRIGGER_CARD             (1 << 3)
#define PM_TRIGGER_CARTRIDGE        (1 << 4)
typedef u32 PMWakeUpTrigger;

#define PM_PAD_LOGIC_OR    (0 << REG_PAD_KEYCNT_LOGIC_SHIFT)
#define PM_PAD_LOGIC_AND   (1 << REG_PAD_KEYCNT_LOGIC_SHIFT)
typedef u32 PMLogic;

typedef enum
{
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
} PMBackLightSwitch;

typedef enum
{
    PM_LCD_TOP = 0,
    PM_LCD_BOTTOM = 1,
    PM_LCD_ALL = 2
}
PMLCDTarget;

void PM_GetBackLight(PMBackLightSwitch * top, PMBackLightSwitch * bottom);
void PM_GoSleepMode(PMWakeUpTrigger trigger, PMLogic logic, u16 keyPattern);
u32 PM_SetBackLight(PMLCDTarget target, PMBackLightSwitch status);
u32 PM_ForceToPowerOff(void);
void PM_SetAmp(int gain);
void PM_SetAmpGain(int gain);

ENUMS_ALWAYS_INT_RESET

#endif //NITRO_SPI_PM_H_
