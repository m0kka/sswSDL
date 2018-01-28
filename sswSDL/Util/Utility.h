#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <gmtl\gmtl.h>
#include <SDL.h>


struct Util {

	/*
	* Get the resource path for resources located in res/subDir
	* It's assumed the project directory is structured like:
	* bin/
	*  Configuration/Executable
	* res/
	*  01/
	*  02/
	*
	* Paths returned will be solutionDir/res/subDir
	*/

	static std::string getResourcePath(const std::string &subDir = "") {
		//We need to choose the path separator properly based on which
		//platform we're running on, since Windows uses a different
		//separator than most systems
#ifdef _WIN32
		const char PATH_SEP = '\\';
#else
		const char PATH_SEP = '/';
#endif
		//This will hold the base resource path: solutionDir/res/
		//We give it static lifetime so that we'll only need to call
		//SDL_GetBasePath once to get the executable path
		static std::string baseRes;
		if (baseRes.empty()) {
			//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
			char *basePath = SDL_GetBasePath();
			if (basePath) {
				baseRes = basePath;
				SDL_free(basePath);
			}
			else {
				std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
				return "";
			}
			//We replace the last bin/ with res/ to get the the resource path
			size_t pos = baseRes.rfind("bin");
			baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
		}
		//If we want a specific subdirectory path in the resource directory
		//append it to the base path. This would be something like Lessons/res/Lesson0
		return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
	}

	/**
	* Log an SDL error with some error message to the output stream of our choice
	* @param os The output stream to write the message to
	* @param msg The error message to write, format will be msg error: SDL_GetError()
	*/

	static void logSDLError(std::ostream & os, const std::string & msg) {
		os << msg << " error: " << SDL_GetError() << std::endl;
	}

	/*
	* Recurse through the list of arguments to clean up, cleaning up
	* the first one in the list each iteration.
	*/
	template<typename T, typename... Args>
	static void cleanup(T *t, Args&&... args) {
		//Cleanup the first item in the list
		cleanup(t);
		//Clean up the remaining arguments
		cleanup(std::forward<Args>(args)...);
	}
	/*
	* These specializations serve to free the passed argument and also provide the
	* base cases for the recursive call above, eg. when args is only a single
	* item one of the specializations below will be called by
	* cleanup(std::forward<Args>(args)...), ending the recursion
	*/
	template<>
	static inline void cleanup<SDL_Window>(SDL_Window *win) {
		if (!win) {
			return;
		}
		SDL_DestroyWindow(win);
	}
	template<>
	static inline void cleanup<SDL_Renderer>(SDL_Renderer *ren) {
		if (!ren) {
			return;
		}
		SDL_DestroyRenderer(ren);
	}
	template<>
	static inline void cleanup<SDL_Texture>(SDL_Texture *tex) {
		if (!tex) {
			return;
		}
		SDL_DestroyTexture(tex);
	}
	template<>
	static inline void cleanup<SDL_Surface>(SDL_Surface *surf) {
		if (!surf) {
			return;
		}
		SDL_FreeSurface(surf);
	}


	// Word-Wrapping function by jsmith
	static std::string wordWrap(std::string str, size_t width = 55) {

		size_t curWidth = width;
		while (curWidth < str.length()) {
			std::string::size_type spacePos = str.find(' ', curWidth);

			if (spacePos == std::string::npos)
				spacePos = str.find(' ', curWidth);

			if (spacePos != std::string::npos) {
				str[spacePos] = '\n';
				curWidth = spacePos + width + 1;
			}
		}

		return str;
	}

};

struct MathsUtil {

	static inline int roundInt(double x) {

		x += 0.5;
		return (int) x;
	}

	static inline int nextPowerOfTwo(int x) {

		double logBase = log(x);
		return roundInt(pow(2, ceil(logBase)));
	}

	static inline float degreeToRadian(float degree) {

		return degree * 0.0174532925;
	}

	/*
	Quake-inspired reverse sqrt function.
	*/

	static float Q_rsqrt(float number) {

		long i;
		float x2, y;
		const float threehalves = 1.5f;

		x2 = number * 0.5f;
		y = number;
		i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;
		y = y * (threehalves - (x2*y*y));

		return y;
	}

	static inline void vec2fToRect(const gmtl::Vec2f& vec, SDL_Rect& rect) {
		rect.x = vec[0];
		rect.y = vec[1];
	}

	static inline void rectToVec2f(const SDL_Rect& rect, gmtl::Vec2f& vec) {
		vec[0] = rect.x;
		vec[1] = rect.y;
	}

	static inline SDL_Rect vec2fToRect(const gmtl::Vec2f& vec) {
		SDL_Rect rect;
		vec2fToRect(vec, rect);
		return rect;
	}

	static inline gmtl::Vec2f rectToVec2f(const SDL_Rect& rect) {
		gmtl::Vec2f vec;
		rectToVec2f(rect, vec);
		return vec;
	}

	static inline void vec2iToRect(const gmtl::Vec2i& vec, SDL_Rect& rect) {
		rect.x = vec[0];
		rect.y = vec[1];
	}

	static inline void rectToVec2i(const SDL_Rect& rect, gmtl::Vec2i& vec) {
		vec[0] = rect.x;
		vec[1] = rect.y;
	}

	static inline SDL_Rect vec2iToRect(const gmtl::Vec2i& vec) {
		SDL_Rect rect;
		vec2iToRect(vec, rect);
		return rect;
	}

	static inline gmtl::Vec2i rectToVec2i(const SDL_Rect& rect) {
		gmtl::Vec2i vec;
		rectToVec2i(rect, vec);
		return vec;
	}
};