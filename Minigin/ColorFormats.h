#pragma once
#include <SDL.h>
//https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
//but with templates

template <typename T>
struct rgb 
{
	T r;       // a fraction between 0 and 1
	T g;       // a fraction between 0 and 1
	T b;       // a fraction between 0 and 1

	rgb<Uint8> ToUint8()
	{
		rgb<Uint8> out;
		out.r = (Uint8) std::round(r * 255);
		out.g = (Uint8) std::round(g * 255);
		out.b = (Uint8) std::round(b * 255);
		return out;
	}

	operator SDL_Color()
	{
		SDL_Color newc;
		newc.r = (Uint8) std::round(r * 255);
		newc.g = (Uint8) std::round(g * 255);
		newc.b = (Uint8) std::round(b * 255);
		newc.a = 255;
		return newc;
	}
};

template <typename T>
struct hsv 
{
	T h;       // angle in degrees
	T s;       // a fraction between 0 and 1
	T v;       // a fraction between 0 and 1
	operator SDL_Color()
	{
		return hsv2rgb(*this);
	}
	operator rgb<T>()
	{
		return hsv2rgb(*this);
	}
};

template <typename T>
static hsv<T> rgb2hsv(rgb<T> in)
{
	hsv<T>         out;
	T      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0;
		out.h = 0.0;                            // its now undefined
		return out;
	}
	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (in.g - in.b) / delta;        // between yellow & magenta
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}

template <typename T>
static rgb<T> hsv2rgb(hsv<T> in)
{
	T      hh, p, q, t, ff;
	int        i;
	rgb<T>         out;

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = T(in.v * (1.0 - in.s));
	q = T(in.v * (1.0 - (in.s * ff)));
	t = T(in.v * (1.0 - (in.s * (1.0 - ff))));

	switch (i) {
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}