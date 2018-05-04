//BEGIN HEAD
//BEGIN DESCRIPTION

/* This is a small SDL2 demo to shows how to use
 * TextureColorMod
 * RMB reset colors
 * LMB sets a few values - log in console
 */

/* DEFINED PROGRESS GOALS
 * 
 * None atm
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
#include <time.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE 255,255,255,255
#define BLACK 0,0,0,255
#define RED   255,0,0,255
#define WW 550
#define WH (WW/16)*12
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS

int ww=WW;
int wh=WH;
Uint8	r;
Uint8	g;
Uint8   b;
//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;
//END 	VISIBLES

SDL_Point	mouse;

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void assets_in	(void);
void assets_out	(void);
struct timespec diff(struct timespec start, struct timespec end);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "TextureColorMod");
SDL_ShowWindow(Window);
//END WINDOW
struct timespec start, stop, temp;

SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				SDL_SetTextureColorMod(logo, 255,255,255);
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
				SDL_GetTextureColorMod(logo, &r,&g,&b);
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
				temp=diff(start,stop);
				SDL_Log("get: %lu ns", temp.tv_nsec );
				//srcC = srcC * (color / 255)
				SDL_Log("before - r: %d g: %d b: %d", r,g,b);
				static int count=1;
				switch(count)
				{

					case 1:	
						r/=2;
						g/=2;
						b/=2;
						count++;
						//some statements to execute when 1
						break;
					case 2:	
						r=0;
						g=0;
						b=255;
						count++;
						//some statements to execute when 1
						break;
					case 3:	
						r=0;
						g=255;
						b=0;
						count++;
						//some statements to execute when 2
						break;
					case 4:	
						r=255;
						g=0;
						b=0;
						count++;
						//some statements to execute when 3
						break;
					default:
						//some statements to execute when default;
						break;
				}
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
				SDL_SetTextureColorMod(logo, r,g,b);
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
				temp=diff(start,stop);
				SDL_Log("set: %lu ns", temp.tv_nsec );
				SDL_GetTextureColorMod(logo, &r,&g,&b);
				SDL_Log("after - r: %d g: %d b: %d", r,g,b);
				if (count == 5)
					count=1;

			}
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);

	SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);

	SDL_RenderPresent(Renderer);
	//END   RENDERING
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{

	int w,h;
	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/flower.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &w, &h);
	logo_dst.h=h*2;
	logo_dst.w=w*2;
	logo_dst.x=(ww/2)-(logo_dst.w/2);
	logo_dst.y=(wh/2)-(logo_dst.h/2);
	//END 	LOGO

}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
}

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
//END   FUNCTIONS
