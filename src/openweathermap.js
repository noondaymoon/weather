var getweather = function(){ //ページを取得してアレコレする
	//現在地の取得

	navigator.geolocation.getCurrentPosition(function(position) {
		console.log("position: " + JSON.stringify(position));

		var lat = (Math.round(position.coords.latitude*100)/100);
		var lon = (Math.round(position.coords.longitude*100)/100);

		var today_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/weather?"+"lat=" + lat + "&lon=" + lon);
		var forcast_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/forecast?"+"lat=" + lat + "&lon=" + lon);
				var today = JSON.parse (today_res);
		var forcast = JSON.parse (forcast_res); //json形式に変換
		
	//jsonの内容を展開
		var location = today.name.toLowerCase();
		var temperature1 = Math.round (today.main.temp - 273.15); //前述jsonよりtemp-273.15を格納
		var icon1 = today.weather[0].icon;
		var description1 = today.weather[0].main.toLowerCase();
		var icon2 = forcast.list[2].weather[0].icon;
		var temperature2 = Math.round (forcast.list[2].main.temp - 273.15);
		//予報の時間を取得しxx:xxで表示する（参考：http://yut.hatenablog.com/entry/20111015/1318633937）
		var time2 = new Date((forcast.list[2].dt)*1000);
		var hour2 = (time2.getHours() < 10) ? "0" + time2.getHours() : time2.getHours();
		var min2 = (time2.getMinutes() < 10) ? "0" + time2.getMinutes() : time2.getMinutes();
		var icon3 = forcast.list[3].weather[0].icon;
		var temperature3 = Math.round (forcast.list[3].main.temp - 273.15);
		var time3 = new Date((forcast.list[3].dt)*1000);
		var hour3 = (time3.getHours() < 10) ? "0" + time3.getHours() : time3.getHours();
		var min3 = (time3.getMinutes() < 10) ? "0" + time3.getMinutes() : time3.getMinutes();
		var icon4 = forcast.list[5].weather[0].icon;
		var temperature4 = Math.round (forcast.list[5].main.temp - 273.15);
		var time4 = new Date((forcast.list[5].dt)*1000);
		var hour4 = (time4.getHours() < 10) ? "0" + time4.getHours() : time4.getHours();
		var min4 = (time4.getMinutes() < 10) ? "0" + time4.getMinutes() : time4.getMinutes();
			
	//logに結果を吐き出す
		console.log(
			"\nloc: " + location +
			"\nstatus1 cnd: " + description1 + ",icon_id: " + icon1 + ",tmp: " + temperature1 +
			"\nstatus2 icon_id: " + icon2 + ",tmp: " + temperature2 + ",time2: " + hour2+":"+min2 +
			"\nstatus3 icon_id: " + icon3 + ",tmp: " + temperature3 + ",time3: " + hour3+":"+min3 +
			"\nstatus4 icon_id: " + icon4 + ",tmp: " + temperature4 + ",time3: " + hour4+":"+min4 +
			"\nlat: " + lat + ",lon: " + lon);

	//c側へ送るための辞書を作成する
		var dict = {
			"KEY_LCT"	: location,
			"KEY_TMP1"	: temperature1,
			"KEY_ICON1"	: icon1,
			"KEY_CND1"	: description1,
			"KEY_TMP2"	: temperature2,
			"KEY_ICON2"	: icon2,
			"KEY_TIME2"	: hour2+":"+min2,
			"KEY_TMP3"	: temperature3,
			"KEY_ICON3"	: icon3,
			"KEY_TIME3"	: hour3+":"+min3,
			"KEY_TMP4"	: temperature4,
			"KEY_ICON4"	: icon4,
			"KEY_TIME4"	: hour4+":"+min4,
		
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
