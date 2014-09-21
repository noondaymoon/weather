var getweather = function(){ //ページを取得してアレコレする
	//現在地の取得
	
	
	
	//lat=xxx&lon=xxx
	var response = HTTPGET ( "http://api.openweathermap.org/data/2.5/forecast?lat=41.78&lon=140.74");
	//都市名なら"q=Hakodate,JP"
	
	var json = JSON.parse(response); //json形式に変換
	//jsonの内容を展開
	var temperature1 = Math.round (json.list[0].main.temp - 273.15); //前述jsonよりtemp-273.15を格納
	var icon1 = json.list[0].weather[0].icon;
	var location = json.city.name;
	var description1 = json.list[0].weather[0].main;
	
	//logに結果を吐き出す
	console.log("\ntmp: " + temperature1 + "\nicon_id: " + icon1 + "\nlocation: " + location + "\ncnd: " + description1/* + "\ngeo: " + geo */ );
	
	//c側へ送るための辞書を作成する
	var dict = {
		"KEY_LCT" : location,
		"KEY_TMP1" : temperature1,
		"KEY_ICON1": icon1,
		"KEY_CND1": description1,
	}; //構造体
	
	//dictをc側へ送る
	Pebble.sendAppMessage(dict);
};

//pebble用アプリと連携するための最初の記述
Pebble.addEventListener("ready",
	function(e) {
		//pebbleから"ready"が送られてくるのを待って、以下のオシゴトをさせる

		getweather();
	}
);



function HTTPGET (url) {
	var req = new XMLHttpRequest();
	req.open ("GET", url, false);
	req.send (null);
	return req.responseText;
}

/*
var getgeo = navigator.geolocation.getCurrentPossition(function(position){
		var lat = position.coords.latitude;
		var lon = position.coords.longitude;
		var geo = "lat=" + lat + "&lon=" + lon;
		return geo;
		*/