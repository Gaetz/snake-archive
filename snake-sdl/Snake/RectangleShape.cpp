#include "RectangleShape.h"

gfx::RectangleShape::RectangleShape() : Rectangle(), color_()
{

}

gfx::RectangleShape::RectangleShape(const SDL_Rect& rect, const SDL_Color& color) : Rectangle(rect), color_(color)
{

}

gfx::RectangleShape::~RectangleShape()
{
}

void gfx::RectangleShape::Render(Window& window)
{
	window.DrawRect(&rect_, color_.r, color_.g, color_.b, color_.a, true);
}

SDL_Color gfx::RectangleShape::GetColor()
{
	return color_;
}

void gfx::RectangleShape::SetColor(const SDL_Color& color)
{
	color_ = color;
}

void gfx::RectangleShape::SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	color_ = color;
}