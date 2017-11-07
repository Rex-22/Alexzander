#include <iostream>

#include <Alex.h>
#include "Test2D.h"

using namespace al;
using namespace graphics;

class Game : public Application
{
public :
	Game()
		: Application("Alexzander!", WindowProperties{ 960, 540, false })
	{	}

	void Init() override
	{
		Application::Init();

		PushLayer(new Test2D());
		// PushLayer(spnew Test3D());
		// PushLayer(spnew SponzaTest());
		// PushLayer(spnew DeferredTest()); // Doesn't work atm
	}
};

int main()
{
	Game game;
	
	game.Start();
	return 0;
}
