#if !defined(AUDIO_CAPTURE)
#define AUDIO_CAPTURE

#include <stdint.h>

void audio_cap_init();
void audio_get_value(float *data, uint32_t count, uint8_t *channel_seq, uint8_t channel_count);

#endif // AUDIO_CAPTURE