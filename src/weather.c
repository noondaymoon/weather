/*
appmessageを利用した天気取得アプリの作成チュートリアル
http://ninedof.wordpress.com/2014/02/02/pebble-sdk-2-0-tutorial-6-appmessage-for-pebblekit-js/

*/

//ヘッダ登録
#include <pebble.h>

//素材等の定義


static Window *window;
static TextLayer *condition1_layer;
static TextLayer *temperature1_layer;
static BitmapLayer *icon1_layer;
static BitmapLayer *tmpm_layer;
static TextLayer *location_layer;

/*
Window* window;
TextLayer 	*location_layer,
			*condition1_layer,
			*temperature1_layer;

BitmapLayer	*icon1_layer;


//テキストレイヤをまとめて定義

static TextLayer* init_text_layer(
		GRect location,
		GColor colour,
		GColor background,
		const char *res_id,
		GTextAlignment alignment)
	{
	TextLayer *layer = text_layer_create(location);
	text_layer_set_text_color(layer, colour);
	text_layer_set_background_color(layer, background);
	//text_layer_set_font(layer, fonts_get_system_font(res_id));
	text_layer_set_text_alignment(layer, alignment);
	
	return layer;
}
*/

//appmessageのラベルを定義(参考：http://wisdom.sakura.ne.jp/programming/c/c51.html)
enum {
	KEY_LCT		= 0,
	KEY_TMP1	= 1,
	KEY_ICON1	= 2,
	KEY_CND1	= 3

};

//テキスト表示に使う変数の文字数も含めた定義
char 	location_buffer[64],
		temperature1_buffer[32],
		icon1_buffer[32],
		condition1_buffer[64];

//変数の定義ここまで

//関数の記述


//appmessageよりtに収納された情報の処理
void process_tuple(Tuple *t)
	{
	int key = t->key; //keyを取得
	int value = t->value->int32; //数値の場合は数値として取得
	char string_value[32];
	strcpy (string_value, t->value->cstring); //文字列の場合は文字列として取得
	//"strcpy"はstringをコピーする記述
	
	//ここから動作
	switch (key) {
		case KEY_LCT:
		//場所を取得した場合
		snprintf (location_buffer, sizeof("Location : couldbereallylongname"), "%s", string_value);
		//snprintf（参考:http://www.c-tipsref.com/reference/stdio/snprintf.html）
		text_layer_set_text(location_layer, (char*) &location_buffer);
		break;
		
		case KEY_TMP1:
		//気温を取得した場合
		snprintf(temperature1_buffer, sizeof("Temperature: XX \u00B0C"), "%d \u00B0C", value);
		//"\u00b0C"は"\u"(ユニコード)+"00b0"(気温の◯記号)+"C"(celcious)というコトで"℃"を構成
		text_layer_set_text(temperature1_layer, (char*) &temperature1_buffer);
		break;
		
		case KEY_ICON1:
		if (strcmp(icon1_buffer, "01d") == 0){ //strcmp(a,b) == 0/1 : 文字列aとbが一致しているかどうかを判断。t/f。
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01D));}
		else if (strcmp(icon1_buffer, "02d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02D));}
		else if (strcmp(icon1_buffer, "03d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03D));}
		else if (strcmp(icon1_buffer, "04d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04D));}
		else if (strcmp(icon1_buffer, "09d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09D));}
		else if (strcmp(icon1_buffer, "10d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10D));}
		else if (strcmp(icon1_buffer, "11d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11D));}
		else if (strcmp(icon1_buffer, "13d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13D));}
		else if (strcmp(icon1_buffer, "50d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50D));}
		else if (strcmp(icon1_buffer, "01n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01N));}
		else if (strcmp(icon1_buffer, "02n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02N));}
		else if (strcmp(icon1_buffer, "03n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03N));}
		else if (strcmp(icon1_buffer, "04n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04N));}
		else if (strcmp(icon1_buffer, "09n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09N));}
		else if (strcmp(icon1_buffer, "10n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10N));}
		else if (strcmp(icon1_buffer, "11n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11N));}
		else if (strcmp(icon1_buffer, "13n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13N));}
		else if (strcmp(icon1_buffer, "50n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50N));}
		else {bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_EX));}
		break;
		
		case KEY_CND1:
		//天候を取得
		snprintf (condition1_buffer, sizeof("Condition : couldbereallylongname"), "%s", string_value);
		text_layer_set_text(condition1_layer, (char*) &condition1_buffer);
		break;
		
	}
	
	// tに関する動作ここまで
	// ついでに時間を取得

}

//appmessageの取り出し
static void in_received_handler (DictionaryIterator *iter, void *context)
	{
	(void) context;
	
	//データを取得し"t"に構造体として収納する
	Tuple *t = dict_read_first(iter); //iterの中にある一番最初のmessageを見に行く
	while (t!= NULL) //以下のジョブをmessageからnullが返ってくるまで繰り返す
		{
		process_tuple(t); //messageの最初のヤツをtに収納
		t = dict_read_next(iter); //次のヤツを同様にtに収納
		
	}
}



//windowに素材を配置
void window_load (Window *window)
	{
	
	//condition1_layer
	condition1_layer = text_layer_create(GRect(47, 38, 90, 18));
  	text_layer_set_background_color(condition1_layer, GColorClear);
 	text_layer_set_text_color(condition1_layer, GColorWhite);
  	text_layer_set_font(condition1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	layer_add_child(window_get_root_layer(window), (Layer *)condition1_layer);
  
  	// temperature1_layer
  	temperature1_layer = text_layer_create(GRect(67, 55, 70, 18));
  	text_layer_set_background_color(temperature1_layer, GColorClear);
  	text_layer_set_text_color(temperature1_layer, GColorWhite);
  	text_layer_set_font(temperature1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	layer_add_child(window_get_root_layer(window), (Layer *)temperature1_layer);
  
  	// icon1_layer
  	icon1_layer = bitmap_layer_create(GRect(6, 38, 36, 36));
  	layer_add_child(window_get_root_layer(window), (Layer *)icon1_layer);

	//tmpm_layer
	tmpm_layer = bitmap_layer_create(GRect(47, 54, 14, 14));
	bitmap_layer_set_background_color(tmpm_layer, GColorClear);
	bitmap_layer_set_bitmap(tmpm_layer, gbitmap_create_with_resource(RESOURCE_ID_TMPM));
	layer_add_child(window_get_root_layer(window), (Layer *)tmpm_layer);
	
  	// location_layer
  	location_layer = text_layer_create(GRect(5, 5, 100, 24));
  	text_layer_set_background_color(location_layer, GColorClear);
  	text_layer_set_text_color(location_layer, GColorWhite);
  	text_layer_set_font(location_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_18)));
  	layer_add_child(window_get_root_layer(window), (Layer *)location_layer);
	
	/*
	location_layer = init_text_layer(GRect(10, 5, 100, 25), GColorWhite, GColorClear, "RESOURCE_ID_FONT_DROID_18", GTextAlignmentLeft);
	text_layer_set_text(location_layer, "loading...");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(location_layer));
	
	temperature1_layer = init_text_layer(GRect(84, 60, 50, 20), GColorWhite, GColorClear, "RESOURCE_ID_FONT_DROID_12", GTextAlignmentLeft);
	text_layer_set_text(temperature1_layer, "");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(temperature1_layer));

	condition1_layer = init_text_layer(GRect(68, 38, 74, 17), GColorWhite, GColorClear, "RESOURCE_ID_FONT_DROID_12", GTextAlignmentLeft);
	text_layer_set_text(condition1_layer, "");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(condition1_layer));

	icon1_layer = bitmap_layer_create(GRect(10, 80, 36, 36));
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(icon1_layer));
	*/
}

//windows素材の撤収
void window_unload (Window *window)
	{
	
	window_destroy(window);
  	text_layer_destroy(condition1_layer);
  	text_layer_destroy(temperature1_layer);
  	bitmap_layer_destroy(icon1_layer);
	bitmap_layer_destroy(tmpm_layer);
  	text_layer_destroy(location_layer);
	
	/*
	text_layer_destroy(location_layer);
	text_layer_destroy(temperature1_layer);
	text_layer_destroy(condition1_layer);
	bitmap_layer_destroy(icon1_layer);
	*/
}

//windowの表示を構成
void init()
	{
	//コピペ
	window = window_create();
  	window_set_background_color(window, GColorBlack);
 	window_set_fullscreen(window, false);

/*
	window = window_create();
	window_set_background_color(window, GColorBlack);
*/
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload,
	};
	window_set_window_handlers(window, handlers);
	
	//appmessage eventsを登録
	app_message_register_inbox_received(in_received_handler);
	app_message_open (app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
		//appmessageの最大入出力数
	
	window_stack_push(window, true);
}

//window表示を撤収
void deinit ()
	{
	window_destroy (window);
}

//関数の記述ここまで

int main (void)
	{
	init();
	app_event_loop();
	deinit();
}