#include <iostream>
#include "includes/Window.h"

int main() {
    Window window;
    window.openConfig("json/main.json");
    window.createWindow();
    window.run();

    return 0;
}