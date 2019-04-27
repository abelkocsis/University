<?php
  define('TOKEN', 'Védelem');
  include_once('modulok/session_login.php');
  if (IsLoggedIn()) {
    header('Location: index.php');
    exit();
  }
  include_once('modulok/consts.php');
  include_once("modulok/dbio.php");
  //-------------------------
  $hibak = array();
  if ($_POST) {
    $email = trim($_POST['email']);
    $jelszo = $_POST['jelszo'];
    $jelszo2 = $_POST['jelszo2'];
    $nev = trim($_POST['nev']);
    
    if ($nev == '') {
      $hibak[] = 'A név megadása kötelező!';
    }
    if ($email == '') {
      $hibak[] = 'E-mail megadása kötelező!';
    }
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)){
      $hibak[] = 'E-mail cím legyen e-mail formátumú!';
    }
    if ($jelszo == '') {
      $hibak[] = 'A jelszó kötelező!';
    }
    if ($jelszo != $jelszo2) {
      $hibak[] = 'A jelszavak nem egyeznek!';
    }
    if (strlen((string)$jelszo) < 6){
      $hibak[] = 'A jelszó legyen legalább 6 karakter hosszú!';
    }
    
    
    if (!$hibak) {
      $kapcsolat = kapcsolodas($MYSQL_HOST, $MYSQL_USERNAME, $MYSQL_PASSWORD);
      $felhasznalok = lekerdezes($kapcsolat, "SELECT * FROM felhasznalok WHERE email = :email", [ ":email" => "${email}" ]);
        
      if ($felhasznalok) {
        $hibak[] = 'Már létezik ilyen felhasználói név!';
      }
      if (!$hibak) {
        $jelszo = md5($jelszo);
        vegrehajtas($kapcsolat,
        "INSERT INTO `felhasznalok` (`email`, `nev`, `jelszo`)
        VALUES ('{$email}', '{$nev}', '{$jelszo}');");
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
    <h2>Regisztráció</h2>
    
    <ul>
    <?php foreach ($hibak as $hiba) : ?>
      <li><?= $hiba; ?></li>
    <?php endforeach;?>
    </ul>
    <form action="" method="post">
      <table >
        <tr>
          <td>Név:</td>
          <td><input type="string" name="nev"></td>
        <tr>
          <td>E-mail cím:</td>
          <td><input type="string" name="email"></td>
        </tr>
        <tr>
          <td>Jelszó:</td>
          <td><input type="password" name="jelszo" ></td>
        <tr>
        <tr>
          <td>Jelszó még egyszer:</td>
          <td><input type="password" name="jelszo2"></td>
        <tr>
        
        <tr>
          <td colspan = 2><input type="submit" value="Regisztráció"></td>
        </tr>
      </table>
      
    </form>
    <?php if ($_POST && !$hibak) : ?>
        <?php header("Location: index.php");?>
    <?php endif; ?>
    <p><a href="index.php">Vissza</a></p>
  </body>
</html>