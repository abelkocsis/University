#!/bin/sh
#Sz�m�t�g�pes Alapismeretek, M�sodik Beadand�
#Kocsis �bel FGSDV2
hanyadik=0
maxar=0
megoldas=Nincs
keresettgyarto=$1

IFS=';'
while read gyarto tipus alapar; do
	if [ $gyarto = $keresettgyarto ]; then
		if [ $alapar -gt $maxar ]; then
			maxar=$alapar
			megoldas=$tipus
		fi
	fi
done < auto.dat
echo $megoldas
