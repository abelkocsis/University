function [kp, r_sor, r_oszl] = HFP1_2(A)
% Kocsis Ábel - FGSDV2
% A program felrajzolja a mátrix Gersgorin köreit, ha létezik.
% Teszt bemenet1: [kp, r_sor, r_oszl]  = HFP1_2([4, -1, 0.1, 0.2; -0.1, 2, 0.1, -0.2; 0.1, -0.1, 12, 0.1; -0.2, 0.2, -0.4, 10])
% Teszt bemenet2: [kp, r_sor, r_oszl] = HFP1_2([3,0.25;0.75,1])
% Teszt bemenet3: [kp, r_sor, r_oszl] = HFP1_2([10, 1, 2, 3, 0.1; 1, 5, 1, 0.1, 3; 1, 0, 16, 1.5, 2.3; 1, 2, 3, -6, 0.4; 1, 3, 2, 0.4 23])
% Teszt generátor:  [kp, r_sor, r_oszl] = HFP1_2(rand(10, 10) + diag(rand(10,1) * 100))

[n, m] = size(A);
if n ~= m
    error('bad dimension')
end 
kp = zeros(1,n);
r_sor = zeros(1,n);
r_oszl = zeros(1,n);

th = 0:pi/50:2*pi;
clf;
hold on

for i = 1:n
    kp(i) = A(i,i);
    r_sor(i) = (sum(abs(A(i,:))) - abs(kp(i)));
    r_oszl(i) = (sum(abs(A(:,i))) - abs(kp(i)));
    
    if r_sor(i) > r_oszl(i)
        subplot(2,1,1);
        axis equal
        hold on
        xunit = r_sor(i) * cos(th) + kp(i);
        yunit = r_sor(i) * sin(th);
        fill(xunit, yunit, 'r');
        legend('soronkénti G-körök');
    
        subplot(2,1,2);
        axis equal
        hold on
        xunit = r_oszl(i) * cos(th) + kp(i);
        yunit = r_oszl(i) * sin(th);
        fill(xunit, yunit, 'g');
        legend('oszloponkénti G-körök');
    else
        subplot(2,1,2);
        axis equal
        hold on
        xunit = r_oszl(i) * cos(th) + kp(i);
        yunit = r_oszl(i) * sin(th);
        fill(xunit, yunit, 'g');
    
        subplot(2,1,1);
        axis equal
        hold on
        xunit = r_sor(i) * cos(th) + kp(i);
        yunit = r_sor(i) * sin(th);
        fill(xunit, yunit, 'r');
    end
end

axis equal
hold off

%BeÃ©pÃ­tett metÃ³dust a Gersgorin kÃ¶rÃ¶kre nem talÃ¡ltam.

end

