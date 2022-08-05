#if !defined(__TMP275_H)
#define __TMP275_H

#include <stdbool.h>
#include <stdint.h>

#define TMP275_DEV_ADDR (0x48)

#define TMP275_RES_9_BITS_LSB (0.5F)
#define TMP275_RES_10_BITS_LSB (0.25F)
#define TMP275_RES_11_BITS_LSB (0.125F)
#define TMP275_RES_12_BITS_LSB (0.0625F)

typedef enum {
    TMP275_REG_TEMP = 0,
    TMP275_REG_CONFIG,
    TMP275_REG_T_LOW,
    TMP275_REG_T_HIGH,
} tmp275_reg_t;

typedef enum {
    TMP275_MODE_COMPARATOR = 0,
    TMP275_MODE_INTERRUPT,
} tmp275_mode_t;

typedef enum {
    TMP275_POL_ACTIVE_LOW = 0,
    TMP275_POL_ACTIVE_HIGH,
} tmp275_pol_t;

typedef enum {
    TMP275_FQ_1 = 0,
    TMP275_FQ_2,
    TMP275_FQ_4,
    TMP275_FQ_6,
} tmp275_fq_t;

typedef enum {
    TMP275_RES_9_BITS = 0,
    TMP275_RES_10_BITS,
    TMP275_RES_11_BITS,
    TMP275_RES_12_BITS,
} tmp275_res_t;

typedef struct {
    bool shutdown : 1;
    tmp275_mode_t mode : 1;
    tmp275_pol_t polarity : 1;
    tmp275_fq_t fault_queue : 2;
    tmp275_res_t resolution : 2;
    bool one_shot : 1;
} tmp275_config_t;

typedef struct {
    tmp275_res_t res;
} tmp275_t;

#ifdef __cpluscplus
extern "C" {
#endif

void tmp275_init(tmp275_t *handle, tmp275_config_t *config);
float tmp275_read_temp(tmp275_t *handle);

#ifdef __cpluscplus
}
#endif

#endif // __TMP275_H