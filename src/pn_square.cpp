#include <purinodi.h>

typedef struct _pn_square {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float r;
} pn_square;

static void init(pn_square *self) {
    self->r = 0.5;
    floatinlet_new(&self->x_obj, &self->r);
}

static void action(pn_square *self) {
    float r = self->r;

    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);

    glVertex3f( r,  r, 0);
    glVertex3f( r, -r, 0);
    glVertex3f(-r, -r, 0);
    glVertex3f(-r,  r, 0);

    glEnd();
}

entity_register(pn_square, init, action);
