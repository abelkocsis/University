<?php
  define('TOKEN', 'Védelem');
  include_once('modulok/session_login.php');
  if (IsLoggedIn()) {
    header('Location: indexvolt.php');
    exit();
  }
  
  include_once("modulok/dbio.php");
  include_once('modulok/consts.php');
  //-------------------------
  $hibak = array();
  if ($_POST) {
    $email = trim($_POST['email']);
    $jelszo = $_POST['jelszo'];
    
    if ($email == '') {
      $hibak[] = 'Az e-mail kötelező!';
    }
    if ($jelszo == '') {
      $hibak[] = 'A jelszó kötelező!';
    }
    
    if (!$hibak) {
      $kapcsolat = kapcsolodas($MYSQL_HOST, $MYSQL_USERNAME, $MYSQL_PASSWORD);
      $felhasznalok = lekerdezes($kapcsolat, "SELECT * FROM felhasznalok WHERE email = :email", [ ":email" => "${email}" ]);
      
      if (count($felhasznalok) != 1) {
        $hibak[] = 'Hibás e-mail vagy jelszó!';
      }
      else {
        $felhasznalo = $felhasznalok[0];
        if (md5($_POST['jelszo']) != $felhasznalo['jelszo']) {
          $hibak[] = 'Hibás email vagy jelszó!';
        }
      }
    }
    
    if (!$hibak) {
      SetUser($email);
      header('Location: index.php');
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
    <h2>Bejelentkezés</h2>
    
    <ul>
    <?php foreach ($hibak as $hiba) : ?>
      <li><?= $hiba; ?></li>
    <?php endforeach;?>
    </ul>
    <form action="" method="post">
      <table >
        <tr>
          <td>E-mail cím:</td>
          <td><input type="email" name="email"></td>
        </tr>
        <tr>
          <td>Jelszó:</td>
          <td><input type="password" name="jelszo"></td>
        <tr>
          <td colspan = 2><input type="submit" value="Belépés"></td>
        </tr>
      </table>
    </form>
    <p><a href="index.php">Vissza</a></p>
  </body>
</html>