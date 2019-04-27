<?php
  if (!defined('TOKEN'))
    exit('Közvetlenül nem elérhetõ!');
  
  if(!isset($_SESSION))
  {
    session_start();
  }

  function SetUser($username = null) {
    if (isset($username)) {
      $_SESSION['username'] = $username;
    }
    else {
      unset($_SESSION['username']);
    }
  }
  
  function IsLoggedIn() {
    return isset($_SESSION['username']);
  }

  function GetCurrentMail(){
    if (IsLoggedIn())
      return $_SESSION['username'];
    else
      return '';
  }
?>