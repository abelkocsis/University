<?php
    include "import.php";
    if (IsLoggedIn()){
        header('Location: listazo.php');
    }
    $konyvek = lekerdezes($kapcsolat, "SELECT * FROM konyvek", []);
    $konyvdarab = count($konyvek);
    $felhasznalok = lekerdezes($kapcsolat, "SELECT * FROM felhasznalok", []);
    $felhdarab = count($felhasznalok);
?>
<h1>Könyvespolc</h1>
<p>Üdvözöljük az oldalon!</p>
<p>
    Jelenleg az alkalmazásban <?= $felhdarab?> felhasználó <?=$konyvdarab?> könyvet tárol.
</p>
<a href = "./login.php">Bejelentkezés</a>
<a href="./reg.php">Regisztráció</a>
