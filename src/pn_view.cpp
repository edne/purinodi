#include <purinodi.h>

static t_class *pn_view_class;

typedef struct _pn_view {
    t_object x_obj;
    GLFWwindow* window;
} t_pn_view;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
void pn_view_float(t_pn_view *self, float _action_id) {
    int action_id = (int)_action_id;
    int width, height, side, x0, y0;

    glfwMakeContextCurrent(self->window);

    glfwGetWindowSize(self->window, &width, &height);

    side = MAX(width, height);
    x0 = (width  - side) / 2;
    y0 = (height - side) / 2;
    glViewport(x0, y0, side, side);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();

    glfwSwapBuffers(self->window);
}

void *pn_view_new(void) {
    t_pn_view *self = (t_pn_view *)pd_new(pn_view_class);

    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "", NULL, NULL);
    if (!window) {
        glfwTerminate();
        post("Cannot create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // vsync

    self->window = window;
    return (void *)self;
}

void pn_view_free(t_pn_view *self) {
    (void) self;
}

extern "C" {
    void pn_view_setup(void) {
        pn_view_class = class_new(
            gensym("pn_view"),
            (t_newmethod)pn_view_new,
            (t_method)pn_view_free,
            sizeof(t_pn_view),
            CLASS_DEFAULT, A_NULL
        );
        class_addfloat(pn_view_class, pn_view_float);

        if (!glfwInit())
            post("Cannot init glfw");
    }
}
