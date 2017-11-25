#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

public:
	float current_frame;

public:
	Animation() : frames(), speed(0.0f), current_frame(0.0f)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	SDL_Rect& GetCurrentInverseFrame()
	{
		current_frame -= speed;
		if (current_frame <= 0)
			current_frame = frames.size() - 1;
		return frames[(int)current_frame];
	}

	SDL_Rect& GetCurrentStaticFrame()
	{
		return frames[(int)current_frame];
	}
};