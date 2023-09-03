#include <iostream>
#include <random>
#include <string>

#include <sgg\graphics.h>

#include "MovieBrowser.h"




void update(float ms) {
    MovieBrowser* browser = (MovieBrowser*)graphics::getUserData();
    browser->update(ms);
}

void draw() {
    MovieBrowser* browser = (MovieBrowser*)graphics::getUserData();
    browser->draw();
}

int main() {
    int window_width = 1024;
    int window_height = 768;
    string title = "MovieBrowser";

    MovieBrowser browser(title, window_width, window_height);

    browser.init();

    browser.preloadAssets();

    browser.load();

    browser.setupWidgets();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    browser.mainLoop();

    return 0;
}
