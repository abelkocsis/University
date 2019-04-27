<?php
  include "import.php";
  //-------------------------
  if (!IsLoggedIn()){
    header('Location: index.php');
}
  $hibak = array();

  if (isset($_GET['kulcs']))
    $kulcs = $_GET['kulcs'];
  else
    exit('Válasszon <a href="index.php">könyvet</a>!');

    echo $kulcs;
    //$konyvek = lekerdezes($kapcsolat, "SELECT * FROM konyvek WHERE kulcs = :kulcs", [ ":kulcs" => $kulcs ]);

    vegrehajtas($kapcsolat,
        "DELETE FROM `konyvek` WHERE kulcs = :kulcs", [ ":kulcs" => $kulcs ]);
    if (isset($_GET['page'])){
        $page = $_GET['page'];
        header("Location: listazo.php?page=$page");
    }  
    else{
      header('Location: listazo.php');
    }
?>
