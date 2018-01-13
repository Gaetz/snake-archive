#include "Window.h"

Window::Window(char* windowName, int width, int height) {
	window_ = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window_ == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
		if (renderer_ == nullptr)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

Window::~Window() {
	SDL_FreeSurface(screenSurface_);
	screenSurface_ = nullptr;
	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;
	SDL_DestroyWindow(window_);
	window_ = nullptr;
}

void Window::Update() {

}

void Window::BeginDraw() {
	//Clear screen
	SDL_RenderClear(renderer_);
}

void Window::DrawTexture(SDL_Texture* texture) {
	//Render texture to screen
	if (SDL_RenderCopy(renderer_, texture, NULL, NULL)) printf("SDL could not draw texture. SDL_Error: %s\n", SDL_GetError());
}

void Window::DrawRect(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool isFilled) {
	// Save former color
	Uint8 formerR = 0; Uint8 formerG = 0; Uint8 formerB = 0; Uint8 formerA = 0;
	if (SDL_GetRenderDrawColor(renderer_, &formerR, &formerG, &formerB, &formerA) < 0) printf("SDL could not draw rect. SDL_Error: %s\n", SDL_GetError());
	// Draw
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);
	if (isFilled)
		SDL_RenderFillRect(renderer_, rect);
	else
		SDL_RenderDrawRect(renderer_, rect);
	// Reload former color
	SDL_SetRenderDrawColor(renderer_, formerR, formerG, formerB, formerA);
}

void Window::EndDraw() {
	//Update screen
	SDL_RenderPresent(renderer_);
}