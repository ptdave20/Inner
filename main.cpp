#include "game/InnerWindow.h"

int main() {
    InnerWindow game;
    game.eval("chai/main.chai");
    game.start();
    return 0;
}