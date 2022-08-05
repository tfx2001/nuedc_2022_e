#if !defined(__SERVO_H)
#define __SERVO_H

#include <stdint.h>

void servo_init();
void servo_set_deg(uint8_t n, float deg);

#endif // __SERVO_H
