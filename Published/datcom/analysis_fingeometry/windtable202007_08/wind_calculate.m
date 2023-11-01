clear
clc
%% wind data
n = 1;
abs_speed = 0;
for i = 1:62
    filename = i+".csv";
    wind = readmatrix(filename);
    for j = 1:10
        if wind(j,1)<120
            north_speed(n,1) = wind(j,2);
            east_speed(n,1) = wind(j,3);
            abs_speed = abs_speed + norm([north_speed(n,1) east_speed(n,1)],2);
            n=n+1;           
        end
        
    end
end
avg_speed = abs_speed/length(north_speed);