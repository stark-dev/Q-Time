#include <pebble.h>

#define COLOR_YELLOW GColorFromRGB(251, 216, 62)

// Window
static Window    *s_main_window;
// Layers
static Layer     *s_canvas_layer;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_day_layer;
static GBitmap   *s_bt_conn, *s_bt_disc;
static GBitmap   *s_quiet_on, *s_quiet_off;
static GBitmap   *s_battery, *s_battery_low, *s_battery_very_low, *s_battery_ch;
// Static variables - battery
static uint8_t   s_battery_level = 0;
static bool      s_charging = false;
// Static variables - bluetooth
static bool      s_bt_connected = false;
// Static variables - vibration
static bool      s_vibration = false;
// Static variables - text
static char      s_time_text[] = "00:00";
static char      s_date_text[] = "02 Dec";
static char      s_day_text[] = "Wednesday";
// Static variables - fonts
static GFont     s_clock_font;
static GFont     s_date_font;
static GFont     s_day_font;

/********************************** Handlers *********************************/

// Time handler
static void handle_tick(struct tm* tick_time, TimeUnits units_changed) {
  // Redraw
  if (s_canvas_layer) {
    layer_mark_dirty(s_canvas_layer);
  }
}

// Battery callback
static void battery_callback(BatteryChargeState state) {
  // Record the new battery level
  s_battery_level = state.charge_percent;
  s_charging = state.is_charging;
  
  layer_mark_dirty(s_canvas_layer);
}

// Bluetooth callback
static void bluetooth_callback(bool connected) {
  s_bt_connected = connected;
  
  if(s_vibration)
    vibes_double_pulse();
  layer_mark_dirty(s_canvas_layer);
}

/********************************* Draw Layers *******************************/

static void update_canvas(Layer *layer, GContext *ctx){
  
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 1);
  
  // Draw battery status 
  
  GRect battery_level = GRect(57, 11, 32, 32);
  GRect battery_image = GRect(63, 17, 20, 20);
  
  // Battery icon
  if(s_charging){
    graphics_draw_bitmap_in_rect(ctx, s_battery_ch, battery_image);
  }
  else if(s_battery_level <= 20 && s_battery_level > 10){
    graphics_draw_bitmap_in_rect(ctx, s_battery_low, battery_image);
  }
  else if(s_battery_level <= 10){
    graphics_draw_bitmap_in_rect(ctx, s_battery_very_low, battery_image);
  }
  else{
    graphics_draw_bitmap_in_rect(ctx, s_battery, battery_image);
  }

  // Battery circle
  graphics_context_set_stroke_color(ctx, GColorDarkGray);
  graphics_context_set_stroke_width(ctx, 2);
  if(s_charging){
    graphics_context_set_fill_color(ctx, COLOR_YELLOW);
  }
  else if(s_battery_level <= 20 && s_battery_level > 10){
    graphics_context_set_fill_color(ctx, COLOR_YELLOW);
  }
  else if(s_battery_level <= 10){
    graphics_context_set_fill_color(ctx, GColorRed);
  }
  else {
    graphics_context_set_fill_color(ctx, GColorWhite);
  }
  graphics_draw_circle(ctx, grect_center_point(&battery_level), 14);
  graphics_fill_radial(ctx, battery_level, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE((s_battery_level*360)/100));
  
  // Bluetooth status
  GRect bt_rect = GRect(4, 11, 48, 30);

  if(s_bt_connected){
    graphics_draw_bitmap_in_rect(ctx, s_bt_conn, bt_rect);
    graphics_context_set_stroke_color(ctx, GColorWhite);
  }
  else {
    graphics_draw_bitmap_in_rect(ctx, s_bt_disc, bt_rect);
    graphics_context_set_stroke_color(ctx, GColorDarkGray);
  }
  
  // Bluetooth circle
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_circle(ctx, grect_center_point(&bt_rect), 13);
  
  // Quiet time status
  GRect quiet_rect = GRect(92, 11, 48, 30);
  
  if(quiet_time_is_active()){
    graphics_draw_bitmap_in_rect(ctx, s_quiet_on, quiet_rect);
    graphics_context_set_stroke_color(ctx, GColorDarkGray);
  }
  else {
    graphics_draw_bitmap_in_rect(ctx, s_quiet_off, quiet_rect);
    graphics_context_set_stroke_color(ctx, GColorWhite);
  }
  
  // Quiet status circle
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_circle(ctx, grect_center_point(&quiet_rect), 13);
  
  // Update text
  strftime(s_time_text, sizeof(s_time_text), "%T", tick_time);
  text_layer_set_text(s_time_layer, s_time_text);
  
  strftime(s_date_text, sizeof(s_date_text), "%d %b", tick_time);
  text_layer_set_text(s_date_layer, s_date_text);
  
  strftime(s_day_text, sizeof(s_day_text), "%A", tick_time);
  text_layer_set_text(s_day_layer, s_day_text);
}

/*********************************** Windows *********************************/
static void main_window_load(Window *window) {
  
  // Disable vibration at startup
  s_vibration = false;
  
  // Add custom fonts
  s_clock_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CLOCK_48));
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DATE_22));
  s_day_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DAY_16));
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  
  // Time Layer
  s_time_layer = text_layer_create(GRect(0, 46, bounds.size.w, 52));
  text_layer_set_text_color(s_time_layer, COLOR_YELLOW);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_font(s_time_layer, s_clock_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  // Day Layer
  s_day_layer = text_layer_create(GRect(0, 107, bounds.size.w, 22));
  text_layer_set_text_color(s_day_layer, GColorFromRGB(0, 196, 185));
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_font(s_day_layer, s_day_font);
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentCenter);
  text_layer_set_text(s_day_layer, "Wednesday");
  
  // Date Layer
  s_date_layer = text_layer_create(GRect(0, 130, bounds.size.w, 30));
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_text(s_date_layer, "02 Dec");

  // Bluetooth bitmaps 
  s_bt_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CONNECTED);
  s_bt_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISCONNECTED);
  
  // Quiet Time bitmaps
  s_quiet_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QUIET);
  s_quiet_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIBE);
  
  // Battery bitmaps
  s_battery = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY);
  s_battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW);
  s_battery_very_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_VERY_LOW);
  s_battery_ch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CH);
  
  // Create canvas
  s_canvas_layer = layer_create(bounds);
  layer_set_update_proc(s_canvas_layer, update_canvas);
  
  // Add layers
  layer_add_child(window_layer, s_canvas_layer);
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_day_layer));
  
  // Subscribe to battery service
  battery_state_service_subscribe(battery_callback);

  // Subscribe to bluetooth service
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });

  // Update battery
  battery_callback(battery_state_service_peek());
  
  // Update connection
  bluetooth_callback(connection_service_peek_pebble_app_connection());
  
  // Retrieve time
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  handle_tick(current_time, MINUTE_UNIT);
  // Subscribe to tick handler
  tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
  
  // Enable vibration after startup
  s_vibration = true;
}

static void main_window_unload(Window *window) {
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  connection_service_unsubscribe();
  gbitmap_destroy(s_bt_conn);
  gbitmap_destroy(s_bt_disc);
  gbitmap_destroy(s_quiet_on);
  gbitmap_destroy(s_quiet_off);
  gbitmap_destroy(s_battery);
  gbitmap_destroy(s_battery_low);
  gbitmap_destroy(s_battery_very_low);
  gbitmap_destroy(s_battery_ch);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_day_layer);
  layer_destroy(s_canvas_layer);
  fonts_unload_custom_font(s_clock_font);
  fonts_unload_custom_font(s_date_font);
  fonts_unload_custom_font(s_day_font);
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}