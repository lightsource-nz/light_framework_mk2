#include <light.h>

#include "framework_internal.h"

#define LTYPE_LIGHT_MODULE_ID "light.module"
#define LTYPE_LIGHT_APPLICATION_ID "light.application"

#define MODULE_ID_LIGHT_FRAMEWORK "mod_light_framework"

extern int __light_modules_start, __light_modules_end;

static struct light_module **static_modules;
static uint64_t static_module_count;

static uint8_t available_module_count;
static const struct light_module *available_modules[LF_STATIC_MODULES_MAX];

static void _find_static_modules()
{
        static_modules = (struct light_module **) &__light_modules_start;
        static_module_count = (((uint64_t)&__light_modules_end) - ((uint64_t)&__light_modules_start)) / sizeof(void *);
        light_debug("located %d static modules", static_module_count);
}
/*
        uint8_t load_count = 0;
        const struct light_module *next_module = (const struct light_module *) &__light_modules_start;
        while (next_module < (const struct light_module *) &__light_modules_end)
        {
                available_modules[load_count++] = next_module++;
        }
        available_module_count = load_count;
        light_debug("preloaded %d static modules", load_count);

} */
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

static void _event_load(const struct light_module *module)
{
        
}
static void _event_unload(const struct light_module *module)
{
        
}
static void _module_event(const struct light_module *module, uint8_t event)
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
Light_Module_Define(light_framework,_module_event,);

// framework internal state variables
static uint8_t framework_loading = 0;
static struct light_application *root_application = NULL;
static uint8_t mods_loading_count = 0;
static uint8_t mods_active_count = 0;
static struct light_module *mods_loading[LF_STATIC_MODULES_MAX];
static struct light_module *mods_active[LF_STATIC_MODULES_MAX];

void light_framework_init()
{
        light_common_init();
        light_info("Loading Light Framework runtime...", "");
        light_info("%s", LF_INFO_STR);

        light_object_setup();
        framework_loading = 1;
        _find_static_modules();

        root_application = this_app;
        light_framework_load_application(root_application);
}

void light_framework_load_application(struct light_application *app)
{
        if(!framework_loading)
                light_fatal("attempted to load an application before calling light_framework_init()","");
        // TODO verify at build-time that we support the runtime version requested by this app
        light_info("loading application '%s': app version %s, framework version %s",
                                        light_application_get_name(app),"NULL","NULL");
        light_framework_load_module(light_application_get_main_module(app));
        light_info("application '%s' loaded successfully", light_application_get_name(app));
}
// TODO overhaul arraylist API to make it suck less
void light_framework_load_module(const struct light_module *mod)
{
        light_debug("begin loading module %s", light_module_get_name(mod));
        light_arraylist_append(&mods_loading, &mods_loading_count, mod);

        // make sure all dependency modules are loaded before activating
        for(uint8_t i = 0; mod->module_deps[i] != NULL; i++) {
                if(light_arraylist_indexof(&mods_loading, mods_loading_count, mod->module_deps[i]) == -1) {
                        light_framework_load_module(mod->module_deps[i]);
                }
        }
        // send LOAD event; module is activated once it returns
        light_module_send_event(mod, LF_EVENT_LOAD);
        light_arraylist_append(&mods_active, &mods_active_count, mod);
        light_debug("module %s loaded successfully", light_module_get_name(mod));
}
struct light_application *light_framework_get_root_application()
{
        return root_application;
}
