$kiolvasott=Get-Process|Select-Object -Property WS
#Write-Host $kiolvasott[1]
#Write-Host $kiolvasott[1].WS
$osszeg=0;

for ($i=0; $i -lt $kiolvasott.Length; $i++)
{
    $osszeg+=$kiolvasott[$i].WS
}
Write-Host $osszeg
#$valami=$kiolvasott[1]
#Write-Host $valami