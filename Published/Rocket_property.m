function y = Rocket_property(U)
thr_cmd = U(1);
t = U(2);
%% initial conditions 
%fixed parts:mass(kg),CG(m)
Nose_tube_mass = 1.72;
payload1_mass = 10;             %%%%
Avionic_tube_mass = 2.94;
avi_act_rec_mass = 10;            %%%%
N2O_tank_mass = 18;            %all = 18
Connect_mass = 0.88;
payload3_mass = 10;             %%%%
combus_mass = 39.7;            %origin,lightening = 39.7 , highreg = 29.5
fin_mass = 2.5;

Nose_x = 0.568;
payload1_x = 0.568;
Avionic_x = 1.39;
payload2_x = 1.39;
N2O_tank_x = 3.084;
Connect_x = 4.566;
payload3_x = 4.566; 
combus_x = 5.556;               %origin,lightening = 5.556  ,highreg = 5.031
fin_x = 6.043;

%N2O:mass(kg),CG(m)
N2O_long = 2.61;%long(m)
N2O_massi = 91;%initial mass(kg)                                %all = 91
N2O_massf = 17;%final mass(kg)                                  %all = 17
N2O_xi = 1+0.772+2.61-N2O_long/2;%initial CG position(m)

%fuel(kg),CG(m)
Fuel_massi = 60.9;%initial mass(kg)               %origin = 60.9 ,lightening = 36.5 , highreg = 18
Fuel_massf = 48.6;%final mass(kg)                %origin = 48.6 ,lightening = 24.3 , highreg = 5.7
Fuel_x0 = 1+0.772+2.61+0.354+1.631/2;%initial CG position(m)

%every part's inertia about each CG
fin_y = 0.21292;%distance from CG_fin to centre                 %%%%
Nose_I = [0.086672 0.086672 0.020317];
payload1_I = [0.002527 0.002527 0.003200];
Avionic_I = [0.270551 0.270551 0.050867];
payload2_I = [0.332395 0.332395 0.324958];
N2O_tank_I = [10.754864 10.754864 0.302346];
N2O_Ii = [42.266237 42.266237 0.769001];                        %all = [42.266237 42.266237 0.769001]; 
N2O_If = [0.344861 0.344861 0.143656];                          %all = [0.344861 0.344861 0.143656];
if t<15                                                         %all = [-0.0067*(t+1)^3 + 0.3913*(t+1)^2 - 7.6138*(t+1) + 49.556 , -0.0067*(t+1)^3 + 0.3913*(t+1)^2 - 7.6138*(t+1) + 49.556 ,  -0.0417*(t+1) + 0.8109];
    N2O_I = [-0.0067*(t+1)^3 + 0.3913*(t+1)^2 - 7.6138*(t+1) + 49.556  
             -0.0067*(t+1)^3 + 0.3913*(t+1)^2 - 7.6138*(t+1) + 49.556
             -0.0417*(t+1) + 0.8109];
else
    N2O_I = N2O_If;
end
fin_I = [0.036099 0.034037 0.002064];
Connect_I = [0.014248 0.014248 0.015260];
payload3_I = [0.022439 0.022439 0.016683];
combus_I = [11.166158 11.166158 0.642622];
Fuel_Ii = [14.77 14.77 0.61];                       %origin = [14.77 14.77 0.61];      lightening = [8.89 8.89 0.453];     highreg = [0.7129 0.7129 0.204];
Fuel_If = [11.81 11.81 0.488];                       %origin = [11.81 11.81 0.488];    lightening = [5.917 5.917 0.3016];     highreg = [0.2276 0.2276 0.065];
if t <15                                             %origin = [-0.197*(t+1) + 14.964 ,-0.197*(t+1) + 14.964, -0.008*(t+1) + 0.6184];  lightening = [-0.1982*(t+1)+9.0873,-0.1982*(t+1)+9.0873,-0.01*(t+1)+0.4632];    highreg =  [-0.0324*(t+1)+0.7452 , -0.0324*(t+1)+0.7452 , -0.0093*(t+1)+0.2132];
    Fuel_I = [-0.197*(t+1) + 14.964 ,-0.197*(t+1) + 14.964, -0.008*(t+1) + 0.6184];
else
    Fuel_I = Fuel_If;
end
    
%% 
%calculate fixed mass,CG
fixed_mass = Nose_tube_mass+payload1_mass+Avionic_tube_mass+...
    avi_act_rec_mass+N2O_tank_mass+Connect_mass+payload3_mass+...
    combus_mass+4*fin_mass;
fixed_x = (Nose_tube_mass*Nose_x+payload1_mass*payload1_x+...
    Avionic_tube_mass*Avionic_x+avi_act_rec_mass*payload2_x+...
    N2O_tank_mass*N2O_tank_x+Connect_mass*Connect_x+...
    payload3_mass*payload3_x+combus_mass*combus_x+...
    4*fin_mass*fin_x)/fixed_mass;
%calculate N2O mass,CG
if thr_cmd==1
    N2O_mass = N2O_massi - (N2O_massi-N2O_massf)/15*t;
else
    N2O_mass = N2O_massf;
end
N2O_x = N2O_xi + N2O_long/2 - (N2O_long/N2O_massi.*N2O_mass)/2;

%calculate fuel mass,CG
if thr_cmd==1
    Fuel_mass = Fuel_massi - (Fuel_massi-Fuel_massf)/15*t;
else
    Fuel_mass = Fuel_massf;
end
Fuel_x = Fuel_x0;

%% calculate total mass
m = fixed_mass+N2O_mass+Fuel_mass;
CG = (fixed_mass*fixed_x + N2O_mass*N2O_x + Fuel_mass*Fuel_x)/m;

%% calculate I
Ixx = Nose_I(3)+payload1_I(3)+Avionic_I(3)+payload2_I(3)+...
     N2O_tank_I(3)+N2O_I(3)+Connect_I(3)+payload3_I(3)+...
    combus_I(3)+Fuel_I(3)+4*(fin_I(3)+fin_mass*fin_y^2);
Iyy = Nose_I(1)+Nose_tube_mass*(CG-Nose_x)^2+payload1_I(1)+...
    payload1_mass*(CG-payload1_x)^2+Avionic_I(1)+...
    Avionic_tube_mass*(CG-Avionic_x)^2+payload2_I(1)+...
    avi_act_rec_mass*(CG-payload2_x)^2+N2O_tank_I(1)+...
    N2O_tank_mass*(CG-N2O_tank_x)^2+N2O_I(1)+...
    N2O_mass*(CG-N2O_x)^2+Connect_I(1)+...
    Connect_mass*(CG-Connect_x)^2+payload3_I(1)+...
    payload3_mass*(CG-payload3_x)^2+combus_I(1)+...
    combus_mass*(CG-combus_x)^2+4*(fin_I(1)+...
    fin_mass*(CG-fin_x)^2)+Fuel_I(1)+...
    Fuel_mass*(CG-Fuel_x)^2;
Izz = Iyy;
I = [Ixx;Iyy;Izz];
%% thrust calculate
% if t<3.3
%     thrust = 1000/3.3*t;%kgf
% else if t<5
%         thrust = 1000 + (1275-1000)/(5-3.3)*(t-3.3);
% else if t<15
%         thrust = 1275 + (1240-1275)/(15-5)*(t-5);
% else
%     thrust = 0;
% end
% end
% end
if t<2
    thrust = 1300/2*t;%kgf
else if t<6.5
        thrust = 1300;
else
    thrust = 0;
end
end

%% output
y = [m;CG;I;thrust];
end