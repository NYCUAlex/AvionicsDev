% clear
clc
close all
s = tf('s');
%% obtain variable
time = 0;
num = 0;
M = [0.30,0.50,0.70,0.90,1.00,1.10,1.30,1.50,1.70,1.90,2.10,2.20];
%rocket property
for i = 2:length(Mach)%get M = 0.3,0.5...'s time
   for k = 1:length(M)
       if Mach(i) == max(Mach)
           time = [time i];
           num = num + 1;
           break;
       end
       if round(Mach(i),2) == round(Mach(i-1),2)
           break;
       end
       if round(Mach(i),2) == M(k)
           time = [time i];
           num = num + 1;
           break;
       end
   end 
end
time(1) = [];%delete 0 value
time(end) = [];%delete M = 0.3
time(end) = [];%delete M = 0.5

m = zeros(1,length(time));
Ix = zeros(1,length(time));
Iy = zeros(1,length(time));
rho = zeros(1,length(time));
V = zeros(1,length(time));
qbar = zeros(1,length(time));
Clpt = zeros(1,length(time));
Clpc = zeros(1,length(time));
Cldp = zeros(1,length(time));
Cw = zeros(1,length(time));
u = zeros(1,length(time));
Cnad = zeros(1,length(time));
Cmad = zeros(1,length(time));
Cna = zeros(1,length(time));
Cma = zeros(1,length(time));
XCP = zeros(1,length(time));
XCP_t = zeros(1,length(time));
XCG = zeros(1,length(time));
Cnq = zeros(1,length(time));
Cmq = zeros(1,length(time));
Cndq = zeros(1,length(time));
Cmdq = zeros(1,length(time));
lt = zeros(1,length(time));
Czdq_lin = zeros(1,length(time));
theta = zeros(1,length(time));


for k = 1:length(time)
    %common variables
    m(k) = simout.mass_property.signals.values(time(k),1);%kg
    rho(k) = simout.air(5,time(k));
    V(k) = simout.air(19,time(k));
    qbar(k) = 1/2.*rho(k).*V(k).^2;
    %roll channel variables
    Ix(k) = simout.mass_property.signals.values(time(k),3);
    Cldp(k) = simout.aeroCoef(time(k),8);
    Clpt(k) = simout.aeroCoef(time(k),9);
    Clpc(k) = simout.aeroCoef(time(k),12);
    %pitch channel variables
    Iy(k) = simout.mass_property.signals.values(time(k),5);
    Cw(k) = -m(k)*g/(S*qbar(k));
    u(k) = simout.vstate(4,time(k));
    XCP_t(k) = simout.aeroCoef(time(k),16)*d;
    XCG(k) = simout.mass_property.signals.values(time(k),2);
    theta(k) = simout.vstate(21,time(k))*pi/180;
    Cmad(k) = simout.aeroCoef(time(k),13);
    Cnq(k) = simout.aeroCoef(time(k),4);
    Cmq(k) = simout.aeroCoef(time(k),5);
    Cmdq(k) = simout.aeroCoef(time(k),6);%Cmde
    XCP(k) = simout.aeroCoef(time(k),7)*d;
%     lt(k) = XCP_t(k) - XCG(k);%Xcg to Xcpt
%     Czdq_lin(k) = (c/lt(k))*Cmdq(k);%Cndq
    Cna(k) = simout.aeroCoef(time(k),14);%Cza
    Cma(k) = simout.aeroCoef(time(k),15);
end
Clp = Clpt+Clpc;
%motor property
BW_HZ = 100;%hz
BW = BW_HZ*2*pi;%rad/s
damp = 0.9;
wn = BW/sqrt(1-2*damp^2+sqrt(2-4*damp^2+4*damp^4));%rad/s
%% roll channel
%% bode plot
% test num
n = 3;
K1 = [1.5,1,3,1,1,1,1,1,1,1,1,1,1,1,1];        %不用太大也可以有好曲線
K2 = [0.15,1,0.35,1,1,1,1,1,0.3,1,1,1,1,1,1];   %與BW正比
K3 = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1];  %與BW反比
IMU_SAMP_FREQ = 100; %Hz
CAN_TRANS_FREQ = 1000; %Hz
figure
for i =n% 1:length(time) 
%     figure
%     alpha = 0.7884;
%     tou = 0.0124;
    NUM1 = [Cldp(i)];
    DEN1 = [Ix(i)/(qbar(i)*S*d) -d*Clp(i)/(2*V(i))];% 0
    NUM2 = [wn^2];
    DEN2 = [1 2*wn*damp wn^2];
    NUM3 = [1];
    DEN3 = [1 0];
%     NUM4 = [tou 1];
%     DEN4 = [alpha*tou 1];
    

    sys_airframe_roll = tf(NUM1,DEN1);
    sys_actuator = tf(NUM2,DEN2);
    integrator = tf(NUM3,DEN3);
%     lead_com = tf(NUM4,DEN4);

    inner_OL = K2(i)*sys_airframe_roll*sys_actuator;%lead_com*integrator* inner loop open loop tf  
    inner_CL = feedback(inner_OL,K3(i),-1);%inner loop closed-loop tf
%     bode(inner_OL)
    bode(sys_airframe_roll*integrator)%*sys_actuator/Cldp(i)
    title(sprintf('Bode plot M = %.1f',M(i)))
    grid on 
    hold on
%     outer_OL = sys_airframe_roll*sys_actuator*integrator;
    outer_OL = K1(i)*inner_CL*integrator;%outer loop open loop tf  lead_com*
    outer_CL = feedback(outer_OL,1);%inner loop closed-loop tf
    bode(outer_OL)
    
%     figure
%     rlocus(outer_OL)
    grid on
    hold on
    legend('system before compensate','system after compensate')
%     legend(sprintf(' M = %.1f',M(i)))%actuator+controllerairframe+actuator
end
% legend("M=0.3","M=0.5","M=0.7","M=0.9","M=1","M=1.1","M=1.3","M=1.5","M=max","M=1.5","M=1.3","M=1.1","M=1","M=0.9","M=0.7")
%% phase lead controller design
% % requirements
% PM_des = 50;%desired PM
% % Kv_des = 20;%velocity error constant (self define)
% 
% % % proportional gain
% % s = 0;
% % % K = 0.01;
% % % Kv = 0;
% % % while(Kv_des>Kv)
% % %     Kv = K*NUM1/(d*Clp(n)/(2*V(n)));
% % %     K = K+0.01;
% % % end%
% % 
% % 
% % phase lead compensator 
% [Gm,Pm,Wcg,Wcp] = margin(K2*sys_airframe_roll*sys_actuator)% *integrator
% phi_m = PM_des-Pm+5;%compensate phase 
% alpha = (1-sind(phi_m))/(1+sind(phi_m));
% com_amp_max = 10*log10(1/alpha);%compensator max amplitude(dB) 
% 
% Wcg_star = 0.01;%initial value of search method
% sys_amp_before_com = 1000;%initial value of search method
% while(sys_amp_before_com>=-com_amp_max)
%     s = j*Wcg_star;
%     G_act_abs = (wn^2)/abs(s^2+2*damp*wn*s+wn^2);
%     G_air_abs = (NUM1/(abs((Ix(i)/(qbar(i)*S*d))*s^2+(d*Clp(n)/(2*V(n)))*s)));
%     G_before_abs = K1*G_act_abs*G_air_abs;
%     sys_amp_before_com = 20*log10(G_before_abs);%
%     Wcg_star = Wcg_star+0.01;%
% end
% wm = Wcg_star;%
% tou = 1/wm*sqrt(1/alpha);

%% roll channel end
%% pitch channel  (ref:automatic control of aircraft and missiles)
% figure
% o = 7;
% for i =o%  1:length(time)
%     NUM_pitch = (Cndq(i)*...%m11
%         (Iy(i)./(S*qbar(i)*c)*s^2-c/(2*u(i))*Cmq(i)*s))-...%m22
%         ((-m(i)*u(i)/(S*qbar(i))*s-Cw(i)*sin(theta(i)))*...%m12
%         Cmdq(i));%m21
%     DEN_pitch = (m(i)*u(i)/(S*qbar(i))*s-Cna(i))*...%m11
%         (Iy(i)/(S*qbar(i)*c)*s^2-c/(2*u(i))*Cmq(i)*s)-...%m22
%         (-m(i)*u(i)/(S*qbar(i))*s-Cw(i)*sin(theta(i)))*...%m12
%         (-c/(2*u(i))*Cmad(i)*s-Cma(i));%m21
% 
%     sys_airframe_pitch = NUM_pitch/DEN_pitch;
%     bode(sys_airframe_pitch)
%  %   pzmap(sys_airframe_pitch)
%     grid on
%     hold on
% %     legend(sprintf(' M = %.0f',Mach(i)))%actuator+controllerairframe+actuator
% end
% legend("M=0.3","M=0.5","M=0.7","M=0.9","M=1","M=1.1","M=max","M=1.1","M=1","M=0.9","M=0.7")

%% pitch channel (self-derived)
figure
o =3;
%ver2: 3,4,5,6,7
for i =o% 3:length(time) 
%     figure
    KP = [0,0,5,1,1,2,3,1,5,1,...
          1,1,1,1,1,1,1,1,1,1,...
          1];%
    wg = [1,1,3,3,3,3,3.5,3,3,3,...
          3,3,3,3,3,3,3,3,3,3,...
          3];
    tou1 = [1,1,10/wg(i),5/wg(i),5/wg(i),...
            5/wg(i),10/wg(i),5/wg(i),5/wg(i),5/wg(i),...
            5/wg(i),5/wg(i),5/wg(i),5/wg(i),5/wg(i),...
            5/wg(i),5/wg(i),5/wg(i),5/wg(i),5/wg(i),5/wg(i)];
    phi_m = [0,0,10,40,50,50,60,65,65,65,...
             65,65,65,65,65,65,65,65,65,65,...
             65];
    wm = [1,1,5,3,3,3,3.5,3,3,3,...
          3,3,3,3,3,3,3,3,3,3,...
          3];
    
    %system
    NUM_pitch_1 = [qbar(i)*S*d/Iy(i)];
    DEN_pitch_1 = [1 -qbar(i)*S*(d^2)*Cmq(i)/(Iy(i)*2*V(i)) 0];
    NUM_pitch_2 = [(m(i)*u(i)-Cnq(i)*d/(2*V(i))) -m(i)*g*sin(theta(i))];
    DEN_pitch_2 = [m(i)*u(i) qbar(i)*S*Cna(i)];
    NUM_act = [wn^2];
    DEN_act = [1 2*wn*damp wn^2];
    sys_airframe_pitch_1 = tf(NUM_pitch_1,DEN_pitch_1);
    sys_airframe_pitch_2 = tf(NUM_pitch_2,DEN_pitch_2);
    sys_airframe_pitch = Cmdq(i)*feedback(sys_airframe_pitch_1,Cma(i)*sys_airframe_pitch_2,1);
    sys_actuator = tf(NUM_act,DEN_act);

    %controller
    beta = abs(evalfr(KP(i)*sys_actuator*sys_airframe_pitch,j*wg(i)));
    NUM_phase_lag = [tou1(i) 1];
    DEN_phase_lag = [beta*tou1(i) 1];
    sys_phase_lag = tf(NUM_phase_lag,DEN_phase_lag);
    alpha = (1-sind(phi_m(i)))/(1+sind(phi_m(i)));
    tou2 = 1/wm(i)*sqrt(1/alpha);
    NUM_phase_lead = [tou2 1];
    DEN_phase_lead = [alpha*tou2 1];
    sys_phase_lead = tf(NUM_phase_lead,DEN_phase_lead);
    inner_OL_pitch = KP(i)*sys_phase_lead*sys_phase_lag*sys_actuator*sys_airframe_pitch;%
    
    bode(sys_airframe_pitch)%sys_actuator*
    title(sprintf('Bode plot M = %.1f',M(i)))
    grid on
    hold on
    bode(KP(i)*sys_phase_lead)%*sys_phase_lag
%     bode(KP(i)*sys_phase_lag*sys_actuator*sys_airframe_pitch)%sys_phase_lead*    
%     rlocus(sys_airframe_pitch*sys_actuator)%*sys_controller*sys_phase_lead
    bode(inner_OL_pitch)
    legend('system before compensate','controller','system after compensate')
end
% legend("M=0.3","M=0.5","M=0.7","M=0.9","M=1","M=1.1","M=1.3","M=1.5","M=1.7","M=1.9","M=2.1","M=2.2","M=2.1","M=1.9","M=1.7","M=1.5","M=1.3","M=1.1","M=1","M=0.9","M=0.7")
%% phase lead controller design for pitch channel
% % requirements
% PM_des = 50;%desired PM
% % Kv_des = 20;%velocity error constant (self define)
% 
% % % proportional gain
% % s = 0;
% % % K = 0.01;
% % % Kv = 0;
% % % while(Kv_des>Kv)
% % %     Kv = K*NUM1/(d*Clp(n)/(2*V(n)));
% % %     K = K+0.01;
% % % end%
% % 
% % 
% % phase lead compensator 
% [Gm,Pm,Wcg,Wcp] = margin(sys_airframe_pitch*sys_actuator)% *integrator
% phi_m = PM_des-Pm+5;%compensate phase 
% alpha = (1-sind(phi_m))/(1+sind(phi_m));
% com_amp_max = 10*log10(1/alpha);%compensator max amplitude(dB) 
% 
% Wcg_star = 0.01;%initial value of search method
% sys_amp_before_com = 1000;%initial value of search method
% while(sys_amp_before_com>=-com_amp_max)
%     s = j*Wcg_star;
%     G_act_abs = (wn^2)/abs(s^2+2*damp*wn*s+wn^2);
%     G_air_abs = (qbar(o)*S*d/Iy(o))/(abs((s^2-qbar(o)*S*d^2*Cmq(o)/(Iy(o)*2*V(o))*s)...
%         -(((m(o)*u(o)-Cnq(o)*d/(2*V(o)))*s-m(o)*g*sin(theta(o)))/(m(o)*u(o)*s+qbar(o)*S*Cna(o))*qbar(o)*S*d/Iy(o))));
% %     (NUM1/(abs((Ix(i)/(qbar(i)*S*d))*s^2+(d*Clp(n)/(2*V(n)))*s)));
%     G_before_abs = G_act_abs*G_air_abs;
%     sys_amp_before_com = 20*log10(G_before_abs);%
%     Wcg_star = Wcg_star+0.01;%
% end
% wm = Wcg_star;%
% tou = 1/wm*sqrt(1/alpha);
