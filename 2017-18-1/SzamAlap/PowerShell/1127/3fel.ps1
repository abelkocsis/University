param($hanyszor)
$val=Random
$val%=100
Write-Host $val
Write-Host $hanyszor


for ($i = 0; $i -le $hanyszor; $i++)
{
    $ran=Random
    $ran%=100
    
    while ($val -gt $ran)
    {
        Write-Host -NoNewline "-"
        $ran=Random
        $ran%=100
    }
    Write-Host " "
}