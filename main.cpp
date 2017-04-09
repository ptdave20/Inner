#include "game/InnerWindow.h"

int main() {
    InnerWindow game;
    try {
        game.eval("chai/main.chai");
        game.start();
    } catch (chaiscript::exception::eval_error ex) {
        std::cout << ex.pretty_print() << std::endl;
    }

    return 0;
}