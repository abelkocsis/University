<?php
  include "import.php";
  if (!IsLoggedIn()){
    header('Location: index.php');
}
  if (isset($_GET['page']) && is_numeric($_GET['page']) && $_GET['page'] > 0)
    $page = $_GET['page'];
  else{
    $page = 1;
  }
    

  $honnan = ($page-1)*5;

  $konyvek = lekerdezes($kapcsolat, "SELECT * FROM konyvek WHERE email = :email ORDER BY szerzo", [ ":email" => $email ]);
  $konyvdarab = count($konyvek);
  echo '<br/>';
  echo 'Bejelentkezve: ';
  echo $email;
  echo '<br>';
  echo 'Összes könyved: ';
  echo $konyvdarab;
  
?>

<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <script type="text/javascript" src="./js/lapozas.js"></script>
    <script type="text/javascript" src="./js/ajax.js"></script>
  </head>
  <body>
    <h1>Könyvespolc</h1>
    <h2>Saját könyvek</h2>
    <div>
    <table style="border: 1px solid black; padding: 10px">
    <thead>
    <tr>
      <th>Szerző</th>
      <th>Cím</th>
      <th>Kategória</th>
      <th>Elolvasva</th>
    </tr>

    </thead>
    <tbody id="konyvek">
    <?php $i = 0; ?>
    <?php while ($honnan + $i < $konyvdarab && $i < 5) : ?>
    <?php $konyv = $konyvek[$i+$honnan];?>
      <tr>
        <td id="sz<?= $i ?>"><b><?= $konyv['szerzo'] ?></b></td>
        <td id="c<?= $i ?>"><?= $konyv['cim'] ?></td>
        <td id="k<?= $i ?>"><?= $konyv['kat'] ?></td>
        <td id="eo<?= $i ?>">
          <?php
            if ($konyv['eo']){
              echo "igen";
            }
            else{
              echo "nem";
            }
          ?>
        
        </td>
        <td><button type="button" id="mod" onclick="window.location.href='./modosit.php?kulcs=<?= $konyv['kulcs']?>&page=<?=$page?>'">Módosítás</button></td>
        <td><button type="button" id = "torl" onclick="window.location.href='./torles.php?kulcs=<?= $konyv['kulcs']?>&page=<?=$page?>'">Törlés</button></td>
      </tr>
    <?php $i++; ?>
    <?php endwhile; ?>
    </tbody>
    </table>
    </div>
    <input id="visszalapoz" type="submit" value="Előző" style="display:<?php
      if ($honnan > 0){
        echo "block";
      }
      else{
        echo "none";
      }
    ?>">
    <input id="tovabblapoz" type="submit" value="Következő" style="display:<?php
      if ($honnan + 5 < $konyvdarab){
        echo "block";
      }
      else{
        echo "none";
      }
    ?>">
    
    <br>
    <a href="logout.php">Kijelentkezés</a>
    <a href = "ujkonyv.php">Új könyv felvétele</a>
  </body>
</html>

<?php
  function mod($index='0'){
    echo $index;
  }
?>
