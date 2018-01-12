#include <stdio.h>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>


#define M_PI 3.14159265358979323846

const float FPS = 60;
const int SCREEN_W = 1200;
const int SCREEN_H = 700;
const int ZIEMNIAK_W = 10;
const int ZIEMNIAK_H = 10;
const int MONETA_W = 25;
const int MONETA_H = 25;
const int PRZESZKODA_W = 0.625 * SCREEN_W;
const int PRZESZKODA_H = 5;
const int PRZESZKODA2_W = 5;
const int PRZESZKODA2_H = 0.25 * SCREEN_H;
const int PRZESZKODA3_W = 5;
const int PRZESZKODA3_H = (0.25 * SCREEN_H) + 5;
const int PRZESZKODA4_W = 0.125 * SCREEN_W;
const int PRZESZKODA4_H = 5;
const int PRZESZKODA5_W = 0.125 * SCREEN_W;
const int PRZESZKODA5_H = 5;
const int PRZESZKODA6_W = 5;
const int PRZESZKODA6_H = 0.25 * SCREEN_H;
const int PRZESZKODA7_W = 5;
const int PRZESZKODA7_H = 0.25 * SCREEN_H;
const int PRZESZKODA8_W = 0.25 * SCREEN_W;
const int PRZESZKODA8_H = 5;
const int PRZESZKODA9_W = 5;
const int PRZESZKODA9_H = 0.25 * SCREEN_H;
const int PRZESZKODA10_W = 30;
const int PRZESZKODA10_H = 30;
const int PRZESZKODA14_W = 5;
const int PRZESZKODA14_H = 0.25 * SCREEN_H;
const int PRZESZKODA15_W = 0.125 * SCREEN_W;
const int PRZESZKODA15_H = 5;

const int PRZESZKODA16_W = 0.12 * SCREEN_H;
const int PRZESZKODA16_H = 0.12 * SCREEN_H;

const int META_W = 0.125 * SCREEN_W;
const int META_H = 5;



enum MYKEYS { KEY_LEFT, KEY_RIGHT, KEY_SPACE };

int ziem_x = 0;
int ziem_y = 0;
double ziem_dx = 0;
double ziem_dy = 0;
double ziem_v = 0;
int ziem_kier = 0;

double p_dx;

int przeszkoda_x = 0;
int przeszkoda_y = 0;

int przeszkoda2_x = 0;
int przeszkoda2_y = 0;

int przeszkoda3_x = 0;
int przeszkoda3_y = 0;

int przeszkoda4_x = 0;
int przeszkoda4_y = 0;

int przeszkoda5_x = 0;
int przeszkoda5_y = 0;

int przeszkoda6_x = 0;
int przeszkoda6_y = 0;

int przeszkoda7_x = 0;
int przeszkoda7_y = 0;

int przeszkoda8_x = 0;
int przeszkoda8_y = 0;

int przeszkoda9_x = 0;
int przeszkoda9_y = 0;

int przeszkoda10_x = 0;
int przeszkoda10_y = 0;

int przeszkoda11_x = 0;
int przeszkoda11_y = 0;

int przeszkoda12_x = 0;
int przeszkoda12_y = 0;

int przeszkoda13_x = 0;
int przeszkoda13_y = 0;

int przeszkoda14_x = 0;
int przeszkoda14_y = 0;

int przeszkoda15_x = 0;
int przeszkoda15_y = 0;

int przeszkoda16_x = 0;
int przeszkoda16_y = 0;

int meta_x = 0;
int meta_y = 0;

int points = 0;
int moneta_x = 0;
int moneta_y = 0;
int moneta2_x = 0;
int moneta2_y = 0;
int moneta3_x = 0;
int moneta3_y = 0;
int moneta4_x = 0;
int moneta4_y = 0;
int moneta5_x = 0;
int moneta5_y = 0;
int moneta6_x = 0;
int moneta6_y = 0;


double tab_sin[72];
double tab_cos[72];

