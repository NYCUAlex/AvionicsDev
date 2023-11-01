function [Mach,AOA,CN,CM,CA,CLL,CNA,CMA,XCP,CNQ,CMQ,CABASE,XCPcanard,XCPtail] = datcomcoef(PHIW,XCG,XLEcanard, ...
    SSPANcanard,CHORDcanard,SWEEPcanard,XLEtail,SSPANtail,CHORDtail, ...
    SWEEPtail,DELTAcanard,DELTAtail)
%% type geometry of rocket
fid = fopen('Miss5.DAT','w');
fprintf(fid,[...
    'CASEID * INPUT is Checked and Created automatically by OLC, Form-Designed by YJP *'    '\n'...
    'SOSE'                                                        '\n'...
    'DIM CM'                                                      '\n'...
    'DAMP'                                                        '\n'...
    'DERIV RAD'                                                   '\n'...
    ' $FLTCON ALT=1000.0,NMACH=11.0,NALPHA=9.0,'                  '\n'...
    '         MACH=0.01,0.3,0.5,0.7,0.9,1.0,1.1,1.3,1.5,1.8,2.0,' '\n'...
    '         ALPHA=0.00000001,0.1,0.3,0.5,1.0,2.0,3.0,4.0,5.0,'  '\n'...
    '         PHI=%f,'                                            '\n'...
    ' $END'                                                       '\n'...
    ' $REFQ SREF=551.545,LREF=26.5,XCG=%f,ZCG=0.0,'               '\n'...       % XCG=minCG when find Cmdq  XCG=0 when other
    '       ROUGH=0.000406,SCALE=1.0,BLAYER=0.0,'                 '\n'...       % ver1CG=432.2 ver2CG=360    
    ' $END'                                                       '\n'...
    ' $AXIBOD X0=0.0,'                                            '\n'...
    '         TNOSE=1.0,'                                         '\n'...
    '         LNOSE=100.0,'                                       '\n'...
    '         DNOSE=26.5,'                                        '\n'...
    '         LCENTR=537.5,'                                      '\n'...
    '         DCENTR=26.5,'                                       '\n'...
    '         LAFT=8.8,'                                          '\n'...
    '         DAFT=19.6,'                                         '\n'...
    '         DEXIT=0.0,'                                         '\n'...
    ' $END'                                                       '\n'...
    ' $FINSET1 SECTYP=3.0,NPANEL=4.0,'                            '\n'...
    '          XLE=%f,%f,'                                        '\n'...
    '          SSPAN=%f,%f,'                                      '\n'... 
    '          CHORD=%f,%f,  '                                    '\n'...                                           
    '          STA=1.0,'                                          '\n'...
    '          SWEEP=%f,'                                         '\n'... 
    '          LER=0.005,0.005,'                                  '\n'... 
    '          XCORD=0.0,0.2,0.99,1.0,'                           '\n'...
    '          MEAN=0.0, 0.0, 0.0, 0.0,'                          '\n'...
    '          THICK=0.0, 0.06,0.06, 0.0,'                        '\n'...
    '          PHIF= 45.0,135.0,225.0,315.0,'                     '\n'...
    ' $END'                                                       '\n'...
    ' $FINSET2 SECTYP=3.0,NPANEL=4.0,'                            '\n'...
    '          XLE=%f,%f,'                                        '\n'...
    '          SSPAN=%f,%f,'                                      '\n'...
    '          CHORD=%f,%f,'                                      '\n'...                                                     
    '          STA=1.0,'                                          '\n'...
    '          SWEEP=%f,'                                         '\n'... 
    '          LER=0.005,0.005,'                                  '\n'...
    '          XCORD=0.0,0.2,0.99,1.0,'                           '\n'...       %very weird of this variable
    '          MEAN=0.0, 0.0, 0.0, 0.0,'                          '\n'...
    '          THICK=0.0, 0.013,0.013, 0.0,'                      '\n'...
    '          PHIF= 45.0,135.0,225.0,315.0,'                     '\n'...       %45.0,135.0,225.0,315.0,
    ' $END'                                                       '\n'...
    ' $DEFLCT'                                                    '\n'...       %-10.0,-10.0,10.0,10.0,
    '          DELTA1=  %f,  %f,  %f,  %f,'                   '\n'...       %0.0,  0.0,  0.0,  0.0,
    '          DELTA2=  %f,  %f,  %f,  %f,'                   '\n'...       %5.73,5.73,5.73,5.73,(roll control)
    '          XHINGE=0.0,0.0,'                                   '\n'...       %5.73,5.73,-5.73,-5.73,(pitch control)
    '          SKEW=0.0, 0.0,'                                    '\n'...       %-5.73,5.73,5.73,-5.73,(yaw control)
    ' $END'                                                       '\n'...
    'BUILD'                                                       '\n'...
    'PART'                                                        '\n'...
    'SAVE'                                                        '\n'...
    'DAMP'                                                        '\n'...
    'NEXT CASE'],PHIW,XCG,XLEcanard,SSPANcanard,CHORDcanard,SWEEPcanard,...
    XLEtail,SSPANtail,CHORDtail,SWEEPtail,DELTAcanard,DELTAtail);
