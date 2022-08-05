#if !defined(__SETTING_H)
#define __SETTING_H

#include <stdint.h>
#include <stdbool.h>

#define SETTING_MAGIC_NUMBER 0x4362BD46

typedef struct
{
    uint32_t magic_number;
    int16_t servo_ver_offset;
    int16_t servo_hor_offset;
    int16_t sound_speed;
} setting_t;

setting_t setting_init(void);
bool setting_save(const setting_t *data);
void setting_read(setting_t *data);

#endif // __SETTING_H
