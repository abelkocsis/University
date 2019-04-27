$szam=Random
$szam %= 100
$szam +=1
$bekert=1000


while ($bekert -ne $szam)
{
$bekert= Read-Host
if ($szam -lt $bekert)
{
    Write-Host "A gondolt szám kisebb."
}
else 
{if ($szam -gt $bekert)
{
    Write-Host "A gondol szám nagyobb."
}
}
}
Write-Host "Talált!"