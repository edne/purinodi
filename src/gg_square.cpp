#include <gg.h>

static t_class *gg_square_class;

typedef struct _gg_square {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    float r;
} t_gg_square;

void gg_square_bang(t_gg_square *x) {
    (void) x;
    outlet_float(x->outlet, x->action_id);
}

void *gg_square_new(void) {
    t_gg_square *x = (t_gg_square *)pd_new(gg_square_class);
    x->outlet = outlet_new(&x->x_obj, &s_pointer);

    x->r = 0.5;
    floatinlet_new(&x->x_obj, &x->r);

    x->action_id = actions.size();
    actions.push_back([x](){
        float r = x->r;

        glColor3f(1, 1, 1);

        glBegin(GL_LINE_LOOP);

        glVertex3f( r,  r, 0);
        glVertex3f( r, -r, 0);
        glVertex3f(-r, -r, 0);
        glVertex3f(-r,  r, 0);

        glEnd();
    });

    return (void *)x;
}

void gg_square_free(t_gg_square *x) {
    outlet_free(x->outlet);
}

extern "C" {
    void gg_square_setup(void) {
        gg_square_class = class_new(
            gensym("gg_square"),
            (t_newmethod)gg_square_new,
            (t_method)gg_square_free,
            sizeof(t_gg_square),
            CLASS_DEFAULT, A_NULL
        );
        class_addbang(gg_square_class, gg_square_bang);
    }
}
