#pragma once
#include <SDL.h>
#include "Vector2.hpp"

using utils::Vector2i;
using utils::Vector2u;

namespace utils
{
	enum CenterPosition
	{
		TOP_LEFT,
		BOTTOM_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT,
		CENTER,
		BOTTOM,
		TOP,
		LEFT,
		RIGHT
	};

	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(Vector2i16 position, Vector2i16 size);
		Rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h);
		Rectangle(const SDL_Rect& rect);
		~Rectangle();

		Sint16 GetX();
		Sint16 GetY();
		Sint16 GetOx();
		Sint16 GetOy();
		Sint16 GetWidth();
		Sint16 GetHeight();
		void SetX(Sint16 x);
		void SetY(Sint16 y);
		void SetOx(Sint16 ox);
		void SetOy(Sint16 oy);
		void SetWidth(Sint16 width);
		void SetHeight(Sint16 height);

		Vector2i16 GetPosition();
		void SetPosition(Vector2i16 position);

		SDL_Rect GetRect();
		void SetRect(const SDL_Rect& rect);

		Vector2i16 GetCenter();
		void SetCenter(Vector2i16 center);

		CenterPosition GetCenterPosition();
		void SetCenterPosition(CenterPosition center);

	protected:
		SDL_Rect rect_;
		Vector2i16 position_;
		Vector2i16 center_;
		CenterPosition centerPosition_;
	};
}