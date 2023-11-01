%% type geometry of rocket
PHIW = 0.0;
XCG = 0.0;
XLEcanard=[90.9,104.756];
SSPANcanard=[13.25,21.25];
CHORDcanard=[14.0,2.0];
SWEEPcanard=13.06;
XLEtail=[470.6,502.6];
SSPANtail=[13.25,45.25];
CHORDtail=[65.0,20.0];
SWEEPtail=-22.11;
DELTAcanard = [0.0 0.0 0.0 0.0];
DELTAtail = [0.0 0.0 0.0 0.0];
[Mach,AOA,CN,CM,CA,CLL,XCP,CNQ,CMQ,CABASE,XCPcanard,XCPtail] = datcomcoef(PHIW,XCG,XLEcanard,SSPANcanard, ...
    CHORDcanard,SWEEPcanard,XLEtail,SSPANtail,CHORDtail,SWEEPtail, ...
    DELTAcanard,DELTAtail);
Minter = Mach;
atkinter = AOA;
cn1000 = CN;
caoff1000 = CA;
caon1000 = CA-0.36*CABASE;
xcp1000 = XCP;
xcp_t1000 = XCPtail;
xcp_c1000 = XCPcanard;
XCG = 360.0;
[Mach,AOA,CN,CM,CA,CLL,XCP,CNQ,CMQ,CABASE,XCPcanard,XCPtail] = datcomcoef(PHIW,XCG,XLEcanard,SSPANcanard, ...
    CHORDcanard,SWEEPcanard,XLEtail,SSPANtail,CHORDtail,SWEEPtail, ...
    DELTAcanard,DELTAtail);
XCG = 0.0;
cnq1000 = CNQ;
cmq1000 = CMQ;
cndq1000 = zeros(1,11);
cldp1000 = zeros(1,11);
clpt_1000 = clp_cc(Mach,CHORDtail(1)/100,CHORDtail(2)/100,(SSPANtail(2)-SSPANtail(1))/100);
clpc_1000 = clp_cc(Mach,CHORDcanard(1)/100,CHORDcanard(2)/100,(SSPANcanard(2)-SSPANcanard(1))/100);
PHIW = 22.5;
[Mach,AOA,CN,CM,CA,CLL,XCP,CNQ,CMQ,CABASE,XCPcanard,XCPtail] = datcomcoef(PHIW,XCG,XLEcanard,SSPANcanard, ...
    CHORDcanard,SWEEPcanard,XLEtail,SSPANtail,CHORDtail,SWEEPtail, ...
    DELTAcanard,DELTAtail);
PHIW = 0.0;
cl_phi1000 = CLL;
cmad_1000 = zeros(1,11);
cna_1000 = zeros(9,11);
cma_1000 = zeros(9,11);


% transfer_txt_mat()