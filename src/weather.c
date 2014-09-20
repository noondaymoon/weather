/*
appmessageを利用した天気取得アプリの作成チュートリアル
http://ninedof.wordpress.com/2014/02/02/pebble-sdk-2-0-tutorial-6-appmessage-for-pebblekit-js/

*/

//ヘッダ登録
#include <pebble.h>

//素材等の定義
Window* window;
TextLayer 	*title_layer,
			*location_layer,
			*temperature_c_layer,
			*temperature_h_layer,
			*temperature_l_layer,
			*condition_layer,
			*time_layer;

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
	text_layer_set_font(layer, fonts_get_system_font(res_id));
	text_layer_set_text_alignment(layer, alignment);
	
	return layer;
}

//appmessageのラベルを定義(参考：http://wisdom.sakura.ne.jp/programming/c/c51.html)
enum {
	KEY_LCT		= 0,
	KEY_C_TMP	= 1,
	KEY_H_TMP	= 2,
	KEY_L_TMP	= 3,
	KEY_CND		= 4
};

//テキスト表示に使う変数の文字数も含めた定義
char 	location_buffer[64],
		temperature_c_buffer[32],
		temperature_h_buffer[32],
		temperature_l_buffer[32],
		condition_buffer[64],
		time_buffer[32];

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
		snprintf (location_buffer, sizeof("Location : couldbereallylongname"), "Location: %s", string_value);
		//snprintf（参考:http://www.c-tipsref.com/reference/stdio/snprintf.html）
		text_layer_set_text(location_layer, (char*) &location_buffer);
		break;
		
		case KEY_C_TMP:
		//気温を取得した場合
		snprintf(temperature_c_buffer, sizeof("Temperature: XX \u00B0C"), "Temperature: %d \u00B0C", value);
		//"\u00b0C"は"\u"(ユニコード)+"00b0"(気温の◯記号)+"C"(celcious)というコトで"℃"を構成
		text_layer_set_text(temperature_c_layer, (char*) &temperature_c_buffer);
		break;
		
		case KEY_H_TMP:
		snprintf(temperature_h_buffer, sizeof("Temperature_h: XX \u00B0C"), "high: %d \u00B0C", value);
		text_layer_set_text(temperature_h_layer, (char*) &temperature_h_buffer);
		break;
		
		case KEY_L_TMP:
		snprintf(temperature_l_buffer, sizeof("Temperature_l: XX \u00B0C"), "low: %d \u00B0C", value);
		text_layer_set_text(temperature_l_layer, (char*) &temperature_l_buffer);
		break;
		
		case KEY_CND:
		//天候を取得
		snprintf (condition_buffer, sizeof("Condition : couldbereallylongname"), "Condition: %s", string_value);
		text_layer_set_text(condition_layer, (char*) &condition_buffer);
		break;
		
	}
	
	// tに関する動作ここまで
	// ついでに時間を取得
	time_t temp = time(NULL);
	struct tm *tm = localtime (&temp);
	strftime (time_buffer, sizeof("Last updated: XX:XX"), "last updated: %H:%M", tm);
	text_layer_set_text(time_layer, (char*) &time_buffer);
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
	title_layer = init_text_layer(GRect(5, 0, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(title_layer, "Openweathermap.org");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(title_layer));
	
	location_layer = init_text_layer(GRect(5, 20, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(location_layer, "Location: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(location_layer));
	
	temperature_c_layer = init_text_layer(GRect(5, 40, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(temperature_c_layer, "Temperature: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(temperature_c_layer));
	
	temperature_h_layer = init_text_layer(GRect(5, 60, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(temperature_h_layer, "Last updated: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(temperature_h_layer));
	
	temperature_l_layer = init_text_layer(GRect(5, 80, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(temperature_l_layer, "Last updated: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(temperature_l_layer));
	
	condition_layer = init_text_layer(GRect(5, 100, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(condition_layer, "Condition: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(condition_layer));
	
	time_layer = init_text_layer(GRect(5, 120, 144, 20), GColorBlack, GColorClear, "RESOURCE_ID_GOTHIC_18", GTextAlignmentLeft);
	text_layer_set_text(time_layer, "Last updated: N/A");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));

}

//windows素材の撤収
void window_unload (Window *window)
	{
	text_layer_destroy(title_layer);
	text_layer_destroy(location_layer);
	text_layer_destroy(temperature_c_layer);
	text_layer_destroy(temperature_h_layer);
	text_layer_destroy(temperature_l_layer);
	text_layer_destroy(condition_layer);
	text_layer_destroy(time_layer);	
}

//windowの表示を構成
void init()
	{
	window = window_create();
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