#include <gg.h>

static t_class *gg_sink_class;

typedef struct _gg_sink {
    t_object x_obj;
} t_gg_sink;

void gg_sink_float(t_gg_sink *x, float _action_id) {
    int action_id = (int)_action_id;
    post("gg_sink: float %d", action_id);

    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();

    (void) x;
}

void *gg_sink_new(void) {
    t_gg_sink *x = (t_gg_sink *)pd_new(gg_sink_class);
    return (void *)x;
}

void gg_sink_free(t_gg_sink *x) {
    (void) x;
}

extern "C" {
    void gg_sink_setup(void) {
        gg_sink_class = class_new(
            gensym("gg_sink"),
            (t_newmethod)gg_sink_new,
            (t_method)gg_sink_free,
            sizeof(t_gg_sink),
            CLASS_DEFAULT, A_NULL
        );
        class_addfloat(gg_sink_class, gg_sink_float);
    }
}
