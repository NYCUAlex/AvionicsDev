clear
clc
fileID = fopen('test_data1.txt','a');
data1 = 123.456;
data2 = 789;
% data = append(data1,data2,',');
data = strcat(data1,data2);
fprintf(fileID,'%d,',data);
% fprintf(fileID,'\b');%\b not work
fprintf(fileID,'\n');
fclose(fileID);clc