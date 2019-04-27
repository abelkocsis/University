<?php
//Bejelentkezéshez szükséges

//Kommunikáláshoz a táblával szükséges
include_once("modulok/dbio.php");
include_once('modulok/consts.php');
include_once('modulok/helper.php');
  

$kapcsolat = kapcsolodas($MYSQL_HOST, $MYSQL_USERNAME, $MYSQL_PASSWORD);

?>