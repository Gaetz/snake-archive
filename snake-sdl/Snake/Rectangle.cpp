#include "Rectangle.h"

using utils::Vector2i16;
using utils::Vector2i16;

utils::Rectangle::Rectangle()
{
	/*rect_.x = 0;
	rect_.y = 0;
	rect_.w = 1;
	rect_.h = 1;
	SetCenterPosition(CenterPosition::TOP_LEFT);*/
}

utils::Rectangle::Rectangle(Vector2i16 position, Vector2i16 size)
{
	rect_.x = position.x;
	rect_.y = position.y;
	rect_.w = size.x;
	rect_.h = size.y;
	SetCenterPosition(CenterPosition::TOP_LEFT);
}

utils::Rectangle::Rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h)
{
	rect_.x = x;
	rect_.y = y;
	rect_.w = w;
	rect_.h = h;
	SetCenterPosition(CenterPosition::TOP_LEFT);
}

utils::Rectangle::Rectangle(const SDL_Rect & rect)
{
	rect_.x = rect.x;
	rect_.y = rect.y;
	rect_.w = rect.w;
	rect_.h = rect.h;
	SetCenterPosition(CenterPosition::TOP_LEFT);
}

utils::Rectangle::~Rectangle()
{

}

Sint16 utils::Rectangle::GetX()
{
	return rect_.x + center_.x;
}

Sint16 utils::Rectangle::GetY()
{
	return rect_.y + center_.y;
}

Sint16 utils::Rectangle::GetOx()
{
	return center_.x;
}

Sint16 utils::Rectangle::GetOy()
{
	return center_.y;
}

Sint16 utils::Rectangle::GetWidth()
{
	return rect_.w;
}

Sint16 utils::Rectangle::GetHeight()
{
	return rect_.h;
}

void utils::Rectangle::SetX(Sint16 x)
{
	rect_.x = x - center_.x;
}

void utils::Rectangle::SetY(Sint16 y)
{
	rect_.y = y - center_.y;
}

void utils::Rectangle::SetOx(Sint16 ox)
{
	// Reset old center
	rect_.x += center_.x;
	// Apply new center
	center_.x = ox;
	rect_.x -= center_.x;
}

void utils::Rectangle::SetOy(Sint16 oy)
{
	// Reset old center
	rect_.y += center_.y;
	// Apply new center
	center_.y = oy;
	rect_.y -= center_.y;
}

void utils::Rectangle::SetWidth(Sint16 width)
{
	rect_.w = width;
	SetCenterPosition(centerPosition_);
}

void utils::Rectangle::SetHeight(Sint16 height)
{
	rect_.h = height;
	SetCenterPosition(centerPosition_);
}

utils::Vector2i16 utils::Rectangle::GetPosition()
{
	return Vector2i16(rect_.x + center_.x, rect_.y + center_.y);
}

void utils::Rectangle::SetPosition(Vector2i16 position)
{
	rect_.x = position.x - center_.x;
	rect_.y = position.y - center_.y;
}

Vector2i16 utils::Rectangle::GetCenter()
{
	return center_;
}

void utils::Rectangle::SetCenter(Vector2i16 center)
{
	// Reset old center
	rect_.x += center_.x;
	rect_.y += center_.y;
	// Apply new center
	center_ = center;
	rect_.x -= center.x;
	rect_.y -= center.y;
}


utils::CenterPosition utils::Rectangle::GetCenterPosition()
{
	return centerPosition_;
}

void utils::Rectangle::SetCenterPosition(CenterPosition center)
{
	centerPosition_ = center;
	switch (center)
	{
	case TOP_LEFT:
		SetCenter(Vector2i16(0, 0));
		break;
	case BOTTOM_LEFT:
		SetCenter(Vector2i16(0, rect_.h));
		break;
	case TOP_RIGHT:
		SetCenter(Vector2i16(rect_.w, 0));
		break;
	case BOTTOM_RIGHT:
		SetCenter(Vector2i16(rect_.w, rect_.h));
		break;
	case CENTER:
		SetCenter(Vector2i16(rect_.w / 2, rect_.h / 2));
		break;
	case BOTTOM:
		SetCenter(Vector2i16(rect_.w / 2, rect_.h));
		break;
	case TOP:
		SetCenter(Vector2i16(rect_.w / 2, 0));
		break;
	case LEFT:
		SetCenter(Vector2i16(0, rect_.h / 2));
		break;
	case RIGHT:
		SetCenter(Vector2i16(rect_.w, rect_.h / 2));
		break;
	default:
		break;
	}
}

SDL_Rect utils::Rectangle::GetRect()
{
	return rect_;
}

void utils::Rectangle::SetRect(const SDL_Rect& rect)
{
	rect_.x = rect.x - center_.x;
	rect_.y = rect.y - center_.y;
	rect_.w = rect.w;
	rect_.h = rect.h;
}