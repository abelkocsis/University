<?php
function kapcsolodas($kapcsolati_szoveg, $felhasznalonev = '', $jelszo = '') {
  $pdo = new PDO($kapcsolati_szoveg, $felhasznalonev, $jelszo);
  $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  return $pdo;
}

function lekerdezes($kapcsolat, $sql, $parameterek = []) {
  $stmt = $kapcsolat->prepare($sql);
  $stmt->execute($parameterek);
  return $stmt->fetchAll();
}

function vegrehajtas($kapcsolat, $sql, $parameterek = []) {
  return $kapcsolat
    ->prepare($sql)
    ->execute($parameterek);
}

// használata
$kapcsolat = kapcsolodas("sqlite:./adatok/minishop.sqlite");
vegrehajtas($kapcsolat, "DROP TABLE IF EXISTS termekek;");
vegrehajtas($kapcsolat, "DROP TABLE IF EXISTS kategoriak;");
vegrehajtas($kapcsolat, "DROP TABLE IF EXISTS rendelesek;");

vegrehajtas($kapcsolat, "
CREATE TABLE `termekek` (
  `id`    INTEGER PRIMARY KEY AUTOINCREMENT,
  `kategoriaid`  INT NOT NULL,
  `nev`   TEXT NOT NULL);
");

vegrehajtas($kapcsolat, "
CREATE TABLE `kategoriak` (
  `id`    INTEGER PRIMARY KEY AUTOINCREMENT,
  `nev`   TEXT NOT NULL);
");

vegrehajtas($kapcsolat, "
CREATE TABLE `rendelesek` (
  `id`    INTEGER PRIMARY KEY AUTOINCREMENT,
  `vevo`   TEXT NOT NULL,
  `cim`   TEXT NOT NULL,
  `aruk`   TEXT NOT NULL,
  `ideje`   DATETIME NOT NULL);
");

vegrehajtas($kapcsolat, "
INSERT INTO `kategoriak` (`id`, `nev`)
VALUES
(1, 'Zöldség'),
(2, 'Gyümölcs'),
(3, 'Pálinka');
");

vegrehajtas($kapcsolat, "
INSERT INTO `termekek` (`id`, `kategoriaid`, `nev`)
VALUES
(1, 1, 'Saláta'),
(2, 1, 'Hagyma'),
(3, 1, 'Zeller');
");

vegrehajtas($kapcsolat, "
INSERT INTO `termekek` (`id`, `kategoriaid`, `nev`)
VALUES
(4, 2, 'Alma'),
(5, 2, 'Körte'),
(6, 2, 'Szilva'),
(7, 2, 'Barack');
");

vegrehajtas($kapcsolat, "
INSERT INTO `termekek` (`id`, `kategoriaid`, `nev`)
VALUES
(8, 3, 'Almás'),
(9, 3, 'Körtés'),
(10, 3, 'Szilvás'),
(11, 3, 'Barackos');
");


vegrehajtas($kapcsolat, "INSERT INTO `rendelesek` (`id`, `vevo`, `cim`, `aruk`, `ideje`) VALUES (1, 'Metal', 'Elios Soros utca 12', '[2,5,6]', '2018.04.12 19:18:16');");


echo '<pre>';
$result = lekerdezes($kapcsolat, "SELECT * FROM kategoriak");
print_r($result);
$result = lekerdezes($kapcsolat, "SELECT * FROM termekek");
print_r($result);
$result = lekerdezes($kapcsolat, "SELECT * FROM rendelesek");
print_r($result);
echo '/<pre>';

?>

