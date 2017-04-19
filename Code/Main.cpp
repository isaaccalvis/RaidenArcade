#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

// Animacio de Inici Implementada
// Sistema de keys del sdl_handout6 implementat
// La pantalla de Game Over ja funciona
// La nau ja dispara
// La nau ja fa be la animacio
// Ja hi ha jugador 2
// Ja hi ha 3 nivells de powerUp vermell (Nomes imatge)

enum main_states{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[]){
	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT){
		switch (state){
			case MAIN_CREATION:{
				App = new Application();
				state = MAIN_START;
			}	break;

			case MAIN_START:{
				if(App->Init() == false){
					LOG("Application Init exits with error -----");
					state = MAIN_EXIT;
				}
				else{
					state = MAIN_UPDATE;
				}

			}	break;

			case MAIN_UPDATE:{
				int update_return = App->Update();

				if (update_return == UPDATE_ERROR){
					LOG("Application Update exits with error -----");
					state = MAIN_EXIT;
				} else if (update_return == UPDATE_STOP)
					state = MAIN_FINISH;
			}
				break;

			case MAIN_FINISH:{
				if(App->CleanUp() == false){
					LOG("Application CleanUp exits with error -----");
				}
				else
					main_return = EXIT_SUCCESS;

				state = MAIN_EXIT;

			} break;
		}
	}

	delete App;
	LOG("Game Finished");
	return main_return;
}