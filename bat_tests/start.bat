set program=eremeev_kinpo.exe

echo test_01 - ������� ���� �� ���������� > .\actual_outputs\result_1.txt
%program% .\inputs\test_01.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_1.txt 


echo test_02 - ���������� ������� �������� ���� > .\actual_outputs\result_2.txt
%program% .\inputs\test_02.txt .\out\result_2.txt > .\actual_outputs\tmp.txt 2>&1
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_2.txt


echo test_03 - ������� ���� ���� > .\actual_outputs\result_3.txt
%program% .\inputs\test_03.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_3.txt


echo test_04 - 3 ������ �� ������� ����� > .\actual_outputs\result_4.txt
%program% .\inputs\test_04.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_4.txt


echo test_05 - ������������ �������� �������� > .\actual_outputs\result_5.txt
%program% .\inputs\test_05.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_5.txt


echo test_06 - ����������� ������ > .\actual_outputs\result_6.txt
%program% .\inputs\test_06.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_6.txt


echo test_07 - ����������� ���������� �������� > .\actual_outputs\result_7.txt
%program% .\inputs\test_07.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_7.txt


echo test_08 - ������������ ��������� > .\actual_outputs\result_8.txt
%program% .\inputs\test_08.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_8.txt


echo test_09 - ������ ������� > .\actual_outputs\result_9.txt
%program% .\inputs\test_09.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_9.txt


echo test_10 - ������������ ����������������� ����� > .\actual_outputs\result_10.txt
%program% .\inputs\test_10.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_10.txt


echo test_11 - ������������ ������������ ����� > .\actual_outputs\result_11.txt
%program% .\inputs\test_11.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_11.txt 


echo test_12 - �������� �������� - ������ > .\actual_outputs\result_12.txt
%program% .\inputs\test_12.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_12.txt


echo test_13 - �������� �������� - ������ ��� ����� > .\actual_outputs\result_13.txt
%program% .\inputs\test_13.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_13.txt


echo test_14 - �������� �������� - ������ ��� ����� > .\actual_outputs\result_14.txt
%program% .\inputs\test_14.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_14.txt


echo test_15 - ������� ����������� > .\actual_outputs\result_15.txt
%program% .\inputs\test_15.txt .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_15.txt


del .\actual_outputs\tmp.txt