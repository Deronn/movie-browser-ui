#include "ImageWidget.h"

#include <string>

using namespace std;

// Constructor

ImageWidget::ImageWidget(graphics::Brush br, float x, float y,int kindof, float width, float height) : Widget(br, x, y, kindof), width(width), height(height) {
}

// Draws a basic rectangle

void ImageWidget::draw() {
    graphics::drawRect(x, y, width, height, br);
}

// Image is not interactive

void ImageWidget::update(float ms, graphics::MouseState& mouse) {
}

// Accessor

void ImageWidget::updateTexture(string texture) {
    br.texture = texture;
}