#include <gg.h>

typedef struct _gg_scale {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float ratio;
} gg_scale;

static void init(gg_scale *self) {
    self->ratio = 1;
    floatinlet_new(&self->x_obj, &self->ratio);
}

static void action(gg_scale *self) {
    int action_id = self->input_action_id;
    float ratio = self->ratio;

    glPushMatrix();
    glScalef(ratio, ratio, ratio);

    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();

    glPopMatrix();
}

entity_register(gg_scale, init, action);
