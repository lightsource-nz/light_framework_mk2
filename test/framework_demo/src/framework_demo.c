#include <light.h>

static void framework_demo_app_event(struct light_module *mod, uint8_t event);

Light_Application_Define(framework_demo, &light_framework, framework_demo_app_event);

void main()
{
        light_framework_init(this_app);
    
        __breakpoint();
}

static void framework_demo_app_event(struct light_module *mod, uint8_t event)
{
        switch (event) {
        case LF_EVENT_LOAD:
                light_info("demo app received LOAD event","");
                break;
        case LF_EVENT_UNLOAD:
                light_info("demo app received UNLOAD event","");
                break;
        }
}
