#include <gg.h>

static t_class *gg_scale_class;

typedef struct _gg_scale {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;
    float ratio;
} t_gg_scale;

void gg_scale_float(t_gg_scale *x, float _action_id) {
    x->input_action_id = (int)_action_id;
    outlet_float(x->outlet, x->action_id);
}

void *gg_scale_new(void) {
    t_gg_scale *x = (t_gg_scale *)pd_new(gg_scale_class);
    x->outlet = outlet_new(&x->x_obj, &s_pointer);

    x->ratio = 1;
    floatinlet_new(&x->x_obj, &x->ratio);

    x->action_id = actions.size();

    actions.push_back([x](){
        int action_id = x->input_action_id;
        float ratio = x->ratio;

        glPushMatrix();
        glScalef(ratio, ratio, ratio);

        if(action_id >= 0 && action_id < (int)actions.size())
            actions[action_id]();

        glPopMatrix();
    });

    return (void *)x;
}

void gg_scale_free(t_gg_scale *x) {
    outlet_free(x->outlet);
}

extern "C" {
    void gg_scale_setup(void) {
        gg_scale_class = class_new(
            gensym("gg_scale"),
            (t_newmethod)gg_scale_new,
            (t_method)gg_scale_free,
            sizeof(t_gg_scale),
            CLASS_DEFAULT, A_NULL
        );
        class_addfloat(gg_scale_class, gg_scale_float);
    }
}
