

function fakt()
{
  param($m)
  
  $F=1
  Write-Host -NoNewline $m!=1
  for ($i = 2; $i -le $m; $i++)
    {
        Write-Host -NoNewline *$i
        $F=$F*$i
    }

        Write-Host =$F

}
fakt 6