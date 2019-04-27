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

window.addEventListener('load', function(e) {
  $('#visszalapoz').addEventListener('click', lapozasvissza, false);
  $('#tovabblapoz').addEventListener('click', lapozastovabb, false);
}, false);

function lapozasvissza(e) {
  e.preventDefault();
  var page = findGetParameter("page");
  console.log(page);
  page--;
  ajax({
    method: 'POST',
    postdata: 'page=' + page,
    url: 'ajax_lapozas_t.php',
    success: function(xhr, xhrResponse) {
      console.log(xhrResponse);
      var konyvek = JSON.parse(xhrResponse);
      //$('#konyvek').innerHTML  = konyvek[0]['szerzo'] + "<br>" + konyvek.length;


        
      $('#konyvek').innerHTML = "";
      //$('#konyvek').innerHTML += '<table>';

      for (let i = 0; i < konyvek.length; i++) {
        //$('#konyvek').innerHTML += '<tr>' + (konyvek[i]).join('</td><td>') + '/tr';
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
      //$('#konyvek').innerHTML += '</table>';
      if (page <= 1){
        $('#visszalapoz').style.display = "none";
      }
      if ((page*5) >= konyvek[0]['osszkonyvszam']){ //Ez még nem jó
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

function lapozastovabb(e) {
  e.preventDefault();
  var page = findGetParameter("page");
  console.log(page);
  page++;
  ajax({
    method: 'POST',
    postdata: 'page=' + page,
    url: 'ajax_lapozas_t.php',
    success: function(xhr, xhrResponse) {
      console.log(xhrResponse);
      var konyvek = JSON.parse(xhrResponse);
      //$('#konyvek').innerHTML  = konyvek[0]['szerzo'] + "<br>" + konyvek.length;


        
      $('#konyvek').innerHTML = "";
      //$('#konyvek').innerHTML += '<table>';

      for (let i = 0; i < konyvek.length; i++) {
        //$('#konyvek').innerHTML += '<tr>' + (konyvek[i]).join('</td><td>') + '/tr';
        var be = '<tr><td><b>' + konyvek[i]['szerzo'] + '</b></td><td>' + konyvek[i]['cim'] + '</td><td>' + konyvek[i]['kat'] + '</td><td>' + konyvek[i]['eo'];
        be += '</td><td><button type="button"  id="mod" onclick=';
        be += konyvek[i]['mod'];
        be += '>Módosítás</button></td>';
        be += '<td><button type="button" id = "torl" onclick=';
        be += konyvek[i]['torl'];
        be += '>Törlés</button></td></tr>';
      
        $('#konyvek').innerHTML += be;
        
        
        
        
        
        
        /*
        var uid = 'm?h=' + i;
        $('#mod').id = uid;
        uid = 't?h=' + i;
        $('#torl').id = uid;*/
      }
      if (page <= 1){
        $('#visszalapoz').style.display = "none";
      }
      else{
        $('#visszalapoz').style.display = "block";
      }
      //$('#konyvek').innerHTML += '</table>';
      if ((page)*5 >= konyvek[0]['osszkonyvszam']){ //Ez még nem jó
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