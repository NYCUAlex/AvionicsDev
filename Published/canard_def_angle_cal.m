clear
clc
close all
%% deflection canard
T = [-1/4 -1/4 -1/4 -1/4;
      1/4  1/4 -1/4 -1/4;
     -1/4  1/4  1/4 -1/4];
invT = T'*inv(T*T')
syms phi
% phi = 0;
T2 = [-1  cosd(phi)-sind(phi) -sind(phi)-cosd(phi);
     -1  cosd(phi)+sind(phi) -sind(phi)+cosd(phi);
     -1 -cosd(phi)+sind(phi)  sind(phi)+cosd(phi);
     -1 -cosd(phi)-sind(phi)  sind(phi)-cosd(phi)];
simplify(pinv(T2))

delta1234 = [10;10;10;10];
deltap = T*delta1234