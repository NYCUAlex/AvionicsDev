% 2022/10/09 modified by Alex : Cmdq->Cndq
function y = totalfm(U)
global g d S mis_angle% stage rail_len
p = U(1);
q = U(2);
r = U(3);
e0 = U(4);
ex = U(5);
ey = U(6);
ez = U(7);
h = U(8);
thr_cmd = U(9);
qbar = U(10);
deltap = U(11);%rad
deltaq = U(12);
deltar = U(13);
CAon = U(14);
CAoff = U(15);
CN = U(16);
CNq = U(17);
Cmq = U(18);
Cmdq = U(19);
xcp = U(20);
Cldp = U(21);
Clp_t = U(22);
Cl_phi = U(23);
Xcp_c = U(24);
Clp_c = U(25);
Cldpt = U(26);
xcg = U(27);
m = U(28);
alpha_t = U(29);
phi_w = U(30);
V = U(31);
% dis_x = U(32);
% rec_cmd = U(33);
stage = U(34);
Ft_1x = U(35);
% Mach = U(36);
thrust = U(37);


%% stage verify
% 0 = on the ground
% 1 = on the rail
% 2 = takeoff
% 3 = rolling controller on(M = 0.3)
% 4 = pitching controller on(M = 0.7)
% 5 = burn out(M = 1.~)
% 6 = controller off(M = 0.7)
% 7 = recovery

%% Aero coefficient
Cyr = CNq;
Cnr = Cmq;
Cndr = Cmdq;
switch stage
    case 0
        CA = CAon;
        Cfx = 0;
        Cfy = 0;
        Cfz = 0;
        Cmx = 0;
        Cmy = 0;
        Cmz = 0;
    case 1
        CA = CAon;
        Cfx = -CA;
        Cfy = 0;
        Cfz = 0;
        Cmx = 0;
        Cmy = 0;
        Cmz = 0;
    case 2
        CA = CAon;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V);%
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V);%
    case 3
        CA = CAon;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldp*deltap+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V);%
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V);%
    case 4
        CA = CAon;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldp*deltap+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V)+Cmdq*deltaq;% 
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V)+Cndr*deltar;% 
    case 5
        CA = CAoff;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldp*deltap+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V)+Cmdq*deltaq;%
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V)+Cndr*deltar;%
    case 6
        CA = CAoff;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V);%
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V);%
    case 7
        CA = CAoff;
        Cfx=-CA;
        Cfy=0-CN*sind(phi_w)+Cyr*r*d/(2*V);%
        Cfz=0-CN*cosd(phi_w)-CNq*q*d/(2*V);%
        Cmx=0+Cl_phi*sind(4*phi_w)+(Clp_t+Clp_c)*p*d/(2*V)+Cldpt*mis_angle;%
        Cmy=0-CN*(xcp*d-xcg)/d*cosd(phi_w)+Cmq*q*d/(2*V);%
        Cmz=0+CN*(xcp*d-xcg)/d*sind(phi_w)+Cnr*r*d/(2*V);%
end

% tail_misalignment = 
%% transform matrix for body frame to NED frame
Hbn = [e0^2+ex^2-ey^2-ez^2     2*ex*ey-2*e0*ez    2*e0*ey+2*ex*ez;
       2*ex*ey+2*e0*ez     e0^2+ey^2-ex^2-ez^2    2*ey*ez-2*e0*ex;
       2*ex*ez-2*e0*ey     2*e0*ex+2*ey*ez    e0^2+ez^2-ex^2-ey^2];
%% force and moment
FA = qbar*S*CA;
FN = qbar*S*CN;
%aerodynamic force(body frame)
Fa = [qbar*S*Cfx;
      qbar*S*Cfy;
      qbar*S*Cfz];
%aerodynamic moment(body frame)
Mga = [qbar*S*d*Cmx;
       qbar*S*d*Cmy;
       qbar*S*d*Cmz];
%thrust force(body frame) or moment(throlling)
if thr_cmd==1
    Fth = [thrust*g;
          0;
          0];
    Mth = [1.06;   %throlling  1.06
           0;
           0];
else
    Fth = zeros(3,1);
    Mth = zeros(3,1);
end


%gravity force(NED frame)
Fgned = [0;
         0;
         m*g];
Fg = Hbn\Fgned;%(body frame)
%% calculate total force and moment
%total force(N)
Ft = Fg + Fa + Fth;%
%total moment(N*m)
Mgt = Mga + Mth;

Mmax = qbar*S*d*CN*(xcp*d-xcg)/d;
% %% stage verify
% % 0 = on the ground
% % 1 = on the rail
% if stage==0 & Ft(1)>0
%     stage = 1
% end


%% output
switch stage
    case 0
        y = [0;0;0;0;0;0;Ft(1)];
    case 1
        y = [Ft(1);0;0;0;0;0;Ft(1)];
    case {2,3,4,5,6,7}
        y=[Ft;Mgt;Ft(1)];
end
end