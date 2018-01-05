#include <m_pd.h>
static t_class *gg_foo_class;


typedef struct _gg_foo {
    t_object x_obj;
} t_gg_foo;


void *gg_foo_new(void) {
    t_gg_foo *x = (t_gg_foo *)pd_new(gg_foo_class);
    return (void *)x;
}


void gg_foo_free(t_gg_foo *x) {
    (void) x;
}


extern "C" {
    void gg_foo_setup(void) {
        gg_foo_class = class_new(
            gensym("gg_foo"),
            (t_newmethod)gg_foo_new,
            (t_method)gg_foo_free,
            sizeof(t_gg_foo),
            CLASS_DEFAULT, A_NULL
        );
    }
}
