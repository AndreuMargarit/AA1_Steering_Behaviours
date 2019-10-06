#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneSeek.h"
#include "SceneFlee.h"
#include "SceneSeekFlee.h"
#include "SceneArrive.h"
#include "SceneWander.h"
#include "SceneFlock.h"


using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneSeek;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_1:
				delete(curr_scene);
				curr_scene = new SceneSeek;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_2:
				delete(curr_scene);
				curr_scene = new SceneFlee;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_3:
				delete(curr_scene);
				curr_scene = new SceneSeekFlee;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_4:
				delete(curr_scene);
				curr_scene = new SceneArrive;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_7:
				delete(curr_scene);
				curr_scene = new SceneWander;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_8:
				delete(curr_scene);
				curr_scene = new SceneFlock;
				app->setWindowTitle(curr_scene->getTitle());
				break;
			case SDL_SCANCODE_Q:
			case SDL_SCANCODE_ESCAPE:
				quit = true;
				break;
			case SDL_SCANCODE_F:
				app->setFullScreen();
			default:
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}

