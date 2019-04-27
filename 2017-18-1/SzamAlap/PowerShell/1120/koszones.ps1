$o=Get-Date
$o=$o.Hour
#Write-Host $o
if ($o -lt 9)
{
    Write-Host "Jó reggel!"
}
else {if ($o -gt 21)
{
    Write-Host "Jó estét!"
}
else
{
    Write-Host "Jó napot!"
    
}}
