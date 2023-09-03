#include "Widget.h"

// Constructor

Widget::Widget(graphics::Brush br, float x, float y, int kindof) : br(br), x(x), y(y), kindof(kindof) {
}

// Destructor

Widget::~Widget() {
}

// isClicked returns true if an item is clickable (not clickable by default)

bool Widget::isClicked() {
    return false;
}

void Widget::setActive(bool a) {
    //m_active[1] = m_active[0];
    m_active = a;
       
    
    
}

void Widget::setHighlight(bool b)
{
   // highlighted[1] = highlighted[0];
    if (highlighted == b)
    {
        highlighted = false;
    }
    else {
        highlighted = b;
    }
}

int Widget::getKindof() {
    return kindof;
}
    // Returns true if an item contains coordinates (x,y) (only if an item is interactive)

bool Widget::contains(int x, int y) {
    return false;
}
