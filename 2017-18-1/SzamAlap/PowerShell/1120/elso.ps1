#parma($paraize)
$F=1
$N=Read-Host "n=?"
Write-Host  -NoNewline $N
Write-Host  -NoNewline !=1
for ($i = 2; $i -le $N; $i++)
{
    Write-Host -NoNewline *$i
    $F=$F*$i
}
Write-Host =$F
Write-Host $paraize

