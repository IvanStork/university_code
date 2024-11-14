function adHoi = get_adjoint(Hoi)%generate the adjoint
    O = Hoi(1:3, 4);
    Otilde = [0 -O(3) O(2) ; O(3) 0 -O(1) ; -O(2) O(1) 0];
    R = [Hoi(1, 1:3);
    Hoi(2, 1:3);
    Hoi(3, 1:3)];
    X = Otilde*R;   
    adHoi = [Hoi(1, 1:3) 0 0 0;
             Hoi(2, 1:3) 0 0 0;
             Hoi(3, 1:3) 0 0 0;
             X(1, 1:3) R(1, 1:3)
             X(2, 1:3) R(2, 1:3)
             X(3, 1:3) R(3, 1:3)];
end