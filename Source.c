#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BUTTON_W = 250;
const int BUTTON_H = 50;
int mouse_x = 0;
int mouse_y = 0;

int main() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *button1 = NULL;
	ALLEGRO_BITMAP *button2 = NULL;
	ALLEGRO_BITMAP *button3 = NULL;

	float button1_x = SCREEN_W / 2.0 - BUTTON_W / 2.0;
	float button1_y = SCREEN_H / 2.0 - BUTTON_H / 2.0 - (2 * BUTTON_H);
	float button2_x = SCREEN_W / 2.0 - BUTTON_W / 2.0;
	float button2_y = SCREEN_H / 2.0 - BUTTON_H / 2.0;
	float button3_x = SCREEN_W / 2.0 - BUTTON_W / 2.0;
	float button3_y = SCREEN_H / 2.0 - BUTTON_H / 2.0 + (2 * BUTTON_H);



	bool redraw = true;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	al_install_mouse();
	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
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
	button1 = al_create_bitmap(BUTTON_W, BUTTON_H);
	if (!button1) {
		fprintf(stderr, "failed to create button1 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	button2 = al_create_bitmap(BUTTON_W, BUTTON_H);
	if (!button2) {
		fprintf(stderr, "failed to create button2 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	button3 = al_create_bitmap(BUTTON_W, BUTTON_H);
	if (!button3) {
		fprintf(stderr, "failed to create button3 bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(button1);
	al_clear_to_color(al_map_rgb(255, 100, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(button2);
	al_clear_to_color(al_map_rgb(255, 100, 200));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(button3);
	al_clear_to_color(al_map_rgb(255, 100, 200));
	al_set_target_bitmap(al_get_backbuffer(display));


	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(button1);
		al_destroy_bitmap(button2);
		al_destroy_bitmap(button3);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.button & 1) {
				if (mouse_x > button1_x
					&& mouse_x < (button1_x + BUTTON_W)
					&& mouse_y > button1_y
					&& mouse_y < (button1_y + BUTTON_H)
					) {

					fprintf(stderr, "Rozpoczyna gre\n");

				}
				else if (mouse_x > button2_x
					&& mouse_x < (button2_x + BUTTON_W)
					&& mouse_y > button2_y
					&& mouse_y < (button2_y + BUTTON_H)) {

					fprintf(stderr, "Wyswietla pomoc\n");
				}
				else if (mouse_x > button3_x
					&& mouse_x < (button3_x + BUTTON_W)
					&& mouse_y > button3_y
					&& mouse_y < (button3_y + BUTTON_H)) {

					break;
				}
			}
		}




		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(100, 200, 0));

			al_draw_bitmap(button1, button1_x, button1_y, 0);
			al_draw_bitmap(button2, button2_x, button2_y, 0);
			al_draw_bitmap(button3, button3_x, button3_y, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), (button1_x + (BUTTON_W / 2)), (button1_y + (BUTTON_H / 4)), ALLEGRO_ALIGN_CENTRE, "START");
			al_draw_text(font, al_map_rgb(0, 0, 0), (button2_x + (BUTTON_W / 2)), (button2_y + (BUTTON_H / 4)), ALLEGRO_ALIGN_CENTRE, "POMOC");
			al_draw_text(font, al_map_rgb(0, 0, 0), (button3_x + (BUTTON_W / 2)), (button3_y + (BUTTON_H / 4)), ALLEGRO_ALIGN_CENTRE, "WYJSCIE");
			al_draw_text(font2, al_map_rgb(0, 0, 0), (SCREEN_W / 2), 40, ALLEGRO_ALIGN_CENTRE, "SUPER ZIEMNIAK");

			al_flip_display();
		}

	}

	al_destroy_bitmap(button1);
	al_destroy_bitmap(button2);
	al_destroy_bitmap(button3);
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
