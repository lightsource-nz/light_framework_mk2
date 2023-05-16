#ifndef _LIGHT_FRAMEWORK_H
#define _LIGHT_FRAMEWORK_H

#include <light_common.h>
#include <light_object.h>

#include <stdint.h>

// TODO implement version fields properly
#define LF_VERSION_STR                  "0.1.0"

#define LF_EVENT_LOAD                   0
#define LF_EVENT_UNLOAD                 1

#define LF_STATIC_MODULES_MAX           16

#define LF_MODULE_DEPS_MAX              8

struct light_module {
        struct light_object header;
        uint8_t module_deps_count;
        struct light_module *module_deps[LF_MODULE_DEPS_MAX];
        void (*event)(struct light_module *, uint8_t);
};

struct light_application {
        struct light_object header;
        struct light_module module;
};

#define Light_Module(_name, _deps, _event) \
{ \
        .header = Light_Object_RO(_name, NULL, &ltype_light_module), \
        .module_deps = _deps, \
        .event = _event \
}
#define Light_Module_Static(_name, _deps, _event) \
{ \
        .header = Light_Object_Static_RO(_name, NULL, &ltype_light_module), \
        .module_deps = { _deps, NULL }, \
        .event = _event \
}

#define __static_module __attribute__ ((section(".light.modules")))

#define Light_Module_Declare(name) \
        extern struct light_module name;

#define Light_Module_Define(name, deps, event) \
        struct light_module __in_flash(".descriptors") name = Light_Module_Static(#name, deps, event); \
        static const struct light_module __static_module *this_module = &name;

#define Light_Application(_name, _deps, _event) \
{ \
        .header = Light_Object_Static_RO(_name, NULL, &ltype_light_application), \
        .module = Light_Module_Static("mod_" _name, _deps, _event) \
}

#define Light_Application_Define(name, deps, event) \
        static struct light_application __this_app = Light_Application(#name, (deps), event); \
        static struct light_module __static_module *this_module = &__this_app.module; \
        struct light_module *mod_ ## name = &__this_app.module; \
        struct light_application *this_app = &__this_app;

#define to_module(ptr) container_of(ptr, struct light_module, header)
#define to_application(ptr) container_of(ptr, struct light_application, header)

Light_Module_Declare(light_framework)

// at least for now this symbol is a single global value determined at build-time
extern struct light_application *this_app;

extern struct lobj_type ltype_light_module;
extern struct lobj_type ltype_light_application;

// framework entry point, enumerates module dependency graph and loads required modules
extern void light_framework_init();
extern void light_framework_load_application(struct light_application *app);
extern void light_framework_load_module(struct light_module *mod);
extern struct light_application *light_framework_get_root_application();

static inline char *light_application_get_name(struct light_application *app)
{
        return app->header.id;
}
static inline struct light_module *light_application_get_main_module(struct light_application *app)
{
        return &app->module;
}
static inline char *light_module_get_name(struct light_module *mod)
{
        return mod->header.id;
}

#define light_module_send_event(module, _event) \
        light_debug("sending event '%s' to module '%s'", #_event, light_module_get_name(module)); \
        module->event(module, _event);

#endif