#include <m_pd.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

using namespace std;

extern vector<function<void(void)>> actions;

#define entity_register(name, init, action) extern "C" {\
    static t_class *name##_class;\
\
    void name##_float(name *self, float _action_id) {\
        self->input_action_id = (int)_action_id;\
        outlet_float(self->outlet, self->action_id);\
    }\
\
    void name##_bang(name *self) {\
        outlet_float(self->outlet, self->action_id);\
    }\
\
    void name##_free(name *self) {\
        outlet_free(self->outlet);\
    }\
\
    void *name##_new(void) {\
        name *self = (name *)pd_new(name##_class);\
        self->outlet = outlet_new(&self->x_obj, &s_pointer);\
\
        init(self);\
\
        self->action_id = actions.size();\
        actions.push_back([self](){action(self);});\
        self->input_action_id = -1;\
\
        return (void *)self;\
    }\
\
    void name##_setup(void) {\
        name##_class = class_new(\
            gensym(#name),\
            (t_newmethod) name##_new,\
            (t_method) name##_free,\
            sizeof(name),\
            CLASS_DEFAULT, A_NULL\
        );\
        class_addbang(name##_class, name##_bang);\
        class_addfloat(name##_class, name##_float);\
    }\
}
