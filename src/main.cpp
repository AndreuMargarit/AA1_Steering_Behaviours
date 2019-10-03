#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneSeek.h"
#include "SceneFlee.h"
#include "SceneSeekFlee.h"
#include "SceneArrive.h"
#include "SceneWander.h"


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
				LoadScene(new SceneSeek, curr_scene, app);
				break;
			case SDL_SCANCODE_2:
				LoadScene(new SceneFlee, curr_scene, app);
				break;
			case SDL_SCANCODE_3:
				LoadScene(new SceneSeekFlee, curr_scene, app);
				break;
			case SDL_SCANCODE_4:
				LoadScene(new SceneArrive, curr_scene, app);
				break;
			case SDL_SCANCODE_7:
				LoadScene(new SceneWander, curr_scene, app);
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

void LoadScene(Scene* scene, Scene* curr_scene, SDL_SimpleApp* app) {
	delete(curr_scene);
	curr_scene = scene;
	app->setWindowTitle(curr_scene->getTitle());
}