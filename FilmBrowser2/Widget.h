#pragma once

#include <iostream>
#include <random>
#include <string>

#include <sgg/graphics.h>



// Base class for all widgets

class Widget {
protected:
    graphics::Brush br;
    float x, y;

    bool highlighted = false;
    bool m_active = false;
    
    int kindof; // false years, true genre
public:
    Widget(graphics::Brush br, float x, float y, int kindof);
    virtual ~Widget();

    virtual void draw() = 0;
    virtual void update(float ms, graphics::MouseState& mouse) = 0;
    virtual bool isClicked();
    virtual bool contains(int x, int y);

    void setActive(bool a);
    void setHighlight(bool b);
    int getKindof();

   
};
