#include "Application.h"
#include "ApplicationListener.h"

class GameCreationTest : public ApplicationListener {
public:
	void create() 
	{
		std::cout << "Game created!" << std::endl;
	}

	void resize(unsigned width, unsigned height) 
	{

	}

	void keyboardInput(InputEvent& e)
	{
		std::cout << "There was a keyboard input!" << std::endl;

	}

	void mouseInput(InputEvent& e)
	{
		std::cout << "There was a mouse input!" << std::endl;

	}

	void update(double delta)
	{
		
	}

	void render() 
	{

	}
}; 

int main(int argc, char** argv)
{
	GameCreationTest game; // user defined game
	Configuration config; // create default configuration, renderer defaults to OpenGL
	config.renderer = COMPATIBILITY;
	Application test(game, config); // pass the game and configuration to the application container system
	return 0;
}