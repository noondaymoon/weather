var getweather = function(temp_unit){
	
	//現在地を取得
	navigator.geolocation.getCurrentPosition(function(position) {
		//console.log("position: " + JSON.stringify(position));
		//現在地を取得し、positionに格納して詳細をログへ吐き出す。

		//positionから緯度経度を取得
		var lat = (Math.round(position.coords.latitude*100)/100);
		var lon = (Math.round(position.coords.longitude*100)/100);
		
		//openweathermap.orgへ現在地参照で天候をjsonで取得するリクエスト
		var today_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/weather?"+"lat=" + lat + "&lon=" + lon);
		var forcast_res = HTTPGET ( "http://api.openweathermap.org/data/2.5/forecast?"+"lat=" + lat + "&lon=" + lon);
		var today = JSON.parse (today_res);
		var forcast = JSON.parse (forcast_res);
		//JSON:parseはページからの戻り値をjsonの形（オブジェクト/配列）にする
		
		//jsonから必要なデータのみを取り出して変数に格納する
		var location = today.name.length > 15 ? today.name.toLowerCase().slice(0,11) + "..." : today.name.toLowerCase();
		
		var temperature1 = Math.round (today.main.temp - 273.15);
		//前述jsonよりtempはf値なので-273.15してから小数点以下丸めて格納
		//f値での表示を多く要請されているのでc側で対応する予定
		
		//日中に夜のアイコンが呼び出される問題を日出・日没時間を利用して解決する（日没-現在時刻と現在-日出時刻が両方とも+なら日中という扱いにする）
		var now = ((new Date(Math.round(new Date()/1000) * 1000)).getHours())*60 + new Date(Math.round(new Date()/1000) * 1000).getMinutes();
		var sunrise = ((new Date((today.sys.sunrise) * 1000)).getHours())*60 + (new Date((today.sys.sunrise) * 1000)).getMinutes();
		var sunset = ((new Date(today.sys.sunset * 1000)).getHours())*60 + (new Date(today.sys.sunrise * 1000)).getMinutes();
		var icon1 = ((sunset - now) > 0 && (now - sunrise) > 0) ? today.weather[0].icon.slice(0,2) + "d" : today.weather[0].icon.slice(0,2) + "n";
		
		//if文は"?"と":"を使う三項演算子という方法で省略できる（参考: http://ja.wikibooks.org/wiki/JavaScript_If文の復習と、三項演算子）
		//取得される日出・日没時間はunixtime小数点以下を丸めた値なので…new Date()で現在時間を取得、/1000でunixtime、Math.roundで小数点以下を丸めて同じ桁数にしている
		
		var description1 = today.weather[0].main.toLowerCase();
		
		//以降、予報の値を適宜文字列操作し表示させる
		
		var temperature2 = Math.round (forcast.list[2].main.temp - 273.15);
		//予報の時間を取得しxx:xxで表示する（参考：http://yut.hatenablog.com/entry/20111015/1318633937）
		var time2 = new Date((forcast.list[2].dt)*1000); //new date()*1000でunixtime
		//var hour2 = (time2.getHours() < 10) ? "0" + time2.getHours() : time2.getHours();
		var hour2 = time2.getHours();
		//var minute2 = (time2.getMinutes() < 10) ? "0" + time2.getMinutes() : time2.getMinutes();
		var icon2 = (sunset - ((time2.getHours()*60)+time2.getMinutes()) > 0 && ((time2.getHours() * 60) + time2.getMinutes()) - sunrise >0) ? forcast.list[2].weather[0].icon.slice(0, 2) + "d" : forcast.list[2].weather[0].icon.slice(0, 2) + "n";
		
		var temperature3 = Math.round (forcast.list[3].main.temp - 273.15);
		var time3 = new Date((forcast.list[3].dt)*1000);
		var hour3 = time3.getHours();
		var icon3 = (sunset - ((time3.getHours()*60)+time3.getMinutes()) > 0 && ((time3.getHours() * 60) + time3.getMinutes()) - sunrise >0) ? forcast.list[3].weather[0].icon.slice(0, 2) + "d" : forcast.list[3].weather[0].icon.slice(0, 2) + "n";
				
		var temperature4 = Math.round (forcast.list[5].main.temp - 273.15);
		var time4 = new Date((forcast.list[5].dt)*1000);
		var hour4 = time4.getHours();
		var icon4 = (sunset - ((time4.getHours()*60)+time4.getMinutes()) > 0 && ((time4.getHours() * 60) + time4.getMinutes()) - sunrise >0) ? forcast.list[5].weather[0].icon.slice(0, 2) + "d" : forcast.list[5].weather[0].icon.slice(0, 2) + "n";
		
	//c側へ送るための辞書を作成する
		var dict = {
			"KEY_UNIT"	: temp_unit,
			"KEY_LCT"	: location,
			"KEY_TMP1"	: temperature1,
			"KEY_ICON1"	: icon1,
			"KEY_CND1"	: description1,
			"KEY_TMP2"	: temperature2,
			"KEY_ICON2"	: icon2,
			"KEY_TIME2" : hour2,
			"KEY_TMP3"	: temperature3,
			"KEY_ICON3"	: icon3,
			"KEY_TIME3"	: hour3,
			"KEY_TMP4"	: temperature4,
			"KEY_ICON4"	: icon4,
			"KEY_TIME4"	: hour4,
						
		}; //構造体
			
	//dictをc側へ送る
		Pebble.sendAppMessage(dict);
	});
};

Pebble.addEventListener("showConfiguration",
  function(e) {
    Pebble.openURL("https://dl.dropboxusercontent.com/u/4570910/pebble/weather/config.html");
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
    var configuration = JSON.parse(decodeURIComponent(e.response));
	var temp_unit = configuration.temp_unit;
	//console.log("response: " + e.response); //JSONの内容をログに出力
	getweather(temp_unit);
  }
);

//pebble用アプリと連携するための最初の記述
Pebble.addEventListener("ready",
	function(e) {
		//pebbleから"ready"が送られてくるのを待って、以下の関数を行う
		getweather();
	}
);

Pebble.addEventListener("appmessage",
	function(e) {
		getweather();
	}
);

function HTTPGET (url) {
	var req = new XMLHttpRequest();
	req.open ("GET", url, false);
	req.send (null);
	return req.responseText;
}