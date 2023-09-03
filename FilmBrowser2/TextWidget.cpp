#include "TextWidget.h"

// Constructor

TextWidget::TextWidget(graphics::Brush br, float x, float y,int kindof, string text, float size, string font) : Widget(br, x, y, kindof), text(text), size(size), font(font) {
}

// Renders simple text

void TextWidget::draw() {
    graphics::setFont(font);
    graphics::drawText(x, y, size, text, br);
}

// Text is not interactive

void TextWidget::update(float ms, graphics::MouseState& mouse) {
    // nothing
}

// Accessor

void TextWidget::setText(string text) {
    this->text = text;
}