void laduj_sin_cos()
{
	for (int i = 0; i < 72; i++)
	{
		tab_sin[i] = sin((M_PI *(i * 5)) / 180);
		tab_cos[i] = cos((M_PI *(i * 5)) / 180);
	}
}

void predkosc() // Obliczanie predkosci czastkowych ziemniaka
{
	if (ziem_v >= 0) { ziem_dx += ziem_v * tab_cos[ziem_kier]; }
	else ziem_v = 0;
	if (ziem_v >= 0) { ziem_dy += ziem_v * tab_sin[ziem_kier]; }

}

void przemieszczenie() // Przemieszczanie ziemniaka
{
	if (ziem_dx >= 1 || ziem_dx <= -1) { ziem_x += int(ziem_dx); ziem_dx = ziem_dx - int(ziem_dx); }
	if (ziem_dy >= 1 || ziem_dy <= -1) { ziem_y += int(ziem_dy); ziem_dy = ziem_dy - int(ziem_dy); }
}

void warunki()
{

	if (ziem_kier > 71) ziem_kier = 0;
	if (ziem_kier < 0) ziem_kier = 71;
	if (ziem_v > 1.5) ziem_v = 1.5;
	if (ziem_v < -1) ziem_v = -1;


}



int main()
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *ziemniak = NULL;
	ALLEGRO_BITMAP *przeszkoda = NULL;
	ALLEGRO_BITMAP *przeszkoda2 = NULL;
	ALLEGRO_BITMAP *przeszkoda3 = NULL;
	ALLEGRO_BITMAP *przeszkoda4 = NULL;
	ALLEGRO_BITMAP *przeszkoda5 = NULL;
	ALLEGRO_BITMAP *przeszkoda6 = NULL;
	ALLEGRO_BITMAP *przeszkoda7 = NULL;
	ALLEGRO_BITMAP *przeszkoda8 = NULL;
	ALLEGRO_BITMAP *przeszkoda9 = NULL;
	ALLEGRO_BITMAP *przeszkoda10 = NULL;
	ALLEGRO_BITMAP *przeszkoda11 = NULL;
	ALLEGRO_BITMAP *przeszkoda12 = NULL;
	ALLEGRO_BITMAP *przeszkoda13 = NULL;
	ALLEGRO_BITMAP *przeszkoda14 = NULL;
	ALLEGRO_BITMAP *przeszkoda15 = NULL;
	
	ALLEGRO_BITMAP *przeszkoda16 = NULL;

	ALLEGRO_BITMAP *meta = NULL;

	ALLEGRO_BITMAP *moneta = NULL;
	ALLEGRO_BITMAP *moneta2 = NULL;
	ALLEGRO_BITMAP *moneta3 = NULL;
	ALLEGRO_BITMAP *moneta4 = NULL;
	ALLEGRO_BITMAP *moneta5 = NULL;
	ALLEGRO_BITMAP *moneta6 = NULL;

	ziem_x = SCREEN_W / 10;
	ziem_y = SCREEN_H / 10;

	przeszkoda_x = 0.125 * SCREEN_W;
	przeszkoda_y = SCREEN_H / 2;
	przeszkoda2_x = SCREEN_W / 2;
	przeszkoda2_y = 0;
	przeszkoda3_x = 0.75 * SCREEN_W;
	przeszkoda3_y = 0.25 * SCREEN_H;
	przeszkoda4_x = 0.875 * SCREEN_W;
	przeszkoda4_y = 0.5 * SCREEN_H;
	przeszkoda5_x = 0.75 * SCREEN_W;
	przeszkoda5_y = 0.25 * SCREEN_H;
	przeszkoda6_x = 0.875 * SCREEN_W;
	przeszkoda6_y = 0.625 * SCREEN_H;
	przeszkoda7_x = 0.75 * SCREEN_W;
	przeszkoda7_y = 0.625 * SCREEN_H;
	przeszkoda8_x = 0.5 * SCREEN_W;
	przeszkoda8_y = 0.75 * SCREEN_H;
	przeszkoda9_x = 0.375 * SCREEN_W;
	przeszkoda9_y = 0.75 * SCREEN_H;

	przeszkoda10_x = 0.125 * SCREEN_W;
	przeszkoda10_y = 0.625 * SCREEN_H;

	przeszkoda11_x = przeszkoda10_x + (3 * PRZESZKODA10_W);
	przeszkoda11_y = przeszkoda10_y;

	przeszkoda12_x = przeszkoda10_x;
	przeszkoda12_y = przeszkoda10_y + (3 * PRZESZKODA10_H);

	przeszkoda13_x = przeszkoda11_x;
	przeszkoda13_y = przeszkoda12_y;

	przeszkoda14_x = przeszkoda_x;
	przeszkoda14_y = 0.25 * SCREEN_H;

	przeszkoda15_x = 0;
	przeszkoda15_y = 0.25 * SCREEN_H;

	przeszkoda16_x = 0.5 * SCREEN_W;
	przeszkoda16_y = (0.5 * SCREEN_H) + 5;

	meta_x = 0;
	meta_y = (SCREEN_H / 4) + 5;


	moneta_x = SCREEN_W / 3;
	moneta_y = SCREEN_H / 3;

	moneta2_x = przeszkoda2_x + 60;
	moneta2_y = 60;

	moneta3_x = SCREEN_W - 100;
	moneta3_y = SCREEN_H - 100;

	moneta4_x = (0.75 * SCREEN_W) + 50;
	moneta4_y = (0.5 * SCREEN_H) + 100;

	moneta5_x = 0.625 * SCREEN_W;
	moneta5_y = 0.875 * SCREEN_H;

	moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
	moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);

	bool redraw = true;
	bool doexit = false;
	bool key[3] = { false, false, false };

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_install_keyboard();
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
	al_init_image_addon(); //initialize the image addon
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);

	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	ALLEGRO_FONT *font = al_load_ttf_font("OpenSans-Regular.ttf", 18, 0);
	ALLEGRO_FONT *font2 = al_load_ttf_font("OpenSans-Regular.ttf", 40, 0);
	if (!font) {
		fprintf(stderr, "Could not load 'OpenSans-Regular.ttf'.\n");
		return -1;
	}

	ziemniak = al_create_bitmap(ZIEMNIAK_W, ZIEMNIAK_H);
	if (!ziemniak) {
		fprintf(stderr, "failed to create ziemniak bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	przeszkoda = al_create_bitmap(PRZESZKODA_W, PRZESZKODA_H);
	if (!przeszkoda) {
		fprintf(stderr, "failed to create przeszkoda bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda2 = al_create_bitmap(PRZESZKODA2_W, PRZESZKODA2_H);
	if (!przeszkoda2) {
		fprintf(stderr, "failed to create przeszkoda2 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda3 = al_create_bitmap(PRZESZKODA3_W, PRZESZKODA3_H);
	if (!przeszkoda3) {
		fprintf(stderr, "failed to create przeszkoda3 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda4 = al_create_bitmap(PRZESZKODA4_W, PRZESZKODA4_H);
	if (!przeszkoda4) {
		fprintf(stderr, "failed to create przeszkoda4 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda5 = al_create_bitmap(PRZESZKODA5_W, PRZESZKODA5_H);
	if (!przeszkoda5) {
		fprintf(stderr, "failed to create przeszkoda5 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda6 = al_create_bitmap(PRZESZKODA6_W, PRZESZKODA6_H);
	if (!przeszkoda6) {
		fprintf(stderr, "failed to create przeszkoda6 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda7 = al_create_bitmap(PRZESZKODA7_W, PRZESZKODA7_H);
	if (!przeszkoda7) {
		fprintf(stderr, "failed to create przeszkoda7 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda8 = al_create_bitmap(PRZESZKODA8_W, PRZESZKODA8_H);
	if (!przeszkoda8) {
		fprintf(stderr, "failed to create przeszkoda8 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda9 = al_create_bitmap(PRZESZKODA9_W, PRZESZKODA9_H);
	if (!przeszkoda9) {
		fprintf(stderr, "failed to create przeszkoda9 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda10 = al_create_bitmap(PRZESZKODA10_W, PRZESZKODA10_H);
	if (!przeszkoda10) {
		fprintf(stderr, "failed to create przeszkoda10 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda11 = al_create_bitmap(PRZESZKODA10_W, PRZESZKODA10_H);
	if (!przeszkoda11) {
		fprintf(stderr, "failed to create przeszkoda11 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda12 = al_create_bitmap(PRZESZKODA10_W, PRZESZKODA10_H);
	if (!przeszkoda12) {
		fprintf(stderr, "failed to create przeszkoda12 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda13 = al_create_bitmap(PRZESZKODA10_W, PRZESZKODA10_H);
	if (!przeszkoda13) {
		fprintf(stderr, "failed to create przeszkoda13 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda14 = al_create_bitmap(PRZESZKODA14_W, PRZESZKODA14_H);
	if (!przeszkoda14) {
		fprintf(stderr, "failed to create przeszkoda14 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	przeszkoda15 = al_create_bitmap(PRZESZKODA15_W, PRZESZKODA15_H);
	if (!przeszkoda15) {
		fprintf(stderr, "failed to create przeszkoda15 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	przeszkoda16 = al_create_bitmap(PRZESZKODA16_W, PRZESZKODA16_H);
	if (!przeszkoda16) {
		fprintf(stderr, "failed to create przeszkoda16 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	meta = al_create_bitmap(META_W, META_H);
	if (!meta) {
		fprintf(stderr, "failed to create meta bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	/*	moneta = al_create_bitmap(MONETA_W, MONETA_H);
	if (!moneta) {
	fprintf(stderr, "failed to create moneta bitmap!\n");
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
	}*/
	moneta = al_load_bitmap("moneta.bmp");
	moneta2 = al_load_bitmap("moneta.bmp");
	moneta3 = al_load_bitmap("moneta.bmp");
	moneta4 = al_load_bitmap("moneta.bmp");
	moneta5 = al_load_bitmap("moneta.bmp");
	moneta6 = al_load_bitmap("moneta.bmp");
	przeszkoda16 = al_load_bitmap("skull.bmp");


	al_set_target_bitmap(ziemniak);
	al_clear_to_color(al_map_rgb(255, 100, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda2);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda3);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda4);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda5);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda6);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda7);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda8);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda9);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda10);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda11);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda12);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda13);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda14);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda15);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(meta);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(display));



	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(ziemniak);
		al_destroy_bitmap(przeszkoda);
		al_destroy_bitmap(przeszkoda2);
		al_destroy_bitmap(przeszkoda3);
		al_destroy_bitmap(przeszkoda4);
		al_destroy_bitmap(przeszkoda5);
		al_destroy_bitmap(przeszkoda6);
		al_destroy_bitmap(przeszkoda7);
		al_destroy_bitmap(przeszkoda8);
		al_destroy_bitmap(przeszkoda9);
		al_destroy_bitmap(przeszkoda10);
		al_destroy_bitmap(przeszkoda11);
		al_destroy_bitmap(przeszkoda12);
		al_destroy_bitmap(przeszkoda13);
		al_destroy_bitmap(przeszkoda14);
		al_destroy_bitmap(przeszkoda15);
		al_destroy_bitmap(przeszkoda16);
		al_destroy_bitmap(meta);
		al_destroy_bitmap(moneta);
		al_destroy_bitmap(moneta2);
		al_destroy_bitmap(moneta3);
		al_destroy_bitmap(moneta4);
		al_destroy_bitmap(moneta5);
		al_destroy_bitmap(moneta6);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {


			if (key[KEY_SPACE]) {

				ziem_v = 5;
				p_dx = 3 + points;

				if (key[KEY_LEFT]) {
					ziem_kier--;
				}

				if (key[KEY_RIGHT]) {
					ziem_kier++;
				}

			}
			else {

				ziem_v = 0;
				p_dx = 0;
			}

			if(przeszkoda16_x >= - PRZESZKODA16_W && przeszkoda16_x <= SCREEN_W)
			{
				przeszkoda16_x -= int(p_dx); p_dx = p_dx - int(p_dx);
			}
			else if (przeszkoda16_x = - PRZESZKODA16_W)
			{
				przeszkoda16_x = SCREEN_W;
			}
			

			if (ziem_x <= 0 || ziem_x >= SCREEN_W || ziem_y <= 0 || ziem_y >= SCREEN_H)
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;

				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}

			if (ziem_x  >= moneta_x && ziem_x  <= (moneta_x + MONETA_W) && ziem_y >= moneta_y && ziem_y <= (moneta_y + MONETA_H))
			{
				points++;
				moneta_x = SCREEN_W + 100;
				moneta_y = SCREEN_H + 100;

				redraw = true;
			}
			if (ziem_x >= moneta2_x && ziem_x <= (moneta2_x + MONETA_W) && ziem_y >= moneta2_y && ziem_y <= (moneta2_y + MONETA_H))
			{
				points++;
				moneta2_x = SCREEN_W + 100;
				moneta2_y = SCREEN_H + 100;

				redraw = true;
			}
			if (ziem_x >= moneta3_x && ziem_x <= (moneta3_x + MONETA_W) && ziem_y >= moneta3_y && ziem_y <= (moneta3_y + MONETA_H))
			{
				points++;
				moneta3_x = SCREEN_W + 100;
				moneta3_y = SCREEN_H + 100;

				redraw = true;
			}
			if (ziem_x >= moneta4_x && ziem_x <= (moneta4_x + MONETA_W) && ziem_y >= moneta4_y && ziem_y <= (moneta4_y + MONETA_H))
			{
				points++;
				moneta4_x = SCREEN_W + 100;
				moneta4_y = SCREEN_H + 100;

				redraw = true;
			}
			if (ziem_x >= moneta5_x && ziem_x <= (moneta5_x + MONETA_W) && ziem_y >= moneta5_y && ziem_y <= (moneta5_y + MONETA_H))
			{
				points++;
				moneta5_x = SCREEN_W + 100;
				moneta5_y = SCREEN_H + 100;

				redraw = true;
			}

			if (ziem_x >= moneta6_x && ziem_x <= (moneta6_x + MONETA_W) && ziem_y >= moneta6_y && ziem_y <= (moneta6_y + MONETA_H))
			{
				points++;
				moneta6_x = SCREEN_W + 100;
				moneta6_y = SCREEN_H + 100;

				redraw = true;
			}

			if (ziem_x >= przeszkoda_x &&
				ziem_x <= (przeszkoda_x + PRZESZKODA_W) &&
				ziem_y >= przeszkoda_y &&
				ziem_y <= (przeszkoda_y + PRZESZKODA_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda2_x &&
				ziem_x <= (przeszkoda2_x + PRZESZKODA2_W) &&
				ziem_y >= przeszkoda2_y &&
				ziem_y <= (przeszkoda2_y + PRZESZKODA2_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda3_x &&
				ziem_x <= (przeszkoda3_x + PRZESZKODA3_W) &&
				ziem_y >= przeszkoda3_y &&
				ziem_y <= (przeszkoda3_y + PRZESZKODA3_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda4_x &&
				ziem_x <= (przeszkoda4_x + PRZESZKODA4_W) &&
				ziem_y >= przeszkoda4_y &&
				ziem_y <= (przeszkoda4_y + PRZESZKODA4_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda5_x &&
				ziem_x <= (przeszkoda5_x + PRZESZKODA5_W) &&
				ziem_y >= przeszkoda5_y &&
				ziem_y <= (przeszkoda5_y + PRZESZKODA5_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda6_x &&
				ziem_x <= (przeszkoda6_x + PRZESZKODA6_W) &&
				ziem_y >= przeszkoda6_y &&
				ziem_y <= (przeszkoda6_y + PRZESZKODA6_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda7_x &&
				ziem_x <= (przeszkoda7_x + PRZESZKODA7_W) &&
				ziem_y >= przeszkoda7_y &&
				ziem_y <= (przeszkoda7_y + PRZESZKODA7_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda8_x &&
				ziem_x <= (przeszkoda8_x + PRZESZKODA8_W) &&
				ziem_y >= przeszkoda8_y &&
				ziem_y <= (przeszkoda8_y + PRZESZKODA8_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda9_x &&
				ziem_x <= (przeszkoda9_x + PRZESZKODA9_W) &&
				ziem_y >= przeszkoda9_y &&
				ziem_y <= (przeszkoda9_y + PRZESZKODA9_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda10_x &&
				ziem_x <= (przeszkoda10_x + PRZESZKODA10_W) &&
				ziem_y >= przeszkoda10_y &&
				ziem_y <= (przeszkoda10_y + PRZESZKODA10_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda11_x &&
				ziem_x <= (przeszkoda11_x + PRZESZKODA10_W) &&
				ziem_y >= przeszkoda11_y &&
				ziem_y <= (przeszkoda11_y + PRZESZKODA10_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda12_x &&
				ziem_x <= (przeszkoda12_x + PRZESZKODA10_W) &&
				ziem_y >= przeszkoda12_y &&
				ziem_y <= (przeszkoda12_y + PRZESZKODA10_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda13_x &&
				ziem_x <= (przeszkoda13_x + PRZESZKODA10_W) &&
				ziem_y >= przeszkoda13_y &&
				ziem_y <= (przeszkoda13_y + PRZESZKODA10_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 20;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda14_x &&
				ziem_x <= (przeszkoda14_x + PRZESZKODA14_W) &&
				ziem_y >= przeszkoda14_y &&
				ziem_y <= (przeszkoda14_y + PRZESZKODA14_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda15_x &&
				ziem_x <= (przeszkoda15_x + PRZESZKODA15_W) &&
				ziem_y >= przeszkoda15_y &&
				ziem_y <= (przeszkoda15_y + PRZESZKODA15_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= przeszkoda16_x &&
				ziem_x <= (przeszkoda16_x + PRZESZKODA16_W) &&
				ziem_y >= przeszkoda16_y &&
				ziem_y <= (przeszkoda16_y + PRZESZKODA16_H))
			{
				ziem_v = 0;
				ziem_kier = 0;
				points = 0;
				//al_rest(5);
				ziem_x = SCREEN_W / 20;
				ziem_y = SCREEN_H / 20;
				moneta_x = SCREEN_W / 3;
				moneta_y = SCREEN_H / 3;
				moneta2_x = przeszkoda2_x + 60;
				moneta2_y = 60;
				moneta3_x = SCREEN_W - 100;
				moneta3_y = SCREEN_H - 100;
				moneta4_x = (0.75 * SCREEN_W) + 50;
				moneta4_y = (0.5 * SCREEN_H) + 100;
				moneta5_x = 0.625 * SCREEN_W;
				moneta5_y = 0.875 * SCREEN_H;
				moneta6_x = 0.5 * (przeszkoda10_x + przeszkoda11_x);
				moneta6_y = 0.5 * (przeszkoda10_y + przeszkoda12_y);
				przeszkoda16_x = 0.5 * SCREEN_W;
				przeszkoda16_y = (0.5 * SCREEN_H) + 5;

				key[KEY_SPACE] = false;
				redraw = true;
			}
			if (ziem_x >= meta_x &&
				ziem_x <= (meta_x + META_W) &&
				ziem_y >= meta_y &&
				ziem_y <= (meta_y + META_H))
			{

				doexit = true;
				break;

			}


			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;


			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}


		}
		laduj_sin_cos();
		predkosc();
		przemieszczenie();
		warunki();
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(ziemniak, (ziem_x - (0.5 * ZIEMNIAK_W)), (ziem_y - (0.5 * ZIEMNIAK_H)), 0);
			//			al_draw_rotated_bitmap(ziemniak,
			//				ziem_x, ziem_y, (ziem_x + ZIEMNIAK_W), (ziem_y + (ZIEMNIAK_H / 2)), tab_cos[ziem_kier], 0);
			al_draw_bitmap(przeszkoda, przeszkoda_x, przeszkoda_y, 0);
			al_draw_bitmap(przeszkoda2, przeszkoda2_x, przeszkoda2_y, 0);
			al_draw_bitmap(przeszkoda3, przeszkoda3_x, przeszkoda3_y, 0);
			al_draw_bitmap(przeszkoda4, przeszkoda4_x, przeszkoda4_y, 0);
			al_draw_bitmap(przeszkoda5, przeszkoda5_x, przeszkoda5_y, 0);
			al_draw_bitmap(przeszkoda6, przeszkoda6_x, przeszkoda6_y, 0);
			al_draw_bitmap(przeszkoda7, przeszkoda7_x, przeszkoda7_y, 0);
			al_draw_bitmap(przeszkoda8, przeszkoda8_x, przeszkoda8_y, 0);
			al_draw_bitmap(przeszkoda9, przeszkoda9_x, przeszkoda9_y, 0);
			al_draw_bitmap(przeszkoda10, przeszkoda10_x, przeszkoda10_y, 0);
			al_draw_bitmap(przeszkoda11, przeszkoda11_x, przeszkoda11_y, 0);
			al_draw_bitmap(przeszkoda12, przeszkoda12_x, przeszkoda12_y, 0);
			al_draw_bitmap(przeszkoda13, przeszkoda13_x, przeszkoda13_y, 0);
			al_draw_bitmap(przeszkoda14, przeszkoda14_x, przeszkoda14_y, 0);
			al_draw_bitmap(przeszkoda15, przeszkoda15_x, przeszkoda15_y, 0);
			al_draw_bitmap(przeszkoda16, przeszkoda16_x, przeszkoda16_y, 0);

			al_draw_bitmap(meta, meta_x, meta_y, 0);

			al_draw_bitmap(moneta, moneta_x, moneta_y, 0);
			al_draw_bitmap(moneta2, moneta2_x, moneta2_y, 0);
			al_draw_bitmap(moneta3, moneta3_x, moneta3_y, 0);
			al_draw_bitmap(moneta4, moneta4_x, moneta4_y, 0);
			al_draw_bitmap(moneta5, moneta5_x, moneta5_y, 0);
			al_draw_bitmap(moneta6, moneta6_x, moneta6_y, 0);
			al_draw_textf(font, al_map_rgb(0, 0, 255), (SCREEN_W - 100), (10), ALLEGRO_ALIGN_CENTRE, "WYNIK: %d", points);

			al_flip_display();
		}
	}

	al_destroy_bitmap(ziemniak);
	al_destroy_bitmap(przeszkoda);
	al_destroy_bitmap(przeszkoda2);
	al_destroy_bitmap(przeszkoda3);
	al_destroy_bitmap(przeszkoda4);
	al_destroy_bitmap(przeszkoda5);
	al_destroy_bitmap(przeszkoda6);
	al_destroy_bitmap(przeszkoda7);
	al_destroy_bitmap(przeszkoda8);
	al_destroy_bitmap(przeszkoda9);
	al_destroy_bitmap(przeszkoda10);
	al_destroy_bitmap(przeszkoda11);
	al_destroy_bitmap(przeszkoda12);
	al_destroy_bitmap(przeszkoda13);
	al_destroy_bitmap(przeszkoda14);
	al_destroy_bitmap(przeszkoda15);
	al_destroy_bitmap(przeszkoda16);

	al_destroy_bitmap(meta);

	al_destroy_bitmap(moneta);
	al_destroy_bitmap(moneta2);
	al_destroy_bitmap(moneta3);
	al_destroy_bitmap(moneta4);
	al_destroy_bitmap(moneta5);
	al_destroy_bitmap(moneta6);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}
