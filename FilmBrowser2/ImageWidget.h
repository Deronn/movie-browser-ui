#pragma once

#include <string>

#include "Widget.h"

using namespace std;

// Image widget
// Contains a basic rectangle

class ImageWidget : public Widget {
private:
    float width;
    float height;

public:
    ImageWidget(graphics::Brush br, float x, float y,int kindof, float width, float height);

    virtual void draw();
    virtual void update(float ms, graphics::MouseState& mouse);

    void updateTexture(string texture);
};
