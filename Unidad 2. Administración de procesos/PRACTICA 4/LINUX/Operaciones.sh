#!/bin/sh
clear
echo –n “Introduce dos valores númericos separados por espacios”
read var1 var2
echo “Los valores son: “
echo var1=$var1
echo var2=$var2
#
if [ $var1 -lt $var2 ]
then
        echo “$var1 menor que $var2”
        while [ $var1 -lt $var2 ]
        do
            echo contador=$var1
            var1=`expr $var1 + 1`
        done
else
        echo “$var1 mayor o igual que $var2”
        case $var2 in
                    10) echo “Fui un 10”;;
                    20) echo “Fui un 20”;;
                    Otro) echo “Otro valor”;;
        esac
fi