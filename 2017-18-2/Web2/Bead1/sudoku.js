// Sakktábla
var m; 

var sudoTable = {
  cellsInRow: 0,
  cellSize: 0,
  canvasContext: undefined,
  mezovalaszt : false,
  szin: -1,
  hx : -1,
  hy : -1,
    
  createTable: function(_cellsInRow, _cellSize) {
      
    this.cellsInRow = _cellsInRow;
    this.cellSize = _cellSize;

    canvas = document.createElement('canvas');
    canvas.setAttribute('id', 'sudoCanvas');
      
    canvas.setAttribute('height', sudoTable.cellSize * (sudoTable.cellsInRow +2) + bo*3);
      
    canvas.setAttribute('width', sudoTable.cellSize * (sudoTable.cellsInRow ) + bo*2);
      
    canvas.innerHTML = 'Ez akkor jelenik meg, ha nincs canvas támogatás szöveg, kép, stb.';
    
    this.canvasContext = canvas.getContext('2d');
    return canvas;
      ctx = this.canvasContext;
  },
  cD : function(szin1, szin2, szin3, szin4, szin5){
    if (!this.canvasContext)
      return;
    var ctx = this.canvasContext;
    ctx.fillStyle = szin1;
    ctx.fillRect(bo, 2*bo+(m)*this.cellSize, this.cellSize, this.cellSize);
    ctx.fillStyle = szin2;
    ctx.fillRect(bo+this.cellSize, 2*bo+(m)*this.cellSize, this.cellSize, this.cellSize);
    ctx.fillStyle = szin3;
    ctx.fillRect(bo+this.cellSize*2, 2*bo+(m)*this.cellSize, this.cellSize, this.cellSize);
    if (m == 4){
        ctx.fillStyle = szin4;
        ctx.fillRect(bo+this.cellSize*3, 2*bo+(m)*this.cellSize, this.cellSize, this.cellSize);
    }
    ctx.fillStyle = szin5;
    if (m == 4){
        ctx.fillRect(bo+this.cellSize*1.5, 2*bo+(m+1)*this.cellSize, this.cellSize, this.cellSize);
    }
    else{
        ctx.fillRect(bo+this.cellSize*1, 2*bo+(m+1)*this.cellSize, this.cellSize, this.cellSize);
    }
    
    
  },
  drawChoose: function(){
    if (!this.canvasContext)
      return;
    this.cD("#CB4335", "#229954", "#F5B041", "#2874A6",   "#ffffff");
    },
  hideChoose: function(){
    if (!this.canvasContext)
      return;
    this.cD("bisque", "bisque", "bisque", "bisque", "bisque");
    },
  draw: function() {
    if (!this.canvasContext)
      return;
    
    var ctx = this.canvasContext;
   
    
    ctx.fillStyle = "#000000";
    ctx.fillRect(bo-szegely, bo-szegely, this.cellsInRow * this.cellSize+szegely*2,  this.cellsInRow  * this.cellSize+szegely*2);
    for (var row = 0; row < this.cellsInRow; row++) {
      for (var column = 0; column < this.cellsInRow; column++) {
        ctx.fillStyle = "#ffffff";  
        ctx.fillRect(bo + row * this.cellSize, bo + column * this.cellSize, this.cellSize, this.cellSize);
        switch(color[row] [column]){
            case 3: ctx.fillStyle = "#2874A6";
                    break;
            case 2: ctx.fillStyle = "#F5B041";
                    break;
            case 0: ctx.fillStyle = "#CB4335";
                    break;
            case 1: ctx.fillStyle = "#229954";
                    break;
            default : ctx.fillStyle = "#ffffff";
                    break;
        }
        if (hole[row][column]){
            ctx.fillStyle = "#ffffff";
        }
        ctx.fillRect(bo + row * this.cellSize, bo + column * this.cellSize, this.cellSize, this.cellSize);
      }
    }
    if (m == 4){
        ctx.fillStyle = "#000000";
        ctx.fillRect(bo + 2 * this.cellSize, bo, szegely/2, this.cellSize*4);
        ctx.fillRect(bo, bo + 2 * this.cellSize, this.cellSize*4, szegely/2);
    }
  },
  update: function(){
      kx = parseInt(kx/this.cellSize);
      if (kx < 0)
          return;
      console.log(kx);
      
      if (this.mezovalaszt){
          ky -= this.cellSize*m + bo;
          ky = parseInt(ky / this.cellSize);
          console.log(ky);
          if (ky == 0 && kx < m){
              this.szin = kx;
              this.kitolt();
              this.mezovalaszt = false;
              this.hideChoose();
              return;
          }
          if (ky == 1){
              this.szin = -1;
              this.mezovalaszt = false;
              this.hideChoose();
              this.kitolt();
              return;
          }
          this.hideChoose();
          this.mezovalaszt = false;
          
          return;
      }
      ky = parseInt(ky/this.cellSize);
      console.log(ky);
      if (ky >= 0 && ky < m && hole[kx][ky]){
          this.mezovalaszt = true;
          this.hx = kx;
          this.hy = ky;
          this.drawChoose();
      }
      
      
},         
  kitolt: function(){
    console.log(this.hx);
    console.log(this.hy);
    var szinvolt = color[this.hx][this.hy];
    color[this.hx][this.hy] = this.szin;
    if (volt(this.hx,this.hy) && this.szin != -1){
        color[this.hx][this.hy] = this.szinvolt;
        console.log("rossz");
        var audio = new Audio('error.wav');
        audio.play();
        return
    }
    /*if (this.szin >= 0 && this.szin < m && this.szin != szinvolt){
        holes--;
    }
    else if (this.szin != szinvolt){
        holes++;
    }*/ 
      console.log(szinvolt);
      console.log(this.szin);
      if (szinvolt == undefined){
          szinvolt = -1;
      }
    if (this.szin>=0 && this.szin < m && (szinvolt < 0 || szinvolt > m)){
        holes--;
    }
    else if (this.szin < 0 && szinvolt >= 0 && szinvolt < m){
        holes++;
    }
    
    
    var ctx = this.canvasContext; 
    console.log("kitolt");
    switch (this.szin){
            case 3: ctx.fillStyle = "#2874A6";
                    break;
            case 2: ctx.fillStyle = "#F5B041";
                    break;
            case 0: ctx.fillStyle = "#CB4335";
                    break;
            case 1: ctx.fillStyle = "#229954";
                    break;
            default : ctx.fillStyle = "#ffffff";
                    break;     
    }
    aktmeret = 10;
    //this.egyetrajzol();  
    ctx.fillRect(bo+this.hx*cellSize+szegely, bo+this.hy*this.cellSize+szegely, this.cellSize-szegely*2, this.cellSize-szegely*2);
    
    //aktmeret = 1;
    //anim(this.canvasContext, this.hx, this.hy, this.cellSize);
    
    //myMove();   
    //timer=setInterval(this.anim, 1000);
      
    if (holes == 0){
        console.log("kesz");
        win();
    }
    
    
},
  
  anim: function(){
      console.log(aktmeret);
      if (aktmeret >= cellSize-szegely*2){
          clearInterval(timer);
      }
      else{
          console.log("egyik");
          if (!this.canvasContext)
                return; 
          console.log("masik");
            var ctx = this.canvasContext;
            switch (this.szin){
            case 3: ctx.fillStyle = "#2874A6";
                    break;
            case 2: ctx.fillStyle = "#F5B041";
                    break;
            case 0: ctx.fillStyle = "#CB4335";
                    break;
            case 1: ctx.fillStyle = "#229954";
                    break;
            default : ctx.fillStyle = "#ffffff";
                    break;     
                }

            ctx.fillRect(bo+this.hx*cellSize+szegely, bo+this.hy*cellSize+szegely, aktmeret, aktmeret);
      
          aktmeret++;
      }
    },

}


function katt(e){
    var x = e.pageX;
    var y = e.pageY;
    x -= canvas.offsetLeft;
    y -= canvas.offsetTop;
    x -= bo;
    y -= bo;
    
    kx = x;
    ky = y;
    sudoTable.update();
    /*
    if (x < 0 || y < 0){
        kx = -1;
        console.log(-999);
        return;
    }   
    x = parseInt(x / cellSize);
    y = parseInt(y / cellSize);
    
    if ((x >= m && x != 5) || (y >= m && y != 5)){
        kx = -1;
        console.log(-999);
        return;
    }
    kx = x;
    ky = y;
    console.log(kx);
    console.log(ky);
    
    sudoTable.update();*/
    
}

/*function anim(ctx, hx, hy, cellSize) {
    aktmeret = 5;
    var id = setInterval(frame(ctx, hx, hy, cellSize), 100);
    function frame(ctx, hx, hy, cellSize){
          console.log("belepett");
          console.log(aktmeret);
          console.log(cellSize-szegely*2);
          console.log(bo+hx*cellSize+szegely);
          ctx.fillRect(bo+hx*cellSize+szegely, bo+hy*cellSize+szegely, 1, 1);
          
        if (aktmeret >= cellSize-szegely*2) {
            console.log("most");
            console.log(aktmeret);
            console.log(cellSize-szegely*2);
            clearInterval(id);
            
        } else {
            sudoTable.egyetrajzol(hx, hy, aktmeret);
              //ctx.fillRect(bo+hx*cellSize+szegely, bo+hy*cellSize+szegely, aktmeret, aktmeret);
            aktmeret++;
            console.log("rajzol");
            console.log(aktmeret);
        }
        }}*/

var cellSize;
var color;
var hole;
var canvas;
var bo;
var kx;
var ky;
const numberOfFrames = 16;
var holes = 5;
var szegely = 2;
var aktmeret;
var ctx;
var w;
var h;
//var kesz = false;
//var cookieValue = document.cookie.replace(/(?:(?:^|.*;\s*)ertek\s*\=\s*([^;]*).*$)|^.*$/, "$1");
//var cookieValue = document.cookie;

function win(){
    document.getElementById('b1').style.visibility = "visible";
    document.getElementById('b2').style.visibility = "visible";
    document.getElementById('b2').style.display = "block";
    document.getElementById('b1').style.display = "block";
     document.getElementById('kep').style.visibility = "visible";
   
    document.getElementById('ny').style.visibility = "visible";
    document.getElementById('kep').style.width = "100%";
    document.getElementById('ny').style.fontSize = "300%";
    document.getElementById('exit').style.visibility = "hidden";
    document.getElementById('exit').style.width = "0px";
    //document.deleteContents('canvas');
}

function creatArray(m){
    color = new Array(m);
    hole = new Array(m);
    for (var i = 0; i < m; i++){
        color[i] = new Array(m);
        hole[i] = new Array(m);
        for (var j = 0; j < m; j++){
            hole[i][j] = false;
            color[i][j] = -1;
        }
    }
}

function creatSudoku(m, i, j){
    if (j == m){
        i++;
        j = 0;
    }
    if (i == m){
        return true;
    }
    var mennyiproba = 0;
    var col = parseInt((Math.random()*100)%m);
    color[i][j] = col; 
    while (volt(i,j) || !creatSudoku(m, i, j+1)){
        mennyiproba++;
        col = (col + 1)%m;
        color[i][j] = col;
        if (mennyiproba == m+1)
            return false;
    }
    return true;
}

function creatHole(m,db){
    var x;
    var y;
    for(var i = 0; i < db; i++){
        x = parseInt((Math.random()*100)%m);
        y = parseInt((Math.random()*100)%m);
        while (hole[x][y]){
            x = parseInt((Math.random()*100)%m);
            y = parseInt((Math.random()*100)%m);
        }
        hole [x][y] = true;
        color[x][y] = -1*Math.random();
        console.log(color[x][y]);
    }
}

function volt (i, j){
    for (var i0 = 0; i0 < m; i0++){
        if (i0 != i && color[i0][j] == color[i][j])
            return true;
    }
    for (var j0 = 0; j0 < m; j0++){
        if (j0 != j && color[i][j0] == color[i][j])
            return true;
    }
    if (m==4 && (i % 2 == 1 && j % 2 == 1) && (color[i-1][j-1] == color[i][j])){
            return true;
        }
    if (m == 4){
        if (i % 2 == 0){
            if (j % 2 == 0){
                if (color[i][j] == color[i+1][j+1])
                    return true;
            }
            else
                if (color[i][j] == color[i+1][j-1])
                    return true;
        }
        else{
            if (j % 2 == 0){
                if (color[i][j] == color[i-1][j+1])
                    return true;
            }
            else
                if (color[i][j] == color[i-1][j-1])
                    return true;
        }
    }
    
    return false;
    
}

function myMove() {
    var elem = document.getElementById("animate"); 
    var pos = 0;
    var id = setInterval(framme, 5);
    function framme() {
        if (pos == 350) {
            clearInterval(id);
        } else {
            pos++; 
            elem.style.top = pos + 'px'; 
            elem.style.left = pos + 'px'; 
        }
    }
}



window.addEventListener('load', function () {
    //myMove();
    //document.getElementById('b1').style.visibility;
    w = window.innerWidth;
    h = window.innerHeight;
    if (h/9 < w/5){
        cellSize = h/9;
        bo = h/18;
    }
    else{
        cellSize = w/5;
        bo = w/10;
    }
    
    
    
    console.log(document.body.clientWidth);
    var ls = parseInt(localStorage.getItem("ertek"));
    switch(ls){
        case 0 :    m = 3;
                    holes = 1;
                    break;
        case 1 :    m = 4;
                    holes = 3;
                    break;
        case 10:    m = 3;
                    holes = 3;
                    break;
        case 11:    m = 4;
                    holes = 5;
                    break;
        default:    m = 4;
                    holes = 5;
    }
    
    
    document.body.addEventListener("click", katt);
    
    creatArray(m);
    creatSudoku(m, 0, 0);
    creatHole(m, holes);
    console.log(localStorage.getItem("ertek"));
    document.body.appendChild(sudoTable.createTable(m, cellSize));
    sudoTable.draw();
    //sudoTable.egyetrajzol();
    document.getElementById('exit').addEventListener('click', function(e) {
    var r = confirm("Biztosan kilépsz?");
    if(r == true){
        console.log("igen");
        document.location.href = "index.html";
    }
    
  }, false);
  
}, false);

