#include <purinodi.h>

typedef struct _pn_polygon {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;

    float r, n;
} pn_polygon;

static void init(pn_polygon *self) {
    self->r = 0.5;
    self->n = 3;
    floatinlet_new(&self->x_obj, &self->r);
    floatinlet_new(&self->x_obj, &self->n);
}

static void action(pn_polygon *self) {
    float r = self->r;
    float n = self->n;
    float theta, x, y;
    int i;

    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);

    for(i=0; i<n; i++) {
        theta = M_PI/2 + i * 2*M_PI / n;
        x = r * cos(theta);
        y = r * sin(theta);
        glVertex3f(x, y, 0);
    }

    glEnd();
}

entity_register(pn_polygon, init, action);
