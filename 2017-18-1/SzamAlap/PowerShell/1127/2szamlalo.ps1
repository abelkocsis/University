if (Test-Path C:\Users\fgsdv2\Desktop\szamolo.txt)
{
}
else
{
    New-Item C:\Users\fgsdv2\Desktop\szamolo.txt
    0|Out-File C:\Users\fgsdv2\Desktop\szamolo.txt
}



$beolv=Get-Content C:\Users\fgsdv2\Desktop\szamolo.txt
$szamlalo=[int]$beolv
$szamlalo+=1
Write-Host $szamlalo
$szamlalo|Out-File C:\Users\fgsdv2\Desktop\szamolo.txt