/*
appmessageを利用した天気取得アプリの作成チュートリアル
http://ninedof.wordpress.com/2014/02/02/pebble-sdk-2-0-tutorial-6-appmessage-for-pebblekit-js/
からの改変
*/

#include <pebble.h>

static Window *window;
static TextLayer *location_layer;
static TextLayer *condition1_layer;
static TextLayer *time2_layer, *time3_layer,  *time4_layer;
static TextLayer *temperature1_layer, *temperature2_layer, *temperature3_layer, *temperature4_layer;
static BitmapLayer *icon1_layer, *icon2_layer, *icon3_layer, *icon4_layer;
static BitmapLayer *tmpm_layer;

//appmessageのラベルを定義(参考：http://wisdom.sakura.ne.jp/programming/c/c51.html)
enum {
	KEY_LCT		= 0,
	KEY_TMP1	= 1,
	KEY_ICON1	= 2,
	KEY_CND1	= 3,
	KEY_TMP2	= 4,
	KEY_ICON2	= 5,
	KEY_TIME2	= 6,
	KEY_TMP3	= 7,
	KEY_ICON3	= 8,
	KEY_TIME3	= 9,
	KEY_TMP4	= 10,
	KEY_ICON4	= 11,
	KEY_TIME4	= 12,

};

//テキスト表示に使う変数の文字数も含めた定義
char 	location_buffer		[32],
		temperature1_buffer	[8],
		icon1_buffer		[4],
		condition1_buffer	[64],
		temperature2_buffer	[8],
		icon2_buffer		[4],
		time2_buffer		[5],
		temperature3_buffer	[8],
		icon3_buffer		[4],
		time3_buffer		[5],
		temperature4_buffer	[8],
		icon4_buffer		[4],
		time4_buffer		[5];

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
		
		//場所を取得した場合
		case KEY_LCT:
		snprintf (location_buffer, sizeof("Location : couldbereallylongname"), "%s", string_value);
		//snprintf（参考:http://www.c-tipsref.com/reference/stdio/snprintf.html）
		text_layer_set_text(location_layer, (char*) &location_buffer);
		//text_layer_set_text(location_layer, "location"); //スクショ用
		
		//jsからのデータの処理が終わったらタイミングで画像を同時に配置する
		bitmap_layer_set_bitmap(tmpm_layer, gbitmap_create_with_resource(RESOURCE_ID_TMPM));
		break;
		
		//天候を取得
		case KEY_CND1:
		snprintf (condition1_buffer, sizeof("Condition : couldbereallylongname"), "%s", string_value);
		text_layer_set_text(condition1_layer, (char*) &condition1_buffer);
		break;
		
		/*
		取得するiconの値をそのままコードに代入したい。できない。
		
		case KEY_ICON1:
		snprintf (icon1_buffer, sizeof("xxx"), "%s", string_value);
		
		bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(icon1_buffer));
		break;
		*/
		
		
		//アスキーコードに変換してやればイケる気がする。
		/*
		case KEY_ICON1:
		//snprintf (icon1_buffer, sizeof("xxx"), "%s", string_value);
		snprintf (icon1_buffer, sizeof("xxx"), "042", value);
		bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(icon1_buffer));
		break;
		*/
		
		
		case KEY_ICON1:
		snprintf (icon1_buffer, sizeof("xxx"), "%s", string_value);
		if (strcmp(icon1_buffer, "01d") == 0){ 
			//strcmp(a,b) == 0/1 : 文字列aとbが一致しているかどうかを判断。
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01d));}
		else if (strcmp(icon1_buffer, "02d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02d));}
		else if (strcmp(icon1_buffer, "03d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03d));}
		else if (strcmp(icon1_buffer, "04d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04d));}
		else if (strcmp(icon1_buffer, "09d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09d));}
		else if (strcmp(icon1_buffer, "10d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10d));}
		else if (strcmp(icon1_buffer, "11d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11d));}
		else if (strcmp(icon1_buffer, "13d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13d));}
		else if (strcmp(icon1_buffer, "50d") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50d));}
		else if (strcmp(icon1_buffer, "01n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01n));}
		else if (strcmp(icon1_buffer, "02n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02n));}
		else if (strcmp(icon1_buffer, "03n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03n));}
		else if (strcmp(icon1_buffer, "04n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04n));}
		else if (strcmp(icon1_buffer, "09n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09n));}
		else if (strcmp(icon1_buffer, "10n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10n));}
		else if (strcmp(icon1_buffer, "11n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11n));}
		else if (strcmp(icon1_buffer, "13n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13n));}
		else if (strcmp(icon1_buffer, "50n") == 0){
			bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50n));}
		else {bitmap_layer_set_bitmap(icon1_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_EX));}
		break;
		
		
		case KEY_ICON2:
		snprintf (icon2_buffer, sizeof("xxx"), "%s", string_value);
		if (strcmp(icon2_buffer, "01d") == 0){ 
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01d));}
		else if (strcmp(icon2_buffer, "02d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02d));}
		else if (strcmp(icon2_buffer, "03d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03d));}
		else if (strcmp(icon2_buffer, "04d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04d));}
		else if (strcmp(icon2_buffer, "09d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09d));}
		else if (strcmp(icon2_buffer, "10d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10d));}
		else if (strcmp(icon2_buffer, "11d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11d));}
		else if (strcmp(icon2_buffer, "13d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13d));}
		else if (strcmp(icon2_buffer, "50d") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50d));}
		else if (strcmp(icon2_buffer, "01n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01n));}
		else if (strcmp(icon2_buffer, "02n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02n));}
		else if (strcmp(icon2_buffer, "03n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03n));}
		else if (strcmp(icon2_buffer, "04n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04n));}
		else if (strcmp(icon2_buffer, "09n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09n));}
		else if (strcmp(icon2_buffer, "10n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10n));}
		else if (strcmp(icon2_buffer, "11n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11n));}
		else if (strcmp(icon2_buffer, "13n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13n));}
		else if (strcmp(icon2_buffer, "50n") == 0){
			bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50n));}
		else {bitmap_layer_set_bitmap(icon2_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_EX));}
		break;
		
		case KEY_ICON3:
		snprintf (icon3_buffer, sizeof("xxx"), "%s", string_value);
		if (strcmp(icon3_buffer, "01d") == 0){ 
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01d));}
		else if (strcmp(icon3_buffer, "02d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02d));}
		else if (strcmp(icon3_buffer, "03d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03d));}
		else if (strcmp(icon3_buffer, "04d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04d));}
		else if (strcmp(icon3_buffer, "09d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09d));}
		else if (strcmp(icon3_buffer, "10d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10d));}
		else if (strcmp(icon3_buffer, "11d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11d));}
		else if (strcmp(icon3_buffer, "13d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13d));}
		else if (strcmp(icon3_buffer, "50d") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50d));}
		else if (strcmp(icon3_buffer, "01n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01n));}
		else if (strcmp(icon3_buffer, "02n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02n));}
		else if (strcmp(icon3_buffer, "03n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03n));}
		else if (strcmp(icon3_buffer, "04n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04n));}
		else if (strcmp(icon3_buffer, "09n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09n));}
		else if (strcmp(icon3_buffer, "10n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10n));}
		else if (strcmp(icon3_buffer, "11n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11n));}
		else if (strcmp(icon3_buffer, "13n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13n));}
		else if (strcmp(icon3_buffer, "50n") == 0){
			bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50n));}
		else {bitmap_layer_set_bitmap(icon3_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_EX));}
		break;
		
		case KEY_ICON4:
		snprintf (icon4_buffer, sizeof("xxx"), "%s", string_value);
		if (strcmp(icon4_buffer, "01d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01d));}
		else if (strcmp(icon4_buffer, "02d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02d));}
		else if (strcmp(icon4_buffer, "03d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03d));}
		else if (strcmp(icon4_buffer, "04d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04d));}
		else if (strcmp(icon4_buffer, "09d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09d));}
		else if (strcmp(icon4_buffer, "10d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10d));}
		else if (strcmp(icon4_buffer, "11d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11d));}
		else if (strcmp(icon4_buffer, "13d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13d));}
		else if (strcmp(icon4_buffer, "50d") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50d));}
		else if (strcmp(icon4_buffer, "01n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_01n));}
		else if (strcmp(icon4_buffer, "02n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_02n));}
		else if (strcmp(icon4_buffer, "03n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_03n));}
		else if (strcmp(icon4_buffer, "04n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_04n));}
		else if (strcmp(icon4_buffer, "09n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_09n));}
		else if (strcmp(icon4_buffer, "10n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_10n));}
		else if (strcmp(icon4_buffer, "11n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_11n));}
		else if (strcmp(icon4_buffer, "13n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_13n));}
		else if (strcmp(icon4_buffer, "50n") == 0){
			bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_50n));}
		else {bitmap_layer_set_bitmap(icon4_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_EX));}
		break;
		
		
		//気温を取得した場合
		case KEY_TMP1:
		snprintf(temperature1_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
		//"\u00b0C"は"\u"(ユニコード)+"00b0"(気温の◯記号)+"C"(celcious)というコトで"℃"を構成
		text_layer_set_text(temperature1_layer, (char*) &temperature1_buffer);
		break;
		
		case KEY_TMP2:
		snprintf(temperature2_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
		text_layer_set_text(temperature2_layer, (char*) &temperature2_buffer);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, (char*) &temperature2_buffer);
		break;
		
		case KEY_TMP3:
		snprintf(temperature3_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
		text_layer_set_text(temperature3_layer, (char*) &temperature3_buffer);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, (char*) &temperature3_buffer);
		break;
		
		case KEY_TMP4:
		snprintf(temperature4_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
		text_layer_set_text(temperature4_layer, (char*) &temperature4_buffer);
		break;
		
		//時刻を取得した場合
		case KEY_TIME2:
		snprintf(time2_buffer, sizeof("xx:xx"), "%s", string_value);
		text_layer_set_text(time2_layer, (char*) &time2_buffer);
		break;
		
		case KEY_TIME3:
		snprintf(time3_buffer, sizeof("xx:xx"), "%s", string_value);
		text_layer_set_text(time3_layer, (char*) &time3_buffer);
		break;
		
		case KEY_TIME4:
		snprintf(time4_buffer, sizeof("xx:xx"), "%s", string_value);
		text_layer_set_text(time4_layer, (char*) &time4_buffer);
		break;
		
	}
	
	
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
	
	// location_layer
  	location_layer = text_layer_create(GRect(5, 2, 144, 30));
  	text_layer_set_background_color(location_layer, GColorClear);
  	text_layer_set_text_color(location_layer, GColorWhite);
  	text_layer_set_font(location_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_22)));
  	text_layer_set_text(location_layer, "loading...");
	layer_add_child(window_get_root_layer(window), (Layer *)location_layer);
	
	// icon1_layer
  	icon1_layer = bitmap_layer_create(GRect(6, 38, 48, 36));
	bitmap_layer_set_alignment(icon1_layer, GAlignLeft);
  	layer_add_child(window_get_root_layer(window), (Layer *)icon1_layer);
	
	//condition1_layer
	condition1_layer = text_layer_create(GRect(48, 33, 98, 20));
  	text_layer_set_background_color(condition1_layer, GColorClear);
 	text_layer_set_text_color(condition1_layer, GColorWhite);
  	text_layer_set_font(condition1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_14)));
  	layer_add_child(window_get_root_layer(window), (Layer *)condition1_layer);
  
	//tmpm_layer
	tmpm_layer = bitmap_layer_create(GRect(47, 54, 14, 14));
	bitmap_layer_set_background_color(tmpm_layer, GColorClear);
	layer_add_child(window_get_root_layer(window), (Layer *)tmpm_layer);
	
  	// temperature1_layer
  	temperature1_layer = text_layer_create(GRect(70, 55, 70, 18));
  	text_layer_set_background_color(temperature1_layer, GColorClear);
  	text_layer_set_text_color(temperature1_layer, GColorWhite);
  	text_layer_set_font(temperature1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	layer_add_child(window_get_root_layer(window), (Layer *)temperature1_layer);
  
	// time2_layer
	time2_layer = text_layer_create(GRect(0, 82, 48, 18));
	text_layer_set_background_color(time2_layer, GColorClear);
	text_layer_set_text_color(time2_layer, GColorWhite);
	text_layer_set_font(time2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(time2_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)time2_layer);
	
	// icon2_layer
  	icon2_layer = bitmap_layer_create(GRect(0, 98, 48, 36));
	bitmap_layer_set_alignment(icon2_layer, GAlignCenter);
  	layer_add_child(window_get_root_layer(window), (Layer *)icon2_layer);
	
	// temperature2_layer
  	temperature2_layer = text_layer_create(GRect(0, 136, 48, 18));
  	text_layer_set_background_color(temperature2_layer, GColorClear);
  	text_layer_set_text_color(temperature2_layer, GColorWhite);
	text_layer_set_font(temperature2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(temperature2_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)temperature2_layer);
	
	// time3_layer
	time3_layer = text_layer_create(GRect(48, 82, 48, 18));
	text_layer_set_background_color(time3_layer, GColorClear);
	text_layer_set_text_color(time3_layer, GColorWhite);
	text_layer_set_font(time3_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(time3_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)time3_layer);
	
	// icon3_layer
  	icon3_layer = bitmap_layer_create(GRect(48, 98, 48, 36));
	bitmap_layer_set_alignment(icon3_layer, GAlignCenter);
  	layer_add_child(window_get_root_layer(window), (Layer *)icon3_layer);
	
	// temperature3_layer
  	temperature3_layer = text_layer_create(GRect(48, 136, 48, 18));
  	text_layer_set_background_color(temperature3_layer, GColorClear);
  	text_layer_set_text_color(temperature3_layer, GColorWhite);
	text_layer_set_font(temperature3_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(temperature3_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)temperature3_layer);
	
	// time4_layer
	time4_layer = text_layer_create(GRect(96, 82, 48, 18));
	text_layer_set_background_color(time4_layer, GColorClear);
	text_layer_set_text_color(time4_layer, GColorWhite);
	text_layer_set_font(time4_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(time4_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)time4_layer);
	
	// icon4_layer
  	icon4_layer = bitmap_layer_create(GRect(96, 98, 48, 36));
	bitmap_layer_set_alignment(icon4_layer, GAlignCenter);
  	layer_add_child(window_get_root_layer(window), (Layer *)icon4_layer);
	
	// temperature4_layer
  	temperature4_layer = text_layer_create(GRect(96, 136, 48, 18));
  	text_layer_set_background_color(temperature4_layer, GColorClear);
  	text_layer_set_text_color(temperature4_layer, GColorWhite);
	text_layer_set_font(temperature4_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_12)));
  	text_layer_set_text_alignment(temperature4_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)temperature4_layer);
	
}

//windows素材の撤収
void window_unload (Window *window)
	{
	text_layer_destroy(location_layer);
	bitmap_layer_destroy(tmpm_layer);
	text_layer_destroy(condition1_layer);
	
	bitmap_layer_destroy(icon1_layer);
	text_layer_destroy(temperature1_layer);
		
	bitmap_layer_destroy(icon2_layer);
  	text_layer_destroy(temperature2_layer);
	text_layer_destroy(time2_layer);
	
	bitmap_layer_destroy(icon3_layer);
  	text_layer_destroy(temperature3_layer);
	text_layer_destroy(time3_layer);
	
	bitmap_layer_destroy(icon4_layer);
  	text_layer_destroy(temperature4_layer);
	text_layer_destroy(time4_layer);
	
}

//windowの表示を構成
void init()
	{
	//コピペ
	window = window_create();
  	window_set_background_color(window, GColorBlack);
 	window_set_fullscreen(window, false);
	
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

void deinit ()
	{
	window_destroy (window);
}

int main (void)
	{
	init();
	app_event_loop();
	deinit();
}