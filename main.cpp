#include "includes/Inner.h"

int main() {
    sel::State state{true};
    Window::Register(state);
    state.Load("lua/main.lua");

    return 0;
}