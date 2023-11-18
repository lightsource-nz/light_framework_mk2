#ifndef _LIGHT_PLATFORM_H
#define _LIGHT_PLATFORM_H

#include <light.h>

#include <stdint.h>

// TODO implement version fields properly
#define LF_PLATFORM_VERSION_STR                  "0.1.0"
#define LF_PLATFORM_INFO_STR                     "Light Platform v" LF_PLATFORM_VERSION_STR ", " LIGHT_BUILD_STRING

Light_Module_Declare(light_platform)

struct lp_timer {
        uint8_t id;
        uint8_t state;
        uint32_t duration_ms;
        uint32_t target_ms;
        void (*timeout)(void *);
};

extern void light_platform_init();
extern struct lp_timer *light_platform_timer_new();
extern uint8_t light_platform_timer_set_ms(struct lp_timer *timer, uint32_t time_ms, bool start);
extern void light_platform_timer_run(struct lp_timer *timer);
extern void light_platform_timer_stop(struct lp_timer *timer);
extern uint32_t light_platform_timer_get_remaining_ms(struct lp_timer *timer);
static inline bool light_platform_timer_get_expired(struct lp_timer *timer)
{
    return light_platform_timer_get_remaining_ms(timer) == 0;
}

extern uint32_t light_platform_get_system_time_ms();
extern void light_platform_sleep_ms(uint32_t period);   

#endif
