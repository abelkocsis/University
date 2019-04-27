<?php
    if (!isset($szerzo) || $szerzo==""){
      $hibak[]="Szerző megadása kötelező!";
    }

    if (!isset($cim) || $cim==""){
      $hibak[]="Cím megadása kötelező!";
    }

    if (isset($osz) && strlen((string)$osz) > 0){
      if (!preg_match("/^[\d]+$/", $osz))
        $hibak[]="Oldalszámnak egész számnak kell lennie!";
    }
    if (isset($ISBN) && strlen((string)$ISBN) > 0){
      if (!preg_match("/^[\d]+$/", $ISBN)){
        $hibak[]="ISBN számnak számsornak kell lennie!";
      }
     
      if (!(strlen((string)$ISBN) == 10 || strlen((string)$ISBN) == 13)){
        $hibak[]="ISBN szám legyen 10 vagy 13 számjegyű!";
      }
    }


?>