<?php
    include "import.php";
    if ($_POST) {
        $page = $_POST['page'];
    }
    else{
        $page = 1;
    }
    $honnan = ($page-1)*5;
    
    $konyvek = lekerdezes($kapcsolat, "SELECT * FROM konyvek WHERE email = :email ORDER BY szerzo LIMIT 5 OFFSET $honnan ", [ ":email" => $email ]);
    $osszkonyv = lekerdezes($kapcsolat, "SELECT * FROM konyvek WHERE email = :email", [ ":email" => $email ]);
    $i = 0;
    $konyvkiir = array();
    $konyvkiir[0]['osszkonyvszam'] = count($osszkonyv);
    foreach ($konyvek as $k){
        $konyvkiir[$i]['szerzo'] = $k['szerzo'];
        $konyvkiir[$i]['cim'] = $k['cim'];
        $konyvkiir[$i]['kat'] = $k['kat'];
        if ($k['eo']){
            $konyvkiir[$i]['eo']="igen";
        }
        else{
            $konyvkiir[$i]['eo']="nem";
        }
        $konyvkiir[$i]['kulcs']= $k['kulcs'];

        $kulcs = $k['kulcs'];
        
        $szoveg1 = "window.location.href='./modosit.php?kulcs=$kulcs&page=$page'";
        $konyvkiir[$i]['mod']= $szoveg1;
        
        $szoveg2 = "window.location.href='./torles.php?kulcs=$kulcs&page=$page'";
        $konyvkiir[$i]['torl']= $szoveg2;






        $i++;
    }
    //echo json_encode($konyvekiir);
    echo json_encode($konyvkiir);
?>