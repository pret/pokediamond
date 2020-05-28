..\..\..\convert\exceltool\exceltabconv dpmusfade.xls
awk -f dpmusfade.awk dpmusfade.txt > dpmusfade.dat
del dpmusfade.txt
