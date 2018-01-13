#pragma once
#include <SDL.h>
#include <stdio.h>

class Window {
public:
	Window(char* windowName, int width, int height);
	~Window();

	/// Game window update
	void Update();

	/// Game window erase former image
	void BeginDraw();

	/** Game window draw texture */
	void DrawTexture(SDL_Texture* texture);

	/** 
	* Game window draw colored rect
	* \param isFilled: fills rectangle if true.
	*/
	void DrawRect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool isFilled);

	/// Game window trigger draw
	void EndDraw();

private:
	/// The window we'll be rendering to
	SDL_Window* window_ = nullptr;

	/// The surface contained by the window
	SDL_Surface* screenSurface_ = nullptr;

	/** Window renderer */
	SDL_Renderer* renderer_ = nullptr;
};