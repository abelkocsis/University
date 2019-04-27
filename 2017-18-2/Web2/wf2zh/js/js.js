function $(element){
    return document.querySelector(element);
  }
  
  function $$(element){
    return document.querySelectorAll(element);
  }

  
  window.addEventListener('load', function(e) {
    //Példa
    var kivalasztott;
    document.addEventListener('keydown', function(e){
        
        
    }, false);

    setInterval(p, 100);
    //console.log(document.onkeypress);
    console.log($('#szuro').value);
  }, false)

  function p(e){
      if ($('#szuro').value != ""){
          var be = $('#szuro').value;
          ajax({
            method: 'POST',
            postdata: 'sz=' + be, //elküldi a page nevű változóba a page változó értékét 
            //formátum: 'változónév=' + érték,
            url: 'ajax_szures.php',
            //Műveleteket végző php, ez egy echo-val és egy xhrREsponse-val tér vissza
            success: function(xhr, xhrResponse) {
              console.log(xhrResponse);
              
              //ha json_encode-val küldtön át listát, ezzel tudjuk dekódolni: JSON.parse(xhrResponse)
              var kij = JSON.parse(xhrResponse);
              console.log(kij[1]);
              for (var i = 1; i < kij[0]; i++){
                  if (typeof(kij[i]) != 'undefined'){

                  
                  if (kij[i]){
                    var nev = "";
                    nev += 'tr[data-id="';
                    nev += (i-1);
                    nev += '"]';
                    console.log(nev);
                    var a = document.querySelector(nev);
                    a.classList.add("table-warning");
                  }
                  else{
                    var nev = "";
                    nev += 'tr[data-id="';
                    nev += (i-1);
                    nev += '"]';
                    console.log(nev);
                    var a = document.querySelector(nev);
                    if (a.classList.contains("table-warning"))
                        a.classList.remove("table-warning");
                  }
                }
              }
             
            },
            error: function(xhr) {
              console.log(xhr);
            }
          });
          //AJAX vége
          
          
        }
      
  }

  


  