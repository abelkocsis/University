<?php
    include "import.php";
    if ($_POST) {
        $szures = $_POST['sz'];
    }
    else{
        $szures = 1;
    }
    
    $ossz = lekerdezes($kapcsolat, "SELECT * FROM ugynokok", []);
    $kij = array();
    $kij[0] = sizeof($ossz);
    foreach ($ossz as $u){
        if (strstr($u['projekt'], $szures)){
            $kij[$u['id']+1] = true;
        }
        else{
            $kij[$u['id']+1] = false;
        }
    }
    //echo json_encode($konyvekiir);
    echo json_encode($kij);
?>