#pragma once

#include "Widget.h"

#include <string>

using namespace std;

// Text widget
// Contains text

class TextWidget : public Widget {
protected:
    string text;
    float size;
    string font;

public:
    TextWidget(graphics::Brush br, float x, float y, int kindof, string text, float size, string font);

    virtual void draw();
    virtual void update(float ms, graphics::MouseState& mouse);
    void setText(string text);
};
