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

	void processInput(SDL_Event& e)
	{

	}

	void update(double delta)
	{
		
	}

	void render() 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// using fixed pipeline - probably not your intention but gets something drawn to see
		// that your project/dev enviornment is working
		glClearColor(1, 1, 1, 1);
		glBegin(GL_TRIANGLES);                     // Drawing Using Triangles
		glVertex3f(0.0f, 1.0f, 0.0f);              // Top
		glVertex3f(-1.0f, -1.0f, 0.0f);            // Bottom Left
		glVertex3f(1.0f, -1.0f, 0.0f);             // Bottom Right
		glEnd();
	}
}; 

int main(int argc, char** argv)
{
	GameCreationTest game; // user defined game
	Configuration config; // create default configuration 
	Application test(game, config); // pass the game and configuration to the application container system
	return 0;
}