#pragma once
#include <SDL.h>

namespace mini
{
	enum Channels
	{
		R = 2 << 0,
		G = 2 << 1,
		B = 2 << 2,
		A = 2 << 3
	};


	class Sprite;
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D();
		explicit Texture2D(SDL_Texture* texture);
		Texture2D(SDL_Surface* surface, bool GenerateTextureImmediately = true);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		void Update();
		void SetChannels(unsigned int channels);

		void Add		(Texture2D* rhs, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX);
		void Substract	(Texture2D* rhs, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX);
		void Overlay	(Texture2D* rhs, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX);
		void AddMask	(Texture2D* mask, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX, bool overwrite = true);

		void Add		(Sprite* rhs, int x = 0, int y = 0);
		void Substract	(Sprite* rhs, int x = 0, int y = 0);
		void Overlay	(Sprite* rhs, int x = 0, int y = 0);
		void AddMask	(Sprite* mask, int x = 0, int y = 0, bool overwrite = true);

		void AddMask	(std::string mask, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX, bool overwrite = true);
		void AddMask	(SDL_Surface* mask, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX, bool overwrite = true);
		void Colorize	(SDL_Color* color, int x = 0, int y = 0, int width = INT_MAX, int height = INT_MAX);
		void Scale		(int width, int height);
		void Crop		(int x, int y, int width, int height);

		Texture2D* GetCropedTexture(int x, int y, int width, int height);
		void SetCropedTexture(Texture2D * rhs,int x, int y, int width, int height);
		SDL_PixelFormat* GetFormat() const;
		

		void ConvertToRGB();
		SDL_Rect GetRect() const;
		int width() const;
		int height() const;
		unsigned int GetChannels() const;


	private:
		SDL_Texture* Texture = nullptr;
		SDL_Surface* Image = nullptr;
		
		bool NeedsUpdate = true;

		unsigned int Channels = 0;
		SDL_Rect rect;
	};
}
