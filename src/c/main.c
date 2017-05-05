#include <pebble.h>

// Persistent storage key
#define SETTINGS_KEY 1

// Define settings struct
typedef struct ClaySettings {
  bool   default_colors;
  char   background_color;
  GColor time_color;
  GColor day_color;
  GColor date_color;
  GColor dial_color;
  char   time_format;
  bool   leading_zero;
  char   time_font_size;
  char   day_font_size;
  char   date_font_size;
} ClaySettings;

// An instance of the struct
static ClaySettings settings;

// Define colors struct
typedef struct ColorSet {
  GColor background_color;
  GColor time_color;
  GColor day_color;
  GColor date_color;
  GColor dial_color;
  GColor dial_off_color;
  GColor battery_low_color;
  GColor battery_very_low_color;
} ColorSet;

// An instance of the struct
static ColorSet s_color_set;

// Define images struct
typedef struct ImageSet {
  GBitmap *bt_conn, *bt_disc;
  GBitmap *quiet_on, *quiet_off;
  GBitmap *battery, *battery_low, *battery_very_low, *battery_ch;
} ImageSet;

// An instance of the struct
static ImageSet s_image_set_std;

// Window
static Window    *s_main_window;
// Layers
static Layer     *s_canvas_layer;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_day_layer;
// Static variables - battery
static uint8_t   s_battery_level = 0;
static bool      s_charging = false;
// Static variables - bluetooth
static bool      s_bt_connected = false;
// Static variables - vibration
static bool      s_vibration = false;
// Static variables - text
static char      h_time[] = "00";
static char      m_time[] = "00";
static char      s_time_text[] = "00:00";
static char      s_date_text[] = "02 Dec";
static char      s_day_text[] = "Wednesday";
// Static variables - fonts
static GFont     s_lato_font_48;
static GFont     s_lato_font_46;
static GFont     s_lato_font_44;
static GFont     s_lato_font_24;
static GFont     s_lato_font_22;
static GFont     s_lato_font_20;
static GFont     s_lato_font_18;
static GFont     s_lato_font_16;

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

// Set colors
static void load_colors() {
  if(settings.default_colors){
    // Standard set
      s_color_set.background_color = GColorBlack;
      s_color_set.time_color = GColorFromRGB(251, 216, 62);
      s_color_set.day_color = GColorFromRGB(0, 196, 185);
      s_color_set.date_color = GColorWhite;
      s_color_set.dial_color = GColorWhite;
      s_color_set.dial_off_color = GColorDarkGray;
      s_color_set.battery_low_color = GColorFromRGB(251, 216, 62);
      s_color_set.battery_very_low_color = GColorRed;
  }
  else {
    switch(settings.background_color){
      case 0:
        // Dark set
        s_color_set.background_color = GColorBlack;
        s_color_set.time_color = settings.time_color;
        s_color_set.day_color = settings.day_color;
        s_color_set.date_color = settings.date_color;
        s_color_set.dial_color = settings.dial_color;
        s_color_set.dial_off_color = GColorDarkGray;
        s_color_set.battery_low_color = GColorOrange;
        s_color_set.battery_very_low_color = GColorDarkCandyAppleRed;
      break;
      case 1:
        // Light set
        s_color_set.background_color = GColorWhite;
        s_color_set.time_color = settings.time_color;
        s_color_set.day_color = settings.day_color;
        s_color_set.date_color = settings.date_color;
        s_color_set.dial_color = settings.dial_color;
        s_color_set.dial_off_color = GColorLightGray;
        s_color_set.battery_low_color = GColorOrange;
        s_color_set.battery_very_low_color = GColorDarkCandyAppleRed;
      break;
      default:
        // Standard set
        s_color_set.background_color = GColorBlack;
        s_color_set.time_color = GColorFromRGB(251, 216, 62);
        s_color_set.day_color = GColorFromRGB(0, 196, 185);
        s_color_set.date_color = GColorWhite;
        s_color_set.dial_color = GColorWhite;
        s_color_set.dial_off_color = GColorDarkGray;
        s_color_set.battery_low_color = GColorFromRGB(251, 216, 62);
        s_color_set.battery_very_low_color = GColorRed;
      break;
    }
  }
}

