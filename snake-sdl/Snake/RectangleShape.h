#pragma once
#include <SDL.h>
#include "Window.h"
#include "Rectangle.h"

namespace gfx
{
	class RectangleShape : public utils::Rectangle
	{
	public:
		RectangleShape();
		RectangleShape(const SDL_Rect& rect, const SDL_Color& color);
		~RectangleShape();

		SDL_Color GetColor();
		void SetColor(const SDL_Color& color);
		void SetColor(const Uint8 r, const Uint8 g, Uint8 b, const Uint8 a);

		void Render(Window& window);

	private:
		SDL_Color color_;
	};
}