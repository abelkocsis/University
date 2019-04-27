// Sakktábla
var sudoTable = {
  cellsInRow: 0,
  cellSize: 0,
  canvasContext: undefined,
  mezovalaszt : false,
  szinvalaszt : false,
  szin: -1,
  hx : 0,
  hy : 0,
   
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
    this.cD("#2874A6", "#F5B041", "#CB4335", "#229954", "#ffffff");
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
            case 0: ctx.fillStyle = "#2874A6";
                    break;
            case 1: ctx.fillStyle = "#F5B041";
                    break;
            case 2: ctx.fillStyle = "#CB4335";
                    break;
            case 3: ctx.fillStyle = "#229954";
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
        ctx.fillRect(bo + 2 * this.cellSize-szegely, bo, 5, this.cellSize*4);
        ctx.fillRect(bo, bo + 2 * this.cellSize-szegely, this.cellSize*4, 5);
    }
    
    /*ctx.fillStyle = "#2874A6";
    ctx.fillRect(bo, bo+(m+1)*this.cellSize, this.cellSize-1, this.cellSize-1);
    ctx.fillStyle = "#F5B041";
    ctx.fillRect(bo+this.cellSize, bo+(m+1)*this.cellSize, this.cellSize-1, this.cellSize-1);
    ctx.fillStyle = "#CB4335";
    ctx.fillRect(bo+this.cellSize*2, bo+(m+1)*this.cellSize, this.cellSize-1, this.cellSize-1);
    if (m == 4){
        ctx.fillStyle = "#229954";
        ctx.fillRect(bo+this.cellSize*3, bo+(m+1)*this.cellSize, this.cellSize-1, this.cellSize-1);
    }*/
  },
    
  update: function(){
      if (!this.mezovalaszt){
          kx -= bo;
          ky -= bo;
          if (kx < 0 || ky < 0){
                kx = -1;
                console.log(-999);
                return;
            }   
            kx = parseInt(kx / cellSize);
            ky = parseInt(ky / cellSize);
    
            if ((kx >= m) || (ky >= m)){
            kx = -1;
            console.log(-999);
            return;
            }
            console.log(kx);
            console.log(ky);
      }
      
      if (this.mezovalaszt && this.szinvalaszt){
          
          return;
      }
      if (this.mezovalaszt){
          kx -= bo;
          ky = ky-bo*2-m*cellSize;
          if (ky >= 0 && parseInt(kx/cellSize) < m  && parseInt(kx/cellSize) >= 0 && ky < this.cellSize){
            console.log(kx);
            console.log(ky);
            this.szin = parseInt(kx/cellSize);
            console.log(this.szin);
            this.kitolt();
              
          }
          else{
              this.mezovalaszt = false;
              //this.update();
              return;
          }
          this.mezovalaszt = false;
          this.hideChoose();
          return;
      }
      if (!hole[kx][ky]){
          this.hideChoose();
          return;
      }
          
      this.hx = kx;
      this.hy = ky;
      this.mezovalaszt = true;
      this.drawChoose();
      
},
              
kitolt: function(){
    var colorvolt = color[hx][hy];
    color[this.hx][this.hy] = this.szin;
    if (volt(this.hy,this.hx)){
        console.log("volt");
        color[this.hx][this.hy] = this.colorvolt;
        return;
    }
}

}

function katt(e){
    var x = e.pageX;
    var y = e.pageY;
    x -= canvas.offsetLeft;
    y -= canvas.offsetTop;
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

var cellSize = 100 ;
var color;
var hole;
var canvas;
var bo = 50;
var kx;
var ky;
var m = document.getCookie("username");
var holes = 3;
var szegely = 5;

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




window.addEventListener('load', function () {
    document.body.addEventListener("click", katt);
    
    creatArray(m);
    creatSudoku(m, 0, 0);
    creatHole(m, holes);
    document.body.appendChild(sudoTable.createTable(m, cellSize));
    sudoTable.draw();
    sudoTable.drawChoose();
    sudoTable.hideChoose();
  
}, false);

