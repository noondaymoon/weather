#include <pebble.h>
static Window *window;
static TextLayer *location_layer;
static TextLayer *condition1_layer;
static TextLayer *time2_layer, *time3_layer,  *time4_layer;
static TextLayer *temperature1_layer, *temperature2_layer, *temperature3_layer, *temperature4_layer;
static BitmapLayer *icon1_layer, *icon2_layer, *icon3_layer, *icon4_layer;
static BitmapLayer *bg_layer, *tmpm_layer;


//appmessageのラベルを定義(参考：http://wisdom.sakura.ne.jp/programming/c/c51.html)
enum {
	KEY_UNIT	= 0,
	KEY_LCT		= 1,
	KEY_TMP1	= 2,
	KEY_ICON1	= 3,
	KEY_CND1	= 4,
	KEY_TMP2	= 5,
	KEY_ICON2	= 6,
	KEY_TIME2	= 7,
	KEY_TMP3	= 8,
	KEY_ICON3	= 9,
	KEY_TIME3	= 10,
	KEY_TMP4	= 11,
	KEY_ICON4	= 12,
	KEY_TIME4	= 13,
};

//テキスト表示に使う変数の文字数も含めた定義
char 	location_buffer		[32], //[+]16文字以上の地域があるので修正
		tmp1_buffer			[8],
		icon1_buffer		[4],
		condition1_buffer	[16],
		tmp2_buffer			[8],
		icon2_buffer		[4],
		time2_buffer		[8],
		hour2_buffer		[4],
		tmp3_buffer			[8],
		icon3_buffer		[4],
		time3_buffer		[8],
		hour3_buffer		[4],
		tmp4_buffer			[8],
		icon4_buffer		[4],
		time4_buffer		[8],
		tempunit			[4],
		hour4_buffer		[4];

static void acceltap (void) {
	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);
	
	if (iter == NULL) {
		return;
	}
	
	app_message_outbox_send();
}


