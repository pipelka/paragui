#include "pgapplication.h"
#include "pgbutton.h"
#include "pglineedit.h"
#include "pgnavigator.h"

class MyApplication : public PG_Application, public PG_Navigator {
protected:
	bool eventKeyDown(const SDL_KeyboardEvent* key);
};

bool MyApplication::eventKeyDown(const SDL_KeyboardEvent* key) {
	PG_Widget* dest = NULL;

	switch(key->keysym.sym) {
		case SDLK_UP:
			dest = FindUp();
			break;
		case SDLK_DOWN:
			dest = FindDown();
			break;
		case SDLK_LEFT:
			dest = FindLeft();
			break;
		case SDLK_RIGHT:
			dest = FindRight();
			break;
		case SDLK_TAB:
			dest = GotoNext();
			if(dest == NULL) {
				GotoFirst();
			}
			return true;
		case SDLK_SPACE:
			Action(PG_Widget::ACT_OK);
			return true;
		default:
			dest = NULL;
			break;
	}

	if(dest != NULL) {
		Goto(dest);
		return true;
	}

	return false;
}


int main(int argc, char* argv[]) {
	char theme[20];

	strcpy(theme, "default");
	
	// initial flags for screensurface
	Uint32 flags = SDL_SWSURFACE;
	int bpp = 0;

	// construct the application object
	MyApplication app;
	
	for(int c=1; c<argc; c++) {

		if(argv[c][0] != '-') {
			strcpy(theme, argv[c]);
		}

		if(strcmp(argv[c], "-f") == 0) {
			flags |= SDL_FULLSCREEN;
		}

		if(strcmp(argv[c], "-bpp") == 0) {
			bpp = atoi(argv[++c]);
		}
	}

	app.LoadTheme(theme);

	// init 640 x 480
	if(!app.InitScreen(640,480, bpp, flags)){
		printf("Resolution not supported\n");
		exit(-1);
	}

	// construct some widgets
	PG_Button btn1(NULL, PG_Rect(295,20,50,50), "UP");
	PG_Button btn2(NULL, PG_Rect(200,80,50,50), "LEFT");
	PG_Button btn3(NULL, PG_Rect(390,80,50,50), "RIGHT");
	PG_Button btn4(NULL, PG_Rect(295,80,50,50), "HOME");
	PG_Button btn5(NULL, PG_Rect(295,140,50,50), "DOWN");
	PG_LineEdit edit1(NULL, PG_Rect(200,200,250,25));

	// show them
	btn1.Show();
	btn2.Show();
	btn3.Show();
	btn4.Show();
	btn5.Show();
	edit1.Show();

	// add the widgets
	app.Add(&btn1);
	app.Add(&btn2);
	app.Add(&btn3);
	app.Add(&btn4);
	app.Add(&btn5);
	app.Add(&edit1);

	app.GotoFirst();

	app.Run();

	return 0;
}
