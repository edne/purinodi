#include <gg.h>

typedef struct _gg_scale {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float ratio;
} gg_scale;

static void init(gg_scale *x) {
    x->ratio = 1;
    floatinlet_new(&x->x_obj, &x->ratio);
}

static void action(gg_scale *x) {
    int action_id = x->input_action_id;
    float ratio = x->ratio;

    glPushMatrix();
    glScalef(ratio, ratio, ratio);

    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();

    glPopMatrix();
}

entity_register(gg_scale, init, action);