// Clay interface
// Initialize the default settings
static void prv_default_settings() {
  settings.default_colors = true;
  settings.background_color = 0;
  settings.time_color = GColorWhite;
  settings.day_color = GColorWhite;
  settings.date_color = GColorWhite;
  settings.dial_color = GColorWhite;
  settings.time_format = 0;
  settings.leading_zero = true;
  settings.time_font_size = 2;
  settings.day_font_size = 0;
  settings.date_font_size = 1;
}

// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}

static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  
  // Read time format preferences
  Tuple *time_format_t = dict_find(iter, MESSAGE_KEY_time_format);
  if(time_format_t) {
    settings.time_format = time_format_t->value->uint8 - '0';
  }
  
  Tuple *leading_zero_t = dict_find(iter, MESSAGE_KEY_leading_zero);
  if(leading_zero_t) {
    settings.leading_zero = leading_zero_t->value->int32 == 1;
  }
  
  // Read fonts preferences
  Tuple *time_font_size_t = dict_find(iter, MESSAGE_KEY_time_font);
  if(time_font_size_t) {
    settings.time_font_size = time_font_size_t->value->uint8 - '0';
  }
  
  Tuple *day_font_size_t = dict_find(iter, MESSAGE_KEY_day_font);
  if(day_font_size_t) {
    settings.day_font_size = day_font_size_t->value->uint8 - '0';
  }
  
  Tuple *date_font_size_t = dict_find(iter, MESSAGE_KEY_date_font);
  if(date_font_size_t) {
    settings.date_font_size = date_font_size_t->value->uint8 - '0';
  }
  
  // Read color preferences
  Tuple *default_colors_t = dict_find(iter, MESSAGE_KEY_default_colors);
  if(default_colors_t) {
    settings.default_colors = default_colors_t->value->int32 == 1;
  }
  
  Tuple *background_color_t = dict_find(iter, MESSAGE_KEY_background_color);
  if(background_color_t) {
    settings.background_color = background_color_t->value->uint8 - '0';
  }
  
  Tuple *time_color_t = dict_find(iter, MESSAGE_KEY_time_color);
  if(time_color_t) {
    settings.time_color = GColorFromHEX(time_color_t->value->int32);
  }
  
  Tuple *day_color_t = dict_find(iter, MESSAGE_KEY_day_color);
  if(day_color_t) {
    settings.day_color = GColorFromHEX(day_color_t->value->int32);
  }
  
  Tuple *date_color_t = dict_find(iter, MESSAGE_KEY_date_color);
  if(date_color_t) {
    settings.date_color = GColorFromHEX(date_color_t->value->int32);
  }
  
  Tuple *dial_color_t = dict_find(iter, MESSAGE_KEY_dial_color);
  if(dial_color_t) {
    settings.dial_color = GColorFromHEX(dial_color_t->value->int32);
  }
  
  prv_save_settings();
}

void prv_init(void) {
  // Open AppMessage connection
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
}

/********************************* Draw Layers *******************************/

static void update_canvas(Layer *layer, GContext *ctx){
  
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  
  // Rectangles
  GRect bt_rect = GRect(4, 11, 48, 30);
  GRect quiet_rect = GRect(92, 11, 48, 30);
  GRect battery_level = GRect(57, 11, 32, 32);
  GRect battery_image = GRect(63, 17, 20, 20);

  graphics_context_set_fill_color(ctx, s_color_set.background_color);
  graphics_context_set_stroke_width(ctx, 1);
  graphics_context_set_compositing_mode(ctx, GCompOpSet);

  // Bluetooth status
  graphics_fill_rect(ctx, bt_rect, 0, GCornerNone);
  if(s_bt_connected){
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.bt_conn, bt_rect);
    graphics_context_set_stroke_color(ctx, s_color_set.dial_color);
  }
  else {
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.bt_disc, bt_rect);
    graphics_context_set_stroke_color(ctx, s_color_set.dial_off_color);
  }

  // Bluetooth circle
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_circle(ctx, grect_center_point(&bt_rect), 13);

  // Quiet time status

  graphics_fill_rect(ctx, quiet_rect, 0, GCornerNone);

  if(quiet_time_is_active()){
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.quiet_on, quiet_rect);
    graphics_context_set_stroke_color(ctx, s_color_set.dial_off_color);
  }
  else {
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.quiet_off, quiet_rect);
    graphics_context_set_stroke_color(ctx, s_color_set.dial_color);
  }

  // Quiet status circle
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_circle(ctx, grect_center_point(&quiet_rect), 13);

  // Draw battery status     
  graphics_fill_rect(ctx, battery_level, 0, GCornerNone);
  graphics_fill_rect(ctx, battery_image, 0, GCornerNone);

  // Battery icon
  if(s_charging){
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.battery_ch, battery_image);
  }
  else if(s_battery_level <= 20 && s_battery_level > 10){
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.battery_low, battery_image);
  }
  else if(s_battery_level <= 10){
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.battery_very_low, battery_image);
  }
  else{
    graphics_draw_bitmap_in_rect(ctx, s_image_set_std.battery, battery_image);
  }

  // Battery circle
  graphics_context_set_stroke_color(ctx, s_color_set.dial_off_color);
  graphics_context_set_stroke_width(ctx, 2);
  if(s_charging){
    graphics_context_set_fill_color(ctx, s_color_set.battery_low_color);
  }
  else if(s_battery_level <= 20 && s_battery_level > 10){
    graphics_context_set_fill_color(ctx, s_color_set.battery_low_color);
  }
  else if(s_battery_level <= 10){
    graphics_context_set_fill_color(ctx, s_color_set.battery_very_low_color);
  }
  else {
    graphics_context_set_fill_color(ctx, s_color_set.dial_color);
  }
  graphics_draw_circle(ctx, grect_center_point(&battery_level), 13);
  graphics_fill_radial(ctx, battery_level, GOvalScaleModeFitCircle, 5, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE((s_battery_level*360)/100));
    
  // Update text
  //strftime(s_time_text, sizeof(s_time_text), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  //strftime(s_time_text, sizeof(s_time_text), (settings.time_format == 0) ? "%H:%M" : "%I:%M", tick_time);
  
  strftime(h_time, sizeof(h_time), (settings.time_format == 0) ? "%H" : "%I", tick_time);
  strftime(m_time, sizeof(m_time), "%M", tick_time);
  
  if ((!settings.leading_zero) && (h_time[0] == '0')){
    strcpy(s_time_text, h_time+1);
    strcat(s_time_text, ":");
    strcat(s_time_text, m_time);
  }
  else {
    strcpy(s_time_text, h_time);
    strcat(s_time_text, ":");
    strcat(s_time_text, m_time);
  }

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
  s_lato_font_48 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_48));
  s_lato_font_46 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_46));
  s_lato_font_44 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_44));
  s_lato_font_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_24));
  s_lato_font_22 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_22));
  s_lato_font_20 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_20));
  s_lato_font_18 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_18));
  s_lato_font_16 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_LATO_FONT_16));
  
  // Load images
  if (settings.default_colors){
      // Bluetooth bitmaps
      s_image_set_std.bt_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CONNECTED_STD);
      s_image_set_std.bt_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISCONNECTED_STD);
      // Quiet Time bitmaps
      s_image_set_std.quiet_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QUIET_STD);
      s_image_set_std.quiet_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIBE_STD);
      // Battery bitmaps
      s_image_set_std.battery = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_STD);
      s_image_set_std.battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW_STD);
      s_image_set_std.battery_very_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_VERY_LOW_STD);
      s_image_set_std.battery_ch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CH_STD);
  }
  else{  
    switch(settings.background_color){
      case 0:
        // Bluetooth bitmaps
        s_image_set_std.bt_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CONNECTED_STD);
        s_image_set_std.bt_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISCONNECTED_STD);
        // Quiet Time bitmaps
        s_image_set_std.quiet_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QUIET_STD);
        s_image_set_std.quiet_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIBE_STD);
        // Battery bitmaps
        s_image_set_std.battery = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_STD);
        s_image_set_std.battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW_REV);
        s_image_set_std.battery_very_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_VERY_LOW_REV);
        s_image_set_std.battery_ch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CH_REV);
      break;
      case 1:
        // Bluetooth bitmaps
        s_image_set_std.bt_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CONNECTED_REV);
        s_image_set_std.bt_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISCONNECTED_REV);
        // Quiet Time bitmaps
        s_image_set_std.quiet_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QUIET_REV);
        s_image_set_std.quiet_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIBE_REV);
        // Battery bitmaps
        s_image_set_std.battery = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_REV);
        s_image_set_std.battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW_REV);
        s_image_set_std.battery_very_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_VERY_LOW_REV);
        s_image_set_std.battery_ch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CH_REV);
      break;
      default:
        // Bluetooth bitmaps
        s_image_set_std.bt_conn = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CONNECTED_STD);
        s_image_set_std.bt_disc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DISCONNECTED_STD);
        // Quiet Time bitmaps
        s_image_set_std.quiet_on = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_QUIET_STD);
        s_image_set_std.quiet_off = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIBE_STD);
        // Battery bitmaps
        s_image_set_std.battery = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_STD);
        s_image_set_std.battery_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_LOW_REV);
        s_image_set_std.battery_very_low = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_VERY_LOW_REV);
        s_image_set_std.battery_ch = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CH_REV);
      break;
    }
  }
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  
  // Time Layer
  s_time_layer = text_layer_create(GRect(0, 46, bounds.size.w, 52));
  text_layer_set_text_color(s_time_layer, s_color_set.time_color);
  text_layer_set_background_color(s_time_layer, GColorClear);
  switch (settings.time_font_size){
    case 0:
      text_layer_set_font(s_time_layer, s_lato_font_44);
      break;
    case 1:
      text_layer_set_font(s_time_layer, s_lato_font_46);
      break;
    case 2:
      text_layer_set_font(s_time_layer, s_lato_font_48);
      break;
    default:
      text_layer_set_font(s_time_layer, s_lato_font_48);
      break;
  }
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_text(s_time_layer, "12:34");
  
  // Day Layer
  s_day_layer = text_layer_create(GRect(0, 104, bounds.size.w, 22));
  text_layer_set_text_color(s_day_layer, s_color_set.day_color);
  text_layer_set_background_color(s_day_layer, GColorClear);
  switch (settings.day_font_size){
    case 0:
      text_layer_set_font(s_day_layer, s_lato_font_16);
      break;
    case 1:
      text_layer_set_font(s_day_layer, s_lato_font_18);
      break;
    case 2:
      text_layer_set_font(s_day_layer, s_lato_font_20);
      break;
    default:
      text_layer_set_font(s_day_layer, s_lato_font_16);
      break;
  }
  
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentCenter);
  text_layer_set_text(s_day_layer, "Wednesday");
  
  // Date Layer
  s_date_layer = text_layer_create(GRect(0, 130, bounds.size.w, 30));
  text_layer_set_text_color(s_date_layer, s_color_set.date_color);
  text_layer_set_background_color(s_date_layer, GColorClear);
  switch (settings.date_font_size){
    case 0:
      text_layer_set_font(s_date_layer, s_lato_font_20);
      break;
    case 1:
      text_layer_set_font(s_date_layer, s_lato_font_22);
      break;
    case 2:
      text_layer_set_font(s_date_layer, s_lato_font_24);
      break;
    default:
      text_layer_set_font(s_date_layer, s_lato_font_22);
      break;
  }
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_text(s_date_layer, "02 Dec");
  
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
  gbitmap_destroy(s_image_set_std.bt_conn);
  gbitmap_destroy(s_image_set_std.bt_disc);
  gbitmap_destroy(s_image_set_std.quiet_on);
  gbitmap_destroy(s_image_set_std.quiet_off);
  gbitmap_destroy(s_image_set_std.battery);
  gbitmap_destroy(s_image_set_std.battery_low);
  gbitmap_destroy(s_image_set_std.battery_very_low);
  gbitmap_destroy(s_image_set_std.battery_ch);
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_day_layer);
  layer_destroy(s_canvas_layer);
  fonts_unload_custom_font(s_lato_font_48);
  fonts_unload_custom_font(s_lato_font_46);
  fonts_unload_custom_font(s_lato_font_44);
  fonts_unload_custom_font(s_lato_font_24);
  fonts_unload_custom_font(s_lato_font_22);
  fonts_unload_custom_font(s_lato_font_20);
  fonts_unload_custom_font(s_lato_font_18);
  fonts_unload_custom_font(s_lato_font_16);
}

static void init() {
  prv_load_settings();
  prv_init();
  s_main_window = window_create();
  load_colors();
  window_set_background_color(s_main_window, s_color_set.background_color);
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

