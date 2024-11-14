function ET = exp_twist(unit_twist)%function to calculate the exponential of a twist
w = [unit_twist(1);unit_twist(2);unit_twist(3)];
v = [unit_twist(4);unit_twist(5);unit_twist(6)];
theta = pi; 
ew = exp_so3(w, theta);
X = (1/norm(w)^2)*((eye(3)-ew)*(cross(w,v))+(transpose(w)*v*w)); %in the case of only rotational joints, this is a 0 vector

ET = [ew(1,1) ew(1,2) ew(1,3) X(1);
      ew(2,1) ew(2,2) ew(2,3) X(2);
      ew(3,1) ew(3,2) ew(3,3) X(3);
      0 0 0 1];

end