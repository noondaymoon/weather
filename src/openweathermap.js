var getweather = function(){ //ページを取得してアレコレする
	
	//現在地を取得
	navigator.geolocation.getCurrentPosition(function(position) {
		console.log("position: " + JSON.stringify(position));
		//現在地を取得し、positionに格納して詳細をログへ吐き出す。

		//positionから緯度経度を取得
		var lat = (Math.round(position.coords.latitude*100)/100);
		var lon = (Math.round(position.coords.longitude*100)/100);
		
		//openweathermap.orgより現在地参照で天候をjsonで取得するページへリクエスト
		var today_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/weather?"+"lat=" + lat + "&lon=" + lon);
		var forcast_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/forecast?"+"lat=" + lat + "&lon=" + lon);
		var today = JSON.parse (today_res);
		var forcast = JSON.parse (forcast_res);
		//JSON:parseはページからの戻り値をjsonの形（オブジェクト/配列）にする
		
		//jsonから必要なデータのみを取り出して変数に格納する
		var location = today.name.toLowerCase(); //小文字大好きな人にはたまらないヤツ
		
		var temperature1 = Math.round (today.main.temp - 273.15);
		//前述jsonよりtempはf値なので-273.15してから小数点以下丸めて格納
		
		//日中に夜のアイコンが呼び出される問題を日出・日没時間を利用して解決する（日没-現在時刻と現在-日出時刻が両方とも+なら日中という扱いにする）
		var icon1 = ((today.sys.sunset - Math.round((new Date())/1000)) > 0 && (Math.round((new Date())/1000) - today.sys.sunrise) > 0) ? today.weather[0].icon.slice(0,2) + "d" : today.weather[0].icon.slice(0,2) + "n";
		//if文は"?"と":"を使う三項演算子という方法で省略できる（参考: http://ja.wikibooks.org/wiki/JavaScript_If文の復習と、三項演算子）
		//取得される日出・日没時間はunixtime小数点以下を丸めた値なので…new Date()で現在時間を取得、/1000でunixtime、Math.roundで小数点以下を丸めて同じ桁数にしている
		
		
		var description1 = today.weather[0].main.toLowerCase();
		
		//以降、予報の値を適宜文字列操作し表示させる
		//アイコンについては日付をまたいだ場合日出・日没時間を取得できないため06:00より18:00までを日中と判断させる。
		var temperature2 = Math.round (forcast.list[2].main.temp - 273.15);
		//予報の時間を取得しxx:xxで表示する（参考：http://yut.hatenablog.com/entry/20111015/1318633937）
		var time2 = new Date((forcast.list[2].dt)*1000); //new date()*1000でunixtime
		var hour2 = (time2.getHours() < 10) ? "0" + time2.getHours() : time2.getHours();
		var min2 = (time2.getMinutes() < 10) ? "0" + time2.getMinutes() : time2.getMinutes();
		var icon2 = (time2.getHours() >= 6 && time2.getHours() <= 18) ? forcast.list[2].weather[0].icon.slice(0, 2) + "d" : forcast.list[2].weather[0].icon.slice(0, 2) + "n";
		
		var temperature3 = Math.round (forcast.list[3].main.temp - 273.15);
		var time3 = new Date((forcast.list[3].dt)*1000);
		var hour3 = (time3.getHours() < 10) ? "0" + time3.getHours() : time3.getHours();
		var min3 = (time3.getMinutes() < 10) ? "0" + time3.getMinutes() : time3.getMinutes();
		var icon3 = (time3.getHours() >= 6 && time3.getHours() <= 18) ? forcast.list[3].weather[0].icon.slice(0, 2) + "d" : forcast.list[3].weather[0].icon.slice(0, 2) + "n";
		
		var temperature4 = Math.round (forcast.list[5].main.temp - 273.15);
		var time4 = new Date((forcast.list[5].dt)*1000);
		var hour4 = (time4.getHours() < 10) ? "0" + time4.getHours() : time4.getHours();
		var min4 = (time4.getMinutes() < 10) ? "0" + time4.getMinutes() : time4.getMinutes();
		var icon4 = (time4.getHours() >= 6 && time4.getHours() <= 18) ? forcast.list[5].weather[0].icon.slice(0, 2) + "d" : forcast.list[5].weather[0].icon.slice(0, 2) + "n";
					
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
