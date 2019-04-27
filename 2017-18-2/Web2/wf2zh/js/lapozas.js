//Adott nevű paramétert kivesz a böngészősávból, ugyan az, mint php-ban a $_GET["változó"]

function findGetParameter(parameterName) {
  var result = null,
      tmp = [];
  location.search
      .substr(1)
      .split("&")
      .forEach(function (item) {
        tmp = item.split("=");
        if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);
      });
  if (result == null || result <= 0 || isNaN(result)){
    result = 1;
  }
  return result;
}

function $(element){
  return document.querySelector(element);
}

function $$(element){
  return document.querySelectorAll(element);
}

//Gombokra ráállítja az adott függvényt

window.addEventListener('load', function(e) {
  //Példa
  $('#visszalapoz').addEventListener('click', lapozasvissza, false);
  $('#tovabblapoz').addEventListener('click', lapozastovabb, false);
  //Példa vége
}, false);

function lapozasvissza(e) {
  e.preventDefault();

  //Ajax lefutása előtti műveletek
  var page = findGetParameter("page");
  console.log(page);
  page--;
  
  
  // Ajax START
  ajax({
    method: 'POST',
    postdata: 'page=' + page, //elküldi a page nevű változóba a page változó értékét 
    //formátum: 'változónév=' + érték,
    url: 'ajax_lapozas_t.php',
    //Műveleteket végző php, ez egy echo-val és egy xhrREsponse-val tér vissza
    success: function(xhr, xhrResponse) {
      console.log(xhrResponse);
      
      //ha json_encode-val küldtön át listát, ezzel tudjuk dekódolni: JSON.parse(xhrResponse)
      var konyvek = JSON.parse(xhrResponse);
      
      //innentől a konyvek id-jű táblázat tbody-ját írjuk felül.
      $('#konyvek').innerHTML = "";

      for (let i = 0; i < konyvek.length; i++) {
        if (!konyvek[i]['szerzo'])
            continue;
        
        
            var be = '<tr><td><b>' + konyvek[i]['szerzo'] + '</b></td><td>' + konyvek[i]['cim'] + '</td><td>' + konyvek[i]['kat'] + '</td><td>' + konyvek[i]['eo'];
        be += '</td><td><button type="button"  id="mod" onclick=';
        be += konyvek[i]['mod'];
        be += '>Módosítás</button></td>';
        be += '<td><button type="button" id = "torl" onclick=';
        be += konyvek[i]['torl'];
        be += '>Törlés</button></td></tr>';

        $('#konyvek').innerHTML += be;
      }
      if (page <= 1){
        $('#visszalapoz').style.display = "none";
      }
      if ((page*5) >= konyvek[0]['osszkonyvszam']){
        $('#tovabblapoz').style.display = "none";
      }
      else{
        $('#tovabblapoz').style.display = "block";
      }
      console.log(konyvek[0]['osszkonyvszam']);
    },
    error: function(xhr) {
      console.log(xhr);
    }
  });
  //AJAX vége
  var ki = '?page=' + page;
  history.replaceState(null, null, ki);
  
}

function lapozastovabb(e) {
  e.preventDefault();
  var page = findGetParameter("page");
  console.log(page);
  page++;
  ajax({
    method: 'POST',
    postdata: 'page=' + page,
    url: 'ajax_szures.php',
    success: function(xhr, xhrResponse) {
      console.log(xhrResponse);
      var konyvek = JSON.parse(xhrResponse);      
      $('#konyvek').innerHTML = "";
      for (let i = 0; i < konyvek.length; i++) {
        var be = '<tr><td><b>' + konyvek[i]['szerzo'] + '</b></td><td>' + konyvek[i]['cim'] + '</td><td>' + konyvek[i]['kat'] + '</td><td>' + konyvek[i]['eo'];
        be += '</td><td><button type="button"  id="mod" onclick=';
        be += konyvek[i]['mod'];
        be += '>Módosítás</button></td>';
        be += '<td><button type="button" id = "torl" onclick=';
        be += konyvek[i]['torl'];
        be += '>Törlés</button></td></tr>';
      
        $('#konyvek').innerHTML += be;
      }
      if (page <= 1){
        $('#visszalapoz').style.display = "none";
      }
      else{
        $('#visszalapoz').style.display = "block";
      }
      if ((page)*5 >= konyvek[0]['osszkonyvszam']){
        $('#tovabblapoz').style.display = "none";
      }
      else{
        $('#tovabblapoz').style.display = "block";
      }
      console.log(konyvek[0]['osszkonyvszam']);
    },
    error: function(xhr) {
      console.log(xhr);
    }
  });
  var ki = '?page=' + page;
  history.replaceState(null, null, ki);
  
}