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
		std::cout << "resize" << width << " " << height << std::endl;
	}

	void keyboardInput(InputEvent& e)
	{

	}

	void mouseInput(InputEvent& e)
	{
	
	}

	void update(double delta)
	{
		
	}

	void render() 
	{
		// using fixed pipeline
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);                     // Drawing Using Triangles
		glVertex3f(0.0f, 1.0f, 0.0f);              // Top
		glVertex3f(-1.0f, -1.0f, 0.0f);            // Bottom Left
		glVertex3f(1.0f, -1.0f, 0.0f);             // Bottom Right
		glEnd();
	}
}; 

/**int main(int argc, char** argv)
{
	GameCreationTest game; // user defined game
	Configuration config; // create default configuration, renderer defaults to OpenGL
	Application test(game, config); // pass the game and configuration to the application container system
	return 0;
} **/