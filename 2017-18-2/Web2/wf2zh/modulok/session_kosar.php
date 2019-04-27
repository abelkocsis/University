<?php
  if (!defined('TOKEN'))
    exit('Közvetlenül nem elérhetõ!');

  if(!isset($_SESSION))
  {
    session_start();
  }

  function GetKosar() {
    if (isset($_SESSION['kosar'])) {
      return $_SESSION['kosar'];
    }
    else {
      return array();
    }
  }

  function SetKosar($kosar) {
    $_SESSION['kosar'] = $kosar;
  }

  function EmptyKosar() {
    $_SESSION['kosar'] = array();
  }
?>