#include <gg.h>

typedef struct _gg_square {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float r;
} gg_square;

static void init(gg_square *x) {
    x->r = 0.5;
    floatinlet_new(&x->x_obj, &x->r);
}

static void action(gg_square *x) {
    float r = x->r;

    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);

    glVertex3f( r,  r, 0);
    glVertex3f( r, -r, 0);
    glVertex3f(-r, -r, 0);
    glVertex3f(-r,  r, 0);

    glEnd();
}

entity_register(gg_square, init, action);
