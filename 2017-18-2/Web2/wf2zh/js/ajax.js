//AJAX, ne bántsd

function getXHR() {
  var xhr = null;
  try {
    xhr = new XMLHttpRequest(); 
  }
  catch (e) {
    try {
      xhr = new ActiveXObject("Msxml2.XMLHTTP");
    }
    catch (e) {
      try {
        xhr = new ActiveXObject("Microsoft.XMLHTTP");
      }
      catch (e) {
        xhr = null;
      }
    }
  }
  
  return xhr;
}

function ajax(opts) {
  var method   = opts.method || "GET";
  var url      = opts.url || "";
  var getdata  = opts.getdata || "";
  var postdata = opts.postdata || "";
  var success  = opts.success || function(){};
  var error    = opts.error || function(){};
  
  method = method.toUpperCase();
  url = url + '?' + getdata;
  var xhr = getXHR();
  xhr.open(method, url, true);
  if (method == "POST") {
    xhr.setRequestHeader(
      'Content-Type',  'application/x-www-form-urlencoded'
    );
  }
  xhr.addEventListener('readystatechange', function(){
    if (xhr.readyState == 4) {
      if (xhr.status == 200) {
        success(xhr, xhr.responseText);
      }
      else { error(xhr); }
    }
  });
  xhr.send(method == "POST" ? postdata : null);
  return xhr;
}

