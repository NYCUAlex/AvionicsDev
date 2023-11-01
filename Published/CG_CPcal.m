clear 
close all
clc 
%% calculate CG
t = 0:1:15;%(s)
%fixed parts:mass(kg),CG(m)
Nose_mass = 1.72;
payload1_mass = 10;                                              %%%%
Avionic_mass = 2.94;
payload2_mass = 70;                                             %%%%
N2O_tank_mass = 18;                                             %all = 18
Connect_mass = 0.88;
payload3_mass = 10;                                             %%%%
combus_mass = 39.7;                                             %origin,lightening = 39.7 , highreg = 29.5
fin_mass = 10;

Nose_x = 0.53951;
payload1_x = 0.53951;
Avionic_x = 1.366;
payload2_x = 1.366;
N2O_tank_x = 3.136;
Connect_x = 4.556;
payload3_x = 4.556; 
combus_x = 5.556;                                               %origin,lightening = 5.556  ,highreg = 5.031
fin_x = 5.972;

%N2O:mass(kg),CG(m)
N2O_area = 0.26^2*pi/4;%internal section area(m^2)
N2O_long = 2.35;%long(m)
N2O_massi = 91;%initial mass(kg)                                %all = 91
N2O_massf = 17;%final mass(kg)                                  %all = 17
N2O_xi = 0.866+1+2.54-N2O_long/2;%initial CG position(m)

%fuel(kg),CG(m)
Fuel_massi = 60.9;%initial mass(kg)                             %origin = 60.9 ,lightening = 36.5 , highreg = 18
Fuel_massf = 48.6;%final mass(kg)                               %origin = 48.6 ,lightening = 24.3 , highreg = 5.7
Fuel_x0 = 0.866+1+2.54+0.3+1.7/2;%initial CG position(m)

%calculate fixed mass,CG
fixed_mass = Nose_mass+payload1_mass+Avionic_mass+...
    payload2_mass+N2O_tank_mass+Connect_mass+payload3_mass+...
    combus_mass+4*fin_mass;
fixed_x = (Nose_mass*Nose_x+payload1_mass*payload1_x+...
    Avionic_mass*Avionic_x+payload2_mass*payload2_x+...
    N2O_tank_mass*N2O_tank_x+Connect_mass*Connect_x+...
    payload3_mass*payload3_x+combus_mass*combus_x+...
    4*fin_mass*fin_x)/fixed_mass;

%calculate N2O mass,CG
N2O_mass = N2O_massi - (N2O_massi-N2O_massf)/15*t;
N2O_x = N2O_xi + N2O_long/2 - (N2O_long/N2O_massi.*N2O_mass)/2;

%calculate fuel mass,CG
Fuel_mass = Fuel_massi - (Fuel_massi-Fuel_massf)/15*t;
Fuel_x = Fuel_x0;

%calculate total mass,CG
m = fixed_mass+N2O_mass+Fuel_mass;
CG = (fixed_mass.*fixed_x + N2O_mass.*N2O_x + Fuel_mass.*Fuel_x)./m;%

%% calculate CP(by barrowman's method)
% %assumption:1.AOA<10    2.speed<<1Mach   3.flow rate not change rapidly
% %4.L/D>>1   5.axially symmetric  
% LN = 0.866;%length of nose
% d = 0.265;%diameter at base of nose
% dF = 0.265;%diameter at front of transition
% dR = 0.26499;%diameter at rear of transition
% LT = 0.001;%length of transition****************
% XP = 1.866;%distance from tip of nose to front of transition
% CR = 1;%fin chord root
% CT = 0.26;%fin chord tip
% S = 0.2;%fin semispan
% LF = 0.311109;%length of mid-chord line 
% R = 0.265;%radius of body at aft end
% XR = 0.608303;%distance from fin root to tip in axle direction
% XB = 4.266;%distance from nose tip to fin root leading edge
% N = 4;%number of fin
% 
% %Nose Cone Terms
% CNN = 2;
% % XN = 0.666*LN;%0.666for cone shape nose
% XN = 0.466*LN;%0.466for ogive shape nose
% 
% %Conical Transition Terms
% CNT = 2*((dR/d)^2-(dF/d)^2);
% XT = XP + LT/3*(1+(1-dF/dR)/(1-(dF/dR)^2));
% 
% %Fin Terms
% CNF = (1+R/(S+R))*(4*N*(S/d)^2/(1+sqrt(1+(2*LF/(CR+CT))^2)));
% XF = XB + XR/3*(CR+2*CT)/(CR+CT) + 1/6*((CR+CT)-CR*CT/(CR+CT));
% 
% %Finding the Center of Pressure
% CNR = CNN+CNT+CNF;
% det_cp= (CNN*XN+CNT*XT+CNF*XF)/CNR;
% CP = det_cp*ones(length(t),1);

% %datcom CP
% dat_data = readmatrix('./datcom/XCP/xcp1.xlsx','range','B248:Q257');
% Mach = dat_data(1,1:15);
% AOA = dat_data(2:10,1);
% dat_xcp = dat_data(2:10,2:16)*26.5/100;
% [dat_mi,dat_ai] = meshgrid(Mach,AOA);
%% ORK CG.CP
% oprk_data = readmatrix('./open rocket data/property2.csv','Range','A9:G247');
% oprk_t = oprk_data(:,1);
% oprk_CG = oprk_data(:,7)/100;
% oprk_CP = oprk_data(:,6)/100;

%% plot
% figure
plot(t,CG,'LineWidth',2)
grid on
hold on
% plot(oprk_t,oprk_CG,'LineWidth',2)
% plot(t,CP)
% plot(oprk_t,oprk_CP)
xlabel('time')
ylabel('CG(m)')
legend('finless CG')
% 
% legend('det CG','ORK CG','det CP','ORK CP')
% legend('det CG','ORK CG')
% legend('avi.payload m=3','avi.payload m=10','avi.payload m=20',...
%     'avi.payload m=30','avi.payload m=40','avi.payload m=54')
% figure
% surf(dat_mi,dat_ai,dat_xcp,'EdgeColor','black', 'FaceColor',[0.4660 0.6740 0.1880], 'FaceAlpha', .5)
% xlabel('Mach')
% ylabel('AOA(degree)')
% zlabel('distance from nose(m)')
% grid on
% hold on

% legend('det CG','ORK CG','datcom CP')

