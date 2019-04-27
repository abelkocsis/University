<?php
    include "import.php";
    if (isset ($_GET['id']))
      $id = $_GET['id'];
    else
     header("Location: lista.php");
    
    $ugynokok = lekerdezes($kapcsolat, "SELECT * FROM ugynokok WHERE id = :id", [ ":id" => $id ]);
    $ugynok = $ugynokok[0];

    $aktiv = 1;
    $nev = $ugynok['nev'];
    $szelesseg = $ugynok['szelesseg'];
    $hosszusag = $ugynok['hosszusag'];
    $projekt = $ugynok['projekt'];
    $feladat = $ugynok['feladat'];


    vegrehajtas($kapcsolat,
        "DELETE FROM `ugynokok` WHERE id = :id", [ ":id" => $id ]);
    vegrehajtas($kapcsolat,
        "INSERT INTO `ugynokok` (`id`, `nev`, `szelesseg`, `hosszusag`, `aktiv`, `projekt`, `feladat`)
        VALUES ('{$id}', '{$nev}', '{$szelesseg}', '{$hosszusag}', '{$aktiv}', '{$projekt}', '{$feladat}');");
    header("Location: lista.php");
?>