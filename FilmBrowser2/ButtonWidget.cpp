#include <sgg/graphics.h>

#include "ButtonWidget.h"
#include "MovieBrowser.h"

// Constructor

ButtonWidget::ButtonWidget(graphics::Brush br[2], float x, float y,int kindof, string text, float size, float width, float height, string font) : Widget(br[0], x, y, kindof), text(text), size(size), width(width), height(height), font(font), hover(false) {
    rectangle_brush = br[1];
}

// Draws a rectangle and the text in it
// The size changes to indicate that the button is clickable when the mouse hovers over it

void ButtonWidget::draw() {

   
    
    graphics::drawRect(x + width / 2 - 1, y - 1, width, height, rectangle_brush);

    graphics::setFont(font);

    if (hover) {
        graphics::drawText(x, y, size + 0.3f, text, br);
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.3f;
    } else {
        graphics::drawText(x, y, size, text, br);
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
    }

    if (highlighted) {
        rectangle_brush.fill_color[0] = 0.2f;
        rectangle_brush.fill_color[1] = 0.8f;
        rectangle_brush.fill_color[2] = 0.3f;
    } else {
        rectangle_brush.fill_color[0] = 1.0f;
        rectangle_brush.fill_color[1] = 1.0f;
        rectangle_brush.fill_color[2] = 1.0f;
    }
}

// Displays the button on the screen
// If the button is clicked, the clickEvent (from the MovieBrowser class) is called to execute the event

void ButtonWidget::update(float ms, graphics::MouseState& mouse) {
    hover = contains(mouse.cur_pos_x, mouse.cur_pos_y);
    bool clicked = hover && mouse.button_left_pressed;

    if (clicked) {
        MovieBrowser* browser = (MovieBrowser*)graphics::getUserData();
        browser->clickEvent(this);
    }
}

// Checks if the button is clicked

bool ButtonWidget::contains(int mx, int my) {
    if (mx >= x + width / 2 - 1 - width / 2 && mx <= x + width / 2 - 1 + width / 2 && my >= y - 1 - height / 2 && my <= y - 1 + height / 2) {
        return true;
    } else {
        return false;
    }
}

// Accessor for the text

string ButtonWidget::getText() {
    return text;
}
