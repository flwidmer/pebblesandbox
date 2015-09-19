#include <pebble.h>

#define KEY_DATA 5
  
static void main_window_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "main window load called");
}

static void main_window_unload(Window *window) {

}

  
Window *window;
TextLayer *text_layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Registering with server");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}


void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

void init comms (void) {
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

 void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
}

 void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

 void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

 void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

int main(void) {
	handle_init();
  init_comms();
	app_event_loop();
	handle_deinit();
}
