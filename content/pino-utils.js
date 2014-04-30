

var pinocchio;
//var pinocchio.utils = {};

pinocchio.utils.getCookieValue = function (cookie, key) 
{
	var params = cookie.split(';');	

	for (var i = 0; i < params.length; i++) {
		var sparam = params[i];
		var keyval = sparam.split('=');
				
		if (keyval[0].toLowerCase == key.toLowerCase)
			return keyval[1];
	}
	return "";
};

pinocchio.utils.extractValueFromSetCookie = function (setcookie, start, key) 
{
	var lines = cookie.split('\n');

	for (var i = 0; i < lines.length; i++) {
		var params = lines[i].split(';');	
		if (params[0].toLowerCase() != start.toLowerCase())
			continue;
		for (var j = 0; j < params.length; j++) {
			var sparam = params[i];
			var keyval = sparam.split('=');
			if (keyval[0].toLowerCase == key.toLowerCase)
				return keyval[1];
		}
	}
	return "";
};
