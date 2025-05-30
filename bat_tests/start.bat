set program=eremeev_kinpo.exe

echo test_01 - Входной файл не существует > .\actual_outputs\result_1.txt
%program% .\inputs\test_01.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_1.txt 


echo test_02 - Невозможно создать выходной файл > .\actual_outputs\result_2.txt
%program% .\inputs\test_02.txt .\out\result_2.txt > .\actual_outputs\tmp.txt 2>&1
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_2.txt


echo test_03 - Входной файл пуст > .\actual_outputs\result_3.txt
%program% .\inputs\test_03.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_3.txt


echo test_04 - 3 строки во входном файле > .\actual_outputs\result_4.txt
%program% .\inputs\test_04.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_4.txt


echo test_05 - Недопустимая корневая операция > .\actual_outputs\result_5.txt
%program% .\inputs\test_05.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_5.txt


echo test_06 - Неизвестный символ > .\actual_outputs\result_6.txt
%program% .\inputs\test_06.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_6.txt


echo test_07 - Неизвестная комбинация символов > .\actual_outputs\result_7.txt
%program% .\inputs\test_07.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_7.txt


echo test_08 - Недостаточно операндов > .\actual_outputs\result_8.txt
%program% .\inputs\test_08.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_8.txt


echo test_09 - Лишний операнд > .\actual_outputs\result_9.txt
%program% .\inputs\test_09.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_9.txt


echo test_10 - Используется шестнадцатеричное число > .\actual_outputs\result_10.txt
%program% .\inputs\test_10.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_10.txt


echo test_11 - Используется восьмеричное число > .\actual_outputs\result_11.txt
%program% .\inputs\test_11.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_11.txt 


echo test_12 - Корневая операция - меньше > .\actual_outputs\result_12.txt
%program% .\inputs\test_12.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_12.txt


echo test_13 - Корневая операция - меньше или равно > .\actual_outputs\result_13.txt
%program% .\inputs\test_13.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_13.txt


echo test_14 - Корневая операция - больше или равно > .\actual_outputs\result_14.txt
%program% .\inputs\test_14.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_14.txt


echo test_15 - Большая вложенность > .\actual_outputs\result_15.txt
%program% .\inputs\test_15.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_15.txt


del .\actual_outputs\tmp.txt