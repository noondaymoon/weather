var getweather = function(){ //ページを取得してアレコレする
	//現在地の取得

	navigator.geolocation.getCurrentPosition(function(position) {
		console.log("Got position! " + JSON.stringify(position));

		var lat = (Math.round(position.coords.latitude*100)/100);
		var lon = (Math.round(position.coords.longitude*100)/100);

		var response = HTTPGET ( "http://api.openweathermap.org/data/2.5/forecast?"+"lat=" + lat + "&lon=" + lon);

		var json = JSON.parse(response); //json形式に変換
	//jsonの内容を展開
		var temperature1 = Math.round (json.list[0].main.temp - 273.15); //前述jsonよりtemp-273.15を格納
		var icon1 = json.list[0].weather[0].icon;
		var location = json.city.name.toLowerCase();
		var description1 = json.list[0].weather[0].description.toLowerCase();
		var icon2 = json.list[1].weather[0].icon;
		var temperature2 = Math.round (json.list[1].main.temp - 273.15);
		var icon3 = json.list[2].weather[0].icon;
		var temperature3 = Math.round (json.list[2].main.temp - 273.15);
		var icon4 = json.list[4].weather[0].icon;
		var temperature4 = Math.round (json.list[4].main.temp - 273.15);
	
	//logに結果を吐き出す
		console.log("\ntmp: " + temperature1 + "\nicon_id: " + icon1 + "\nlocation: " + location + "\ncnd: " + description1+ "\nlat: " + lat + "\nlon: " + lon);

	//c側へ送るための辞書を作成する
		var dict = {
			"KEY_LCT" : location,
			"KEY_TMP1" : temperature1,
			"KEY_ICON1": icon1,
			"KEY_CND1": description1,
			"KEY_TMP2": temperature2,
			"KEY_ICON2": icon2,
			"KEY_TMP3": temperature3,
			"KEY_ICON3": icon3,
			"KEY_TMP4": temperature4,
			"KEY_ICON4": icon4,

		
		
		}; //構造体
	
	//dictをc側へ送る
		Pebble.sendAppMessage(dict);
	});
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
