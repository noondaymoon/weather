var getWeather = function(){
	//ページを取得してアレコレする
	var response = HTTPGET ( "http://api.openweathermap.org/data/2.5/weather?q=Hakodate,JP");
	//"&APPID=375cae36f97ac8ea716a681e9c708f1c"
	var json = JSON.parse(response); //json形式に変換
	//jsonの内容を展開
	var temperature_c = Math.round (json.main.temp - 273.15); //前述jsonよりtemp-273.15を格納
	var temperature_h = Math.round (json.main.temp_max - 273.15);
	var temperature_l = Math.round (json.main.temp_min - 273.15);
	var location = json.name;
	var condition = json.weather[0].main;
	
	//logに結果を吐き出す
	console.log("current tmp: " + temperature_c + "\nhigh_tmp" + temperature_h + "\nlow_tmp" + temperature_l + "\ncnd: " + condition　+ "\nlct: " + location + "\nres: " + response);
	
	//c側へ送るための辞書を作成する
	var dict = {
		"KEY_LCT" : location,
		"KEY_C_TMP" : temperature_c,
		"KEY_H_TMP": temperature_h,
		"KEY_L_TMP": temperature_l,
		"KEY_CND": condition,
	}; //構造体
	
	//dictをc側へ送る
	Pebble.sendAppMessage(dict);
};

//pebble用アプリと連携するための最初の記述
Pebble.addEventListener("ready",
	function(e) {
		//pebbleから"ready"が送られてくるのを待って、以下のオシゴトをさせる
		getWeather();
	}
);

function HTTPGET (url) {
	var req = new XMLHttpRequest();
	req.open ("GET", url, false);
	req.send (null);
	return req.responseText;
}
