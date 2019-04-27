<?php
  include "import.php";
  //-------------------------
  if (!IsLoggedIn()){
    header('Location: index.php');
}
  if ($_POST) {
    $hibak = array();
    $email = GetCurrentMail();
    $szerzo = trim($_POST['szerzo']);
    $cim = trim($_POST['cim']);
    $osz = trim($_POST['osz']);
    $kat = trim($_POST['kat']);
    $eo = isset($_POST["eo"]);
    $ISBN = $_POST['ISBN'];
    $kulcs = time();
    
    include('hibacheck.php');

    if (!$hibak) {
      
      if (!$hibak) {
        vegrehajtas($kapcsolat,
        "INSERT INTO `konyvek` (`email`, `szerzo`, `cim`, `osz`, `kat`, `ISBN`, `eo`, `kulcs`)
        VALUES ('{$email}', '{$szerzo}', '{$cim}', '{$osz}', '{$kat}', '{$ISBN}', '{$eo}', '{$kulcs}');");
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
    <h1>Könyvespolc</h1>
    <h2>Új könyv hozzáadása</h2>
    <ul>
    <?php if (isset($hibak)) : ?>
    <?php foreach ($hibak as $hiba) : ?>
      <li><?= $hiba; ?></li>
    <?php endforeach;?>
    <?php endif ; ?>
    </ul>
    Új könyv adtai:
    <form action="" method="post">
      <table >
        <tr>
          <td>Szerző</td>
          <td><input type=text name="szerzo"></td>
        </tr>
        <tr>
          <td>Cím:</td>
          <td><input type="text" name="cim"></td>
        <tr>
          <td>Oldalszám:</td>
          <td><input type="text" name="osz"></td>
        <tr>
          <td>Kategoria:</td>
          <td><input list='kat' name="kat">
                <datalist id='kat'> 
                    <option value="Szépirodalom">
                    <option value="Szakirodalom">
                    <option value="Könnyűirodalom">
                    <option value="Egyéb">
                </datalist>
          </td>
        <tr>
          <td>ISBN szám:</td>
          <td><input type="text" name="ISBN"></td>
        <tr>
          <td>Elolvasva:</td>
          <td><input type="checkbox" name="eo"></td>
        <tr>
          <td colspan = 2><input type="submit" value="Mentés"></td>
        </tr>
      </table>
    </form>
    <p><a href="listazo.php">Mégsem</a></p>
  </body>
</html>
<?php if ($_POST && !$hibak)
    header('Location: listazo.php');
?>
