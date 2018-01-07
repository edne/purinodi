#include <gg.h>

static t_class *gg_view_class;

typedef struct _gg_view {
    t_object x_obj;
    GLFWwindow* window;
} t_gg_view;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
void gg_view_float(t_gg_view *x, float _action_id) {
    int action_id = (int)_action_id;
    int width, height, side, x0, y0;

    glfwMakeContextCurrent(x->window);

    glfwGetWindowSize(x->window, &width, &height);

    side = MAX(width, height);
    x0 = (width  - side) / 2;
    y0 = (height - side) / 2;
    glViewport(x0, y0, side, side);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();

    glfwSwapBuffers(x->window);
}

void *gg_view_new(void) {
    t_gg_view *x = (t_gg_view *)pd_new(gg_view_class);

    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "", NULL, NULL);
    if (!window) {
        glfwTerminate();
        post("Cannot create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // vsync

    x->window = window;
    return (void *)x;
}

void gg_view_free(t_gg_view *x) {
    (void) x;
}

extern "C" {
    void gg_view_setup(void) {
        gg_view_class = class_new(
            gensym("gg_view"),
            (t_newmethod)gg_view_new,
            (t_method)gg_view_free,
            sizeof(t_gg_view),
            CLASS_DEFAULT, A_NULL
        );
        class_addfloat(gg_view_class, gg_view_float);

        if (!glfwInit())
            post("Cannot init glfw");
    }
}
