#include <stdio.h>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>


#define M_PI 3.14159265358979323846

const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 700;
const int ZIEMNIAK_W = 10;
const int ZIEMNIAK_H = 10;
const int MONETA_W = 25;
const int MONETA_H = 25;
const int PRZESZKODA_W = 0.75 * SCREEN_W;
const int PRZESZKODA_H = 5;

enum MYKEYS { KEY_LEFT, KEY_RIGHT, KEY_SPACE };

int ziem_x = 0;
int ziem_y = 0;
double ziem_dx = 0;
double ziem_dy = 0;
double ziem_v = 0;
int ziem_kier = 0;

int przeszkoda_x = 0;
int przeszkoda_y = 0;

int points = 0;
int moneta_x = 0;
int moneta_y = 0;
int moneta2_x = 0;
int moneta2_y = 0;


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
	ALLEGRO_BITMAP *moneta = NULL;
	ALLEGRO_BITMAP *moneta2 = NULL;

	ziem_x = SCREEN_W / 10;
	ziem_y = SCREEN_H / 10;

	przeszkoda_x = 0;
	przeszkoda_y = SCREEN_H / 2;
	moneta_x = SCREEN_W / 3;
	moneta_y = SCREEN_H / 3;
	moneta2_x = SCREEN_W - 100;
	moneta2_y = SCREEN_H - 100;

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

	/*	moneta = al_create_bitmap(MONETA_W, MONETA_H);
		if (!moneta) {
			fprintf(stderr, "failed to create moneta bitmap!\n");
			al_destroy_display(display);
			al_destroy_timer(timer);
			return -1;
		}
*/  moneta = al_load_bitmap("moneta.bmp");
	moneta2 = al_load_bitmap("moneta.bmp");

	al_set_target_bitmap(ziemniak);
	al_clear_to_color(al_map_rgb(255, 100, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(przeszkoda);
	al_clear_to_color(al_map_rgb(1, 255, 200));
	al_set_target_bitmap(al_get_backbuffer(display));



	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(ziemniak);
		al_destroy_bitmap(przeszkoda);
		al_destroy_bitmap(moneta);
		al_destroy_bitmap(moneta2);
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

			}
			else {

				ziem_v = 0;
			}

			if (key[KEY_LEFT]) {
				ziem_kier--;
			}

			if (key[KEY_RIGHT]) {
				ziem_kier++;
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
				moneta2_x = SCREEN_W - 100;
				moneta2_y = SCREEN_H - 100;

				key[KEY_SPACE] = false;
				redraw = true;
			}

			if (ziem_x >= moneta_x && ziem_x <= (moneta_x + MONETA_W) && ziem_y >= moneta_y && ziem_y <= (moneta_y + MONETA_H))
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
				moneta2_x = SCREEN_W - 100;
				moneta2_y = SCREEN_H - 100;

				key[KEY_SPACE] = false;
				redraw = true;
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
			al_draw_bitmap(ziemniak, ziem_x, ziem_y, 0);
//			al_draw_rotated_bitmap(ziemniak,
//				ziem_x, ziem_y, (ziem_x + ZIEMNIAK_W), (ziem_y + (ZIEMNIAK_H / 2)), tab_cos[ziem_kier], 0);
			al_draw_bitmap(przeszkoda, przeszkoda_x, przeszkoda_y, 0);
			al_draw_bitmap(moneta, moneta_x, moneta_y, 0);
			al_draw_bitmap(moneta2, moneta2_x, moneta2_y, 0);
			al_draw_textf(font, al_map_rgb(0, 0, 255), (SCREEN_W - 100), (10), ALLEGRO_ALIGN_CENTRE, "WYNIK: %d", points);

			al_flip_display();
		}
	}

	al_destroy_bitmap(ziemniak);
	al_destroy_bitmap(przeszkoda);
	al_destroy_bitmap(moneta);
	al_destroy_bitmap(moneta2);
	al_destroy_timer(timer);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);


	return 0;
}