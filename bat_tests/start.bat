set program=eremeev_kinpo.exe

echo test_01 - Входной файл не существует > ./outputs/result_1.txt
%program% ./inputs/test_01.txt ./outputs/result_1.txt 

echo test_02 - Невозможно создать выходной файл > ./outputs/result_2.txt
%program% ./inputs/test_02.txt ./out/result_2.txt > ./outputs/result_2.txt 2>&1


echo test_03 - Входной файл пуст > ./outputs/result_3.txt
%program% ./inputs/test_03.txt ./outputs/result_3.txt


echo test_04 - 3 строки во входном файле > ./outputs/result_4.txt
%program% ./inputs/test_04.txt ./outputs/result_4.txt


echo test_05 - Недопустимая корневая операция > ./outputs/result_5.txt
%program% ./inputs/test_05.txt ./outputs/result_5.txt


echo test_06 - Неизвестный символ > ./outputs/result_6.txt
%program% ./inputs/test_06.txt ./outputs/result_6.txt


echo test_07 - Неизвестная комбинация символов > ./outputs/result_7.txt
%program% ./inputs/test_07.txt ./outputs/result_7.txt


echo test_08 - Недостаточно операндов > ./outputs/result_8.txt
%program% ./inputs/test_08.txt ./outputs/result_8.txt


echo test_09 - Лишний операнд > ./outputs/result_9.txt
%program% ./inputs/test_09.txt ./outputs/result_9.txt


echo test_10 - Используется шестнадцатеричное число > ./outputs/result_10.txt
%program% ./inputs/test_10.txt ./outputs/result_10.txt


echo test_11 - Используется восьмеричное число > ./outputs/result_11.txt
%program% ./inputs/test_11.txt ./outputs/result_11.txt 


echo test_12 - Корневая операция - меньше > ./outputs/result_12.txt
%program% ./inputs/test_12.txt ./outputs/result_12.txt


echo test_13 - Корневая операция - меньше или равно > ./outputs/result_13.txt
%program% ./inputs/test_13.txt ./outputs/result_13.txt


echo test_14 - Корневая операция - больше или равно > ./outputs/result_14.txt
%program% ./inputs/test_14.txt ./outputs/result_14.txt


echo test_15 - Большая вложенность > ./outputs/result_15.txt
%program% ./inputs/test_15.txt ./outputs/result_15.txt
