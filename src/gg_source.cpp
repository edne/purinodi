#include <gg.h>

static t_class *gg_source_class;

typedef struct _gg_source {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
} t_gg_source;

void gg_source_bang(t_gg_source *x) {
    (void) x;
    outlet_float(x->outlet, x->action_id);
    post("gg_source: bang");
}

void *gg_source_new(void) {
    t_gg_source *x = (t_gg_source *)pd_new(gg_source_class);
    x->outlet = outlet_new(&x->x_obj, &s_pointer);

    x->action_id = actions.size();
    actions.push_back([](){post("gg_source: f");});

    return (void *)x;
}

void gg_source_free(t_gg_source *x) {
    outlet_free(x->outlet);
}

extern "C" {
    void gg_source_setup(void) {
        gg_source_class = class_new(
            gensym("gg_source"),
            (t_newmethod)gg_source_new,
            (t_method)gg_source_free,
            sizeof(t_gg_source),
            CLASS_DEFAULT, A_NULL
        );
        class_addbang(gg_source_class, gg_source_bang);
    }
}
