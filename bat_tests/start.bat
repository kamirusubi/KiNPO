set program=eremeev_kinpo.exe

echo test_01 - ������� ���� �� ���������� > ./outputs/result_1.txt
%program% ./inputs/test_01.txt ./outputs/result_1.txt 

echo test_02 - ���������� ������� �������� ���� > ./outputs/result_2.txt
%program% ./inputs/test_02.txt ./out/result_2.txt > ./outputs/result_2.txt 2>&1


echo test_03 - ������� ���� ���� > ./outputs/result_3.txt
%program% ./inputs/test_03.txt ./outputs/result_3.txt


echo test_04 - 3 ������ �� ������� ����� > ./outputs/result_4.txt
%program% ./inputs/test_04.txt ./outputs/result_4.txt


echo test_05 - ������������ �������� �������� > ./outputs/result_5.txt
%program% ./inputs/test_05.txt ./outputs/result_5.txt


echo test_06 - ����������� ������ > ./outputs/result_6.txt
%program% ./inputs/test_06.txt ./outputs/result_6.txt


echo test_07 - ����������� ���������� �������� > ./outputs/result_7.txt
%program% ./inputs/test_07.txt ./outputs/result_7.txt


echo test_08 - ������������ ��������� > ./outputs/result_8.txt
%program% ./inputs/test_08.txt ./outputs/result_8.txt


echo test_09 - ������ ������� > ./outputs/result_9.txt
%program% ./inputs/test_09.txt ./outputs/result_9.txt


echo test_10 - ������������ ����������������� ����� > ./outputs/result_10.txt
%program% ./inputs/test_10.txt ./outputs/result_10.txt


echo test_11 - ������������ ������������ ����� > ./outputs/result_11.txt
%program% ./inputs/test_11.txt ./outputs/result_11.txt 


echo test_12 - �������� �������� - ������ > ./outputs/result_12.txt
%program% ./inputs/test_12.txt ./outputs/result_12.txt


echo test_13 - �������� �������� - ������ ��� ����� > ./outputs/result_13.txt
%program% ./inputs/test_13.txt ./outputs/result_13.txt


echo test_14 - �������� �������� - ������ ��� ����� > ./outputs/result_14.txt
%program% ./inputs/test_14.txt ./outputs/result_14.txt


echo test_15 - ������� ����������� > ./outputs/result_15.txt
%program% ./inputs/test_15.txt ./outputs/result_15.txt
