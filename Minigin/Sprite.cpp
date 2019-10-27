#include "MiniginPCH.h"
#include "Sprite.h"


mini::Sprite::Sprite(int width, int height, Texture2D* Texture, int x, int y, bool isLooping, float Speed, bool SheetIsVertical, int FrameCount, SDL_RendererFlip flip)
{
	this->width = width;
	this->height = height;
	this->isLooping = isLooping;
	this->sheetIsVertical = SheetIsVertical;
	this->Flip = flip;
	this->TimerFrame = 0;
	this->FrameSpeed = Speed;

	if (SheetIsVertical)
	{
		if (FrameCount < 0)
		{
			this->FrameCount = (int)std::floor(Texture->height() / (height - y));
		}

		this->Texture = Texture->GetCropedTexture(x, y, width, height * this->FrameCount);
	}
	else
	{
		if (FrameCount < 0)
		{
			this->FrameCount = (int)std::floor(Texture->width() / (width - x));
		}

		this->Texture = Texture->GetCropedTexture(x, y, width * this->FrameCount, height);
	}
}

mini::Sprite::~Sprite()
{
	delete Texture;
}
SDL_Rect mini::Sprite::GetFrameRect(int frame) const
{
	SDL_Rect src;

	if (frame == -1)
	{
		if (FrameIndex != -1)
			frame = FrameIndex;
		else
			frame = TimerFrame;
	}

	if (sheetIsVertical)
	{
		src.x = 0;
		src.y = height * frame;
	}
	else
	{
		src.x = width * frame;
		src.y = 0;
	}

	src.w = width;
	src.h = height;

	return src;
}
void mini::Sprite::AddInstance(int x, int y, int frame)
{
	Instance inst;
	inst.RelativeX = x;
	inst.Y = y;

	if(frame > 0)
		inst.FrameIndex = frame;

	Instances.push_back(inst);
}

void mini::Sprite::SetFrame(int frame)
{
	if (isLooping)
	{
		FrameIndex = frame % FrameCount;
	}
	else
	{
		FrameIndex = min(frame, FrameCount);
	}
}

void mini::Sprite::Reset()
{
	visible = false;
	Instances.clear();
}

void mini::Sprite::SetTimerFrame(int frame)
{
	if (isLooping)
	{
		TimerFrame = frame % FrameCount;
	}
	else
	{
		TimerFrame = min(frame, FrameCount);
	}
}



