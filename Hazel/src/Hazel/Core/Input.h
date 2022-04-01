#pragma once
#include "Hazel/Core/Base.h"
namespace Hazel {

	class Input
	{
	public:
		 static bool IsKeyPressed(int KeyCode) ;

		 static bool IsMouseButtonPressed(int button);
		 static float GetMouseX();
		 static float GetMouseY();

		 static std::pair<float, float> GetMousePosition();
	};

}