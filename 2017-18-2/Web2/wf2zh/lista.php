<?php
  include "import.php";
  

  $aktiv = lekerdezes($kapcsolat, "SELECT * FROM ugynokok WHERE aktiv = :aktiv", [ ":aktiv" => 1 ]);
  $inaktiv = lekerdezes($kapcsolat, "SELECT * FROM ugynokok WHERE aktiv = :aktiv", [ ":aktiv" => 0 ]);
  $osszes = lekerdezes($kapcsolat, "SELECT * FROM ugynokok", []);
  
?>

<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <script type="text/javascript" src="./js/js.js"></script>
    <script type="text/javascript" src="./js/ajax.js"></script>
    <link rel="stylesheet" type="text/css" href="http://webprogramozas.inf.elte.hu/webfejl2/gyak/style.css">
  </head>
  <body>
  <div class="container">
    <input id="szuro" type="text">
    <div class="row">
        <div class="col">
            <h2>Aktív ügynökök</h2>
            <table class="table table-sm aktiv" >
            <thead class="thead-dark">
            <tr>
              <th>Név</th>
              <th>Koordináták</th>
              <th>Projekt</th>
              <th>Feladat</th>
              <th></th>
            </tr>
            </thead>
            <tbody>
              <?php foreach ($aktiv as $a) : ?>
                <tr data-id="<?=$a['id']?>">
                <td><a href = "modosit.php?id=<?=$a['id']?>"><?=$a['nev']?></a></td>
                <td><?=$a['szelesseg']?>,<?=$a['hosszusag']?></td>
                <td><?=$a['projekt']?></td>
                <td><?=$a['feladat']?></td>
                <td><a href = "inaktivizal.php?id=<?=$a['id']?>">Off</a></td>
                </tr>
              <?php endforeach ; ?>
            </tbody>
            </table>

            <h2>Inaktív ügynökök</h2>
            <table class="table table-sm inaktiv">
            <thead class="thead-dark">
            <tr>
              <th>Név</th>
              <th>Koordináták</th>
              <th>Projekt</th>
              <th>Feladat</th>
              <th></th>
            </tr>
            </thead>
            <tbody>
              <?php foreach ($inaktiv as $a) : ?>
                <tr data-id="<?=$a['id']?>">
                <td><a href = "modosit.php?id=<?=$a['id']?>"><?=$a['nev']?></a></td>
                <td><?=$a['szelesseg']?>,<?=$a['hosszusag']?></td>
                <td><?=$a['projekt']?></td>
                <td><?=$a['feladat']?></td>
                <td><a href = "aktivizal.php?id=<?=$a['id']?>">On</a></td>
                </tr>
              <?php endforeach ; ?>
            </tbody>
            </table>

        </div>
        <div class="col">
            <h2>Térkép</h2>
            <div class="terkep">
              <?php foreach ($osszes as $a) : ?>
                <span data-id="<?=$a['id']?>" style="transform: translate(<?=$a['hosszusag']?>px,<?=$a['szelesseg']?>px)"></span>
              <?php endforeach ; ?>
            </div>

            <h2>Fizikai állapot</h2>
            <ul class="allapot list-group">
                <li class="pulzus list-group-item d-flex justify-content-between align-items-center">
                    Pulzus
                    <span class="badge badge-primary badge-pill">-</span>
                </li>
                <li class="vernyomas list-group-item d-flex justify-content-between align-items-center">
                    Vérnyomás
                    <span class="badge badge-primary badge-pill">-</span>
                </li>
                <li class="faradtsag list-group-item d-flex justify-content-between align-items-center">
                    Fáradtság
                    <span class="badge badge-primary badge-pill">-</span>
                </li>
            </ul>
        </div>
    </div>
</div>
    
    
    
  </body>
</html>

