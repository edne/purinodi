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
    void name##_float(name *x, float _action_id) {\
        x->input_action_id = (int)_action_id;\
        outlet_float(x->outlet, x->action_id);\
    }\
\
    void name##_bang(name *x) {\
        outlet_float(x->outlet, x->action_id);\
    }\
\
    void name##_free(name *x) {\
        outlet_free(x->outlet);\
    }\
\
    void *name##_new(void) {\
        name *x = (name *)pd_new(name##_class);\
        x->outlet = outlet_new(&x->x_obj, &s_pointer);\
\
        init(x);\
\
        x->action_id = actions.size();\
        actions.push_back([x](){action(x);});\
        x->input_action_id = -1;\
\
        return (void *)x;\
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