fclose(fid);
%% compile datcom
system('M5-061031.exe')
%% transfer .dat file into .xlsx file
ceo_static = readmatrix("coef.tab","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range","B7:M1204");
Mach = ceo_static(1,1:11);
AOA = ceo_static(2:10,1);
CN = ceo_static(2:10,2:12);
CM = ceo_static(14:22,2:12);
CA = ceo_static(26:34,2:12);
CLL = ceo_static(62:70,2:12);
CNA = ceo_static(74:82,2:12);
CMA = ceo_static(86:94,2:12);
XCP = ceo_static(134:142,2:12);
XCPcanard = ceo_static(1046:1054,2:12);
XCPcanard(1,1:11) = XCPcanard(2,1:11);
XCPtail = ceo_static(1190:1198,2:12);
XCPtail(1,1:11) = XCPtail(2,1:11);
% ceo_dynamic = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range","A1:M10307");
for i=1:11
    if i<8
        ind(i) = 1163+913*(i-1);
        CNQindex(i,1:3) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind(i) 3 ind(i) 5]);
%         CNQindex2(i,1:3) = ceo_dynamic(970,3:5)
    else if i==8
        ind(i) = 1163+913*6+916;
        CNQindex(i,1:3) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind(i) 3 ind(i) 5]);
    else 
        ind(i) = 1163+913*6+916+914*(i-8);
        CNQindex(i,1:3) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind(i) 3 ind(i) 5]);
    end
    end
end
CNQindex = CNQindex';
CNQ = CNQindex(1,:);
CNAD = CNQindex(2,:);
CMQpCMAD = CNQindex(3,:);
CMQ = CMQpCMAD.*CNQ./(CNQ+CNAD);
% CABASEindex =  readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range","A1:M10307");
for i=1:11
    if i<8
        ind2(i) = 273+913*(i-1);
        CABASEindex(1:9,i) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind2(i) 5 ind2(i)+8 5]);
    else if i<9
        ind2(i) = 273+913*(i-1);
        CABASEindex(1:9,i) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind2(i) 5 ind2(i)+8 5]);
    else if i<10
        ind2(i) = 273+913*7+916;
        CABASEindex(1:9,i) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind2(i) 5 ind2(i)+8 5]);
    else
        ind2(i) = 273+913*7+916+914*(i-9);
        CABASEindex(1:9,i) = readmatrix("tape6","FileType","text",'Delimiter',' ','ConsecutiveDelimitersRule','join',"Range",[ind2(i) 5 ind2(i)+8 5]);
    end
    end
    end
end
CABASE = CABASEindex;
end