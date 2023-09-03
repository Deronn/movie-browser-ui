#pragma once

#include <string>

#include "Widget.h"

using namespace std;


// Widget Button
// Contains text and a rectangle to shape the button

class ButtonWidget : public Widget {
private:
    string text;
    float size;
    float width;
    float height;
    string font;
    graphics::Brush rectangle_brush;
    bool hover;

    

public:
    ButtonWidget(graphics::Brush br[2], float x, float y,int kindof, string text, float size, float width, float height, string font);

    virtual void draw();
    virtual void update(float ms, graphics::MouseState& mouse);
    virtual bool contains(int x, int y);

    string getText();

    
    
};
