<?php
  include "import.php";

  if (isset($_GET['id']))
    $id = $_GET['id'];
  else
    exit();

    $ugynokok = lekerdezes($kapcsolat, "SELECT * FROM ugynokok WHERE id = :id", [ ":id" => $id ]);
    $ugynok = $ugynokok[0];
    $nev = $ugynok['nev'];
    $szelesseg = $ugynok['szelesseg'];
    $hosszusag = $ugynok['hosszusag'];
    $aktiv = $ugynok['aktiv'];
    $projekt = $ugynok['projekt'];
    $feladat = $ugynok['feladat'];



  if ($_POST) {
    $hibak = array();
    $id = trim($_POST['id']);;
    $szelesseg = trim($_POST['szelesseg']);
    $hosszusag = trim($_POST['hosszusag']);
    $aktiv = isset($_POST['aktiv']);
    $projekt = trim($_POST['projekt']);
    $feladat = trim($_POST['feladat']);
    
    include('hibacheck.php');
    


    if (!$hibak) {
      
      if (!$hibak) {
        vegrehajtas($kapcsolat,
        "DELETE FROM `ugynokok` WHERE id = :id", [ ":id" => $id ]);

        vegrehajtas($kapcsolat,
        "INSERT INTO `ugynokok` (`id`, `nev`, `szelesseg`, `hosszusag`, `aktiv`, `projekt`, `feladat`)
        VALUES ('{$id}', '{$nev}', '{$szelesseg}', '{$hosszusag}', '{$aktiv}', '{$projekt}', '{$feladat}');");
      }
      
    }
    
  }
?>
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
  </head>
  <body>
    <h1><?=$nev?></h1>
    <ul>
    <div id="hibak">
    <?php if (isset($hibak)) : ?>
    <?php foreach ($hibak as $hiba) : ?>
      <li><?= $hiba; ?></li>
    <?php endforeach;?>
    <?php endif ; ?>
    </div>
    </ul>
    <form action="" method="post">
      <table >
        <tr>
          <input name="id" type="hidden" value="<?=$id?>" >
          <td>Szélesség</td>
          <td><input type=text name="szelesseg" value="<?=$szelesseg?>"></td>
        </tr>
        <tr>
          <td>Hosszúság:</td>
          <td><input type="text" name="hosszusag" value="<?=$hosszusag?>"></td>
        <tr>
          <td>Aktív:</td>
          <td><input type="checkbox" name="aktiv" 
          <?php
            if ($aktiv)
              echo "checked";
          ?>
          ></td>
        <tr>
          <td>Projekt:</td>
          <td><input type='text' name="projekt" value="<?=$projekt?>">
          </td>
        <tr>
          <td>Feladat:</td>
          <td><input type="text" name="feladat" value="<?=$feladat?>" >
        <tr>
          <td colspan = 2><input type="submit" value="Submit"></td>
        </tr>
      </table>
    </form>
    <p><a href="lista.php">Mégsem</a></p>
  </body>
</html>
<?php if ($_POST && !$hibak)
    header("Location: lista.php?");

?>
