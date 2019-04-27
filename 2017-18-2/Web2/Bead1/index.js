var m = 0;
var nehez;
var meret;

window.addEventListener('load', function () {
  document.getElementById('3x3').addEventListener('click', function(e) {
    document.getElementById('3x3').style.border = "thick solid #000000";
    document.getElementById('4x4').style.border = "none";
      m = parseInt(m/10)*10;
      //console.log(m);
      setCookies();
      
  }, false)
    document.getElementById('4x4').addEventListener('click', function(e) {
    document.getElementById('4x4').style.border = "thick solid #000000";
    document.getElementById('3x3').style.border = "none";
      m = parseInt(m/10)*10 + 1;
       // console.log(m);
        setCookies();
  }, false)
    document.getElementById('3x3').style.border = "thick solid #000000";
    document.getElementById('4x4').style.border = "none";
      m = parseInt(m/10)*10;
    //console.log(m);
    setCookies();
   document.getElementById('easy').addEventListener('click', function(e) {
    document.getElementById('easy').style.border = "thick solid #000000";
    document.getElementById('difficult').style.border = "none";
      m = m%10;
        //console.log(m);
       setCookies();
  }, false) 
    
    document.getElementById('difficult').addEventListener('click', function(e) {
    document.getElementById('difficult').style.border = "thick solid #000000";
    document.getElementById('easy').style.border = "none";
      m = m%10 + 10;
        //console.log(m);
        setCookies();
  }, false)  
    document.getElementById('easy').style.border = "thick solid #000000";
    document.getElementById('difficult').style.border = "none";
      m = m%10;
    //console.log(m);
    setCookies();
  
}, false);

function setCookies(){
    //document.cookie = 'valami=' + m + '';
    //document.cookie = 'nehez=' + nehez + '';
    //console.log(document.cookie);
    localStorage.setItem("ertek", m);
    console.log(localStorage.getItem("ertek"));
    //console.log("pediglefuttoot");
}

document.cookie = 'test1=semmi';
//document.cookie = 'test2=World';