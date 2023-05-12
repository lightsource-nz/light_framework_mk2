#ifndef _LIGHT_FRAMEWORK_H
#define _LIGHT_FRAMEWORK_H

#include <light_util.h>
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
struct light_module_state {
        const struct light_module *desc;
        uint8_t state;
};

struct light_application {
        struct light_object header;
        struct light_module module;
};
struct light_application_state {
        const struct light_application *desc;
        uint8_t state;
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
        .module_deps = _deps, \
        .event = _event \
}

#define Light_Module_Declare(name) \
        extern struct light_module *name;

#define Light_Module_Define(name, deps, event) \
        static struct light_module __this_module = Light_Module_Static(#name, deps, event); \
        static struct light_module *this_module = &__this_module; \
        struct light_module *name = &__this_module;

#define Light_Application(_name, _deps, _event) \
{ \
        .header = Light_Object_Static_RO(_name, NULL, &ltype_light_application), \
        .module = Light_Module_Static("mod_" _name, _deps, _event) \
}

#define Light_Application_Define(name, deps, event) \
        static struct light_application __this_app = Light_Application(#name, deps, event); \
        static struct light_module *this_module = &__this_app.module; \
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

static inline char *light_application_get_name(struct light_application *app)
{
        return app->header.id;
}

#endif