function ew = exp_so3(w,theta)%theta included for completeness
wtilde =[0 -w(3) w(2) ; w(3) 0 -w(1) ; -w(2) w(1) 0];
ew = eye(3)+wtilde*sin(theta)+wtilde^2*(1-cos(theta));
end