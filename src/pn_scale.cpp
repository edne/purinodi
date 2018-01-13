#include <purinodi.h>

typedef struct _pn_scale {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float ratio;
} pn_scale;

static void init(pn_scale *self) {
    self->ratio = 1;
    floatinlet_new(&self->x_obj, &self->ratio);
}

static void action(pn_scale *self) {
    int action_id = self->input_action_id;
    float ratio = self->ratio;

    glPushMatrix();
    glScalef(ratio, ratio, ratio);

    call_action(action_id);

    glPopMatrix();
}

entity_register(pn_scale, init, action);
