<?php

    if (!isset($szelesseg) || $szelesseg==""){
      $hibak[]="A szélesség kötelező";
    }
    if (!is_numeric($szelesseg)){
      $hibak[]="A szélesség nem szám";
    }
    if (!isset($hosszusag) || $hosszusag==""){
      $hibak[]="A hosszúság kötelező";
    }
    if (!is_numeric($hosszusag)){
      $hibak[]="A hosszúság nem szám";
    }
    if (!isset($projekt) || $projekt==""){
      $hibak[]="A projekt kötelező";
    }
    if (!isset($feladat) || $feladat==""){
      $hibak[]="A feladat kötelező";
    }


?>