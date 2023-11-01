function stage = stage_func(U)
stage_1 = U(1);
Ft_x = U(2);
dis_x = U(3);
rail_len = U(4);
Mach = U(5);
thr_cmd = U(6);
rec_cmd = U(7);
%% stage verify
% 0 = on the ground
% 1 = on the rail
% 2 = takeoff
% 3 = rolling controller on(M = 0.3)
% 4 = pitching controller on(M = 0.7)
% 5 = burn out(M = 1.~)
% 6 = controller off(M = 0.7)
% 7 = recovery
stage = stage_1;
if stage_1==0 & Ft_x==0
    stage = 0  
else if stage_1==0 & Ft_x>0
    stage = 1   
else if stage_1==1 & dis_x>rail_len
    stage = 2
else if stage_1==2 & Mach>0.3
    stage = 3
else if stage_1==3 & Mach>0.7
    stage = 4    
else if stage_1==4 & thr_cmd == 0
    stage = 5
else if stage_1==5 & Mach<0.7
    stage = 6    
else if stage_1==6 & rec_cmd == 1
    stage = 7
end
end
end
end
end
end
end
end