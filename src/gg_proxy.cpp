#include <gg.h>

static t_class *gg_proxy_class;

typedef struct _gg_proxy {
    t_object x_obj;
    t_outlet *outlet;
    int action_id;
    int input_action_id;
} t_gg_proxy;

void gg_proxy_float(t_gg_proxy *x, float _action_id) {
    x->input_action_id = (int)_action_id;

    outlet_float(x->outlet, x->action_id);
}

void *gg_proxy_new(void) {
    t_gg_proxy *x = (t_gg_proxy *)pd_new(gg_proxy_class);
    x->outlet = outlet_new(&x->x_obj, &s_pointer);

    x->action_id = actions.size();

    actions.push_back([x](){
        int action_id = x->input_action_id;
        // post("Now size is %d", actions.size());
        post("gg_proxy: f");
        if(action_id >= 0 && action_id < (int)actions.size())
            actions[action_id]();
    });

    return (void *)x;
}

void gg_proxy_free(t_gg_proxy *x) {
    outlet_free(x->outlet);
}

extern "C" {
    void gg_proxy_setup(void) {
        gg_proxy_class = class_new(
            gensym("gg_proxy"),
            (t_newmethod)gg_proxy_new,
            (t_method)gg_proxy_free,
            sizeof(t_gg_proxy),
            CLASS_DEFAULT, A_NULL
        );
        class_addfloat(gg_proxy_class, gg_proxy_float);
    }
}
