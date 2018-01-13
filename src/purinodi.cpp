#include <purinodi.h>
#include <functional>
#include <vector>

using namespace std;


vector<function<void(void)>> actions;

int add_action(void *self, void (*action)(void *)) {
    int action_id = actions.size();
    actions.push_back([=](){action(self);});
    return action_id;
}

void call_action(int action_id) {
    if(action_id >= 0 && action_id < (int)actions.size())
        actions[action_id]();
}
