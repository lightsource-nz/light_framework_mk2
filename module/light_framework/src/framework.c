#include <light.h>

#include "framework_internal.h"

#define LTYPE_LIGHT_MODULE_ID "light.module"
#define LTYPE_LIGHT_APPLICATION_ID "light.application"

#define MODULE_ID_LIGHT_FRAMEWORK "mod_light_framework"

const struct light_module *static_modules[LF_STATIC_MODULES_MAX];
extern int __light_modules_start, __light_modules_end;

static void _static_module_load(const struct light_module *module)
{
        
}
static void _load_static_modules()
{
        uint8_t load_count = 0;
        const struct light_module *next_module = (const struct light_module *) &__light_modules_start;
        while (next_module < (const struct light_module *) &__light_modules_end)
        {
                _static_module_load(next_module);
                load_count++;
                next_module++;
        }
        light_debug("preloaded %d device classes", load_count);

}
static void _module_release(struct light_object *obj)
{
        light_free(to_module(obj));
}
static void _application_release(struct light_object *obj)
{
        light_free(to_application(obj));
}
struct lobj_type ltype_light_module = {
        .id = LTYPE_LIGHT_MODULE_ID,
        .release = _module_release
};
struct lobj_type ltype_light_application = {
        .id = LTYPE_LIGHT_APPLICATION_ID,
        .release = _application_release
};

static void _event_load(struct light_module *module)
{
        
}
static void _event_unload(struct light_module *module)
{
        
}
static void _module_event(struct light_module *module, uint8_t event)
{
        switch(event) {
        case LF_EVENT_LOAD:
                _event_load(module);
                break;
        case LF_EVENT_UNLOAD:
                _event_unload(module);
                break;
        }
}
Light_Module_Define(light_framework,NULL,_module_event);

static uint8_t framework_loading = 0;
static struct light_application *root_application = NULL;

void light_framework_init()
{
        light_info("Loading Light Framework runtime v%s...", LF_VERSION_STR);
        light_info("LIGHT_RUN_MODE=%s, LIGHT_MAX_LOG_LEVEL=%s",
                                        light_run_mode_to_string(LIGHT_RUN_MODE),
                                        light_log_level_to_string(LIGHT_MAX_LOG_LEVEL));
        framework_loading = 1;
        root_application = this_app;
        light_framework_load_application(root_application);
}

void light_framework_load_application(struct light_application *app)
{
        if(!framework_loading)
                light_fatal("attempted to load an application before calling light_framework_init()","");
        // TODO verify at build-time that we support the runtime version requested by this app
        light_info("Loading application '%s': app version %s, framework version %s",
                                        light_application_get_name(app),"NULL","NULL");
        
}
