#pragma once

#include <stdint.h>
#include <stdbool.h>

#define NS2009_ADDR 0x48

#define NS2009_MODE_12B 0x00
#define NS2009_MODE_8B 0x01

#define NS2009_POWER_DOWN_ENABLE 0x00
#define NS2009_POWER_DOWN_DISABLE 0x01

typedef enum
{
  InputX = 0x0C,
  InputY = 0x0D,
} ns2009_input_t;

typedef struct
{
  uint8_t reserve_b0 : 1;
  uint8_t mode : 1;
  uint8_t power_down : 1;
  uint8_t reserve_b3 : 1;
  uint8_t input : 4;
} ns2009_cmd_t;

void ns2009_init();
bool ns2009_is_touch();
uint16_t ns2009_read_pos(ns2009_input_t input);