//appmessageよりtに収納された情報の処理
void process_tuple(Tuple *t)
	{
	int key = t->key; //keyを取得
	int value = t->value->int32; //数値の場合は数値として取得
	char string_value[16];
	strcpy (string_value, t->value->cstring); //文字列の場合は文字列として取得
	//"strcpy"はstringをコピーする記述
		
	//ここからdictより取得した値に対応する動作
	switch (key) {
		
		case KEY_UNIT:
		snprintf (tempunit, sizeof("x"), "%s", string_value);
		break;
		
		//場所を取得した場合
		case KEY_LCT:
		snprintf (location_buffer, sizeof("xxxxxxxxxxxxxx"), "%s", string_value); //[+]文字列サイズ延長
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
		取得するiconの値をそのままコードに代入したいんだケド、できない。
		できたら以下のiconに関するステップが一気に減らせるのに。
		
		イイ案を見つけるまでここは放置する。
		*/
		
		/*
		//作業中。任意の変数にアイコンID代入してif文を一掃する作戦
		js側でアイコンidの数字と昼夜判定を切り離して別のkeyで送り出せばどうだろう？
		tmpx_bufferの表示部(char*)&の記述を使えそう
		
		case KEY_ICON1:
		snprintf (icon1_buffer, sizeof("xxx"), "%s", string_value);
		
		APP_LOG(APP_LOG_LEVEL_INFO, "icon1_buffer: %s", icon1_buffer);
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
		if(strcmp(tempunit, "F") == 0){
			double tmp1f = (((9.0/5.0)*value)+32.0);
			snprintf(tmp1_buffer, sizeof("XXXX \u00B0F"), "%d \u00B0F", (int)tmp1f);
			text_layer_set_text(temperature1_layer, (char*) &tmp1_buffer);
		}
		else{
			snprintf(tmp1_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
			//"\u00b0C"は"\u"(ユニコード)+"00b0"(気温の◯記号)+"C"(celcious)というコトで"℃"を構成
			text_layer_set_text(temperature1_layer, (char*) &tmp1_buffer);
		}
		break;
		
		case KEY_TMP2:
		if(strcmp(tempunit, "F") == 0){
			double tmp2f = (((9.0/5.0)*value)+32.0);			
			snprintf(tmp2_buffer, sizeof("XXXX \u00B0F"), "%d \u00B0F", (int)tmp2f);
			text_layer_set_text(temperature2_layer, (char*) &tmp2_buffer);
		}
		else{
			snprintf(tmp2_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
			text_layer_set_text(temperature2_layer, (char*) &tmp2_buffer);
		}
		break;
		
		case KEY_TMP3:
		if(strcmp(tempunit, "F") == 0){
			double tmp3f = (((9.0/5.0)*value)+32.0);			
			snprintf(tmp3_buffer, sizeof("XXXX \u00B0F"), "%d \u00B0F", (int)tmp3f);
			text_layer_set_text(temperature3_layer, (char*) &tmp3_buffer);
		}
		else{
			snprintf(tmp3_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
			text_layer_set_text(temperature3_layer, (char*) &tmp3_buffer);
		}
		break;
		
		case KEY_TMP4:
		if(strcmp(tempunit, "F") == 0){
			double tmp4f = (((9.0/5.0)*value)+32.0);			
			snprintf(tmp4_buffer, sizeof("XXXX \u00B0F"), "%d \u00B0F", (int)tmp4f);
			text_layer_set_text(temperature4_layer, (char*) &tmp4_buffer);
		}
		else{
			snprintf(tmp4_buffer, sizeof("XXXX \u00B0C"), "%d \u00B0C", value);
			text_layer_set_text(temperature4_layer, (char*) &tmp4_buffer);
		}
		break;
		
		//時刻を取得した場合
		case KEY_TIME2:
		
		snprintf(hour2_buffer, sizeof("xx"), "%d", value);
		
		if (!clock_is_24h_style()){			
			int hour2 = atoi(hour2_buffer);
			int hour12_2 = 12;
			if		(hour2 == 0) {snprintf(time2_buffer, sizeof("xx:xxx"),"%d:00a", hour12_2);}
			else if (hour2 < 12 && hour2 > 0){snprintf(time2_buffer, sizeof("xx:xxx"),"%d:00a", hour2);}
			else if (hour2 == 12) {snprintf(time2_buffer, sizeof("xx:xxx"),"%d:00p", hour12_2);}
			else {
				int hour2_12 = hour2-12;
				snprintf(time2_buffer, sizeof("xx:xxx"),"%d:00p", hour2_12);
			}
		}
		
		else {
			if (value < 10){
				char dhour2[] = "0";
				strcpy(time2_buffer, dhour2);
				strcat(time2_buffer, hour2_buffer);
			}
			else{
				strcpy(time2_buffer, hour2_buffer);
			}
			strcat(time2_buffer, ":00");
		}
		
		text_layer_set_text(time2_layer, (char*) &time2_buffer);
		break;
		
		case KEY_TIME3:
		snprintf(hour3_buffer, sizeof("xx"), "%d", value);
		
		if (!clock_is_24h_style()) {			
			int hour3 = atoi(hour3_buffer);
			int hour12_3 = 12;
			if		(hour3 == 0) {snprintf(time3_buffer, sizeof("xx:xxx"),"%d:00a", hour12_3);}
			else if (hour3 < 12 && hour3 > 0){snprintf(time3_buffer, sizeof("xx:xxx"),"%d:00a", hour3);}
			else if (hour3 == 12) {snprintf(time3_buffer, sizeof("xx:xxx"),"%d:00p", hour12_3);}
			else {
				int hour3_12 = hour3-12;
				snprintf(time3_buffer, sizeof("xx:xxx"),"%d:00p", hour3_12);
			}
		}
		
		else {
			if (value < 10){
				char dhour3[] = "0";
				strcpy(time3_buffer, dhour3);
				strcat(time3_buffer, hour3_buffer);
			}
			else{
				strcpy(time3_buffer, hour3_buffer);
			}
			strcat(time3_buffer, ":00");
		}
		
		text_layer_set_text(time3_layer, (char*) &time3_buffer);
		break;
		
		case KEY_TIME4:
		snprintf(hour4_buffer, sizeof("xx"), "%d", value);
		
		if (!clock_is_24h_style()) {			
			int hour4 = atoi(hour4_buffer);
			int hour12_4 = 12;
			if		(hour4 == 0) {snprintf(time4_buffer, sizeof("xx:xxx"),"%d:00a", hour12_4);}
			else if (hour4 < 12 && hour4 > 0){snprintf(time4_buffer, sizeof("xx:xxx"),"%d:00a", hour4);}
			else if (hour4 == 12) {snprintf(time4_buffer, sizeof("xx:xxx"),"%d:00p", hour12_4);}
			else {
				int hour4_12 = hour4-12;
				snprintf(time4_buffer, sizeof("xx:xxx"),"%d:00p", hour4_12);
			}
		}
		
		else {
			if (value < 10){
				char dhour4[] = "0";
				strcpy(time4_buffer, dhour4);
				strcat(time4_buffer, hour4_buffer);
			}
			else{
				strcpy(time4_buffer, hour4_buffer);
			}
			strcat(time4_buffer, ":00");
		}
		
		text_layer_set_text(time4_layer, (char*) &time4_buffer);
		break;
	}
	vibes_short_pulse();
}

//appmessageの取り出し
static void in_received_handler (DictionaryIterator *iter, void *context)
	{
	(void) context;

	//データを取得し"t"に構造体として収納する
	Tuple *t = dict_read_first(iter);
	while (t!= NULL) //以下をmessageからnullが返ってくるまで繰り返す
		{
		process_tuple(t);
		t = dict_read_next(iter);
	}
}

//windowに素材を配置
void window_load (Window *window)
	{
	
	// location_layer
  	location_layer = text_layer_create(GRect(5, 1, 144, 30));
  	text_layer_set_background_color(location_layer, GColorClear);
  	text_layer_set_text_color(location_layer, GColorWhite);
  	text_layer_set_font(location_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_22)));
  	text_layer_set_text(location_layer, "loading...");
	layer_add_child(window_get_root_layer(window), (Layer *)location_layer);
	
	//ここにbitmaplayer"background"を挿入
	bg_layer = bitmap_layer_create(GRect(0, 33, 120, 42));
	bitmap_layer_set_background_color(bg_layer, GColorClear);
	bitmap_layer_set_bitmap(bg_layer, gbitmap_create_with_resource(RESOURCE_ID_BG));
	layer_add_child(window_get_root_layer(window), (Layer *)bg_layer);
	
	// icon1_layer
  	icon1_layer = bitmap_layer_create(GRect(0, 38, 48, 36));
	bitmap_layer_set_alignment(icon1_layer, GAlignCenter);
	bitmap_layer_set_compositing_mode(icon1_layer, GCompOpAssignInverted); //画像色反転
  	layer_add_child(window_get_root_layer(window), (Layer *)icon1_layer);
	
	//結果1のレイヤを反転処理
	//condition1_layer
	condition1_layer = text_layer_create(GRect(48, 35, 67, 20));
  	text_layer_set_background_color(condition1_layer, GColorClear);
 	text_layer_set_text_color(condition1_layer, GColorBlack);
  	text_layer_set_font(condition1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_B_14)));
  	text_layer_set_text_alignment(condition1_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer *)condition1_layer);
  
	//tmpm_layer
	tmpm_layer = bitmap_layer_create(GRect(48, 55, 14, 14));
	bitmap_layer_set_background_color(tmpm_layer, GColorClear);
	bitmap_layer_set_compositing_mode(tmpm_layer, GCompOpAssignInverted);
	layer_add_child(window_get_root_layer(window), (Layer *)tmpm_layer);
	
  	// temperature1_layer
  	temperature1_layer = text_layer_create(GRect(62, 55, 53, 18));
  	text_layer_set_background_color(temperature1_layer, GColorClear);
  	text_layer_set_text_color(temperature1_layer, GColorBlack);
	text_layer_set_text_alignment(temperature1_layer, GTextAlignmentCenter);
  	text_layer_set_font(temperature1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROID_B_12)));
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
	bitmap_layer_destroy(bg_layer);
	
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

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  acceltap();
}

//windowの表示を構成
void init()
	{
	window = window_create();
  	window_set_background_color(window, GColorBlack);
 	window_set_fullscreen(window, false);
	
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload,
	};
	window_set_window_handlers(window, handlers);
	
	//appmessage eventsを登録？
	app_message_register_inbox_received(in_received_handler);
	//appmessageの最大入出力数？
	app_message_open (app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	/*
	アプリ終了時に次回起動時に必要な変数を母艦アプリに保存する
	persist_write_[bool/int/string/data]("keyname", "name");
	
	アプリ起動時に保存された変数を母艦アプリより読み出す
	persist_read_[bool/int/string/data]("keyname", "name", sizeof("size"));
	
	参考：http://developer.getpebble.com/guides/pebble-apps/app-structure/persistent-storage/
	*/
	
	persist_read_string(KEY_UNIT, tempunit, sizeof(tempunit));
	
	accel_tap_service_subscribe(accel_tap_handler);
	window_stack_push(window, true);
}

void deinit ()
	{
	persist_write_string(KEY_UNIT, tempunit);
	accel_tap_service_unsubscribe();
	window_destroy (window);
}

int main (void)
	{
	init();
	app_event_loop();
	deinit();
}