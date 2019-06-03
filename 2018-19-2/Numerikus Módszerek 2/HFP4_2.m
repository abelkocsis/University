function [polert, lambda] = HFP4_2 (beta, alfa, gamma, x, N)
% Kocsis Ábel - FGSDV2
% A program egy tridiagonális mátrix (alfa fõátlójú, béta és gamma mellékátlójú) egy sajátértékét határozza meg a Newton módszer segítségével.
% Teszt1: [polert] = HFP4_2([1,2,3],[1,2,3,4],[1,2,3], 0, 3);
% Teszt2: [polert] = HFP4_2([1,2,3],[1,2,3,4],[1,2,3], 0, 10);
% Teszt3, nagyobb teszt : [polert] = HFP4_2([4,1,6,2,4,0,3,1],[12,0,34,12,5,4,0,11,19],[12,3,42,3,11,0,7,17], 3, 5);
% Teszt4, speciális teszt (szimmetrikus, velós sajátértékek) : [polert] = HFP4_2 ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 3, 5);
% Teszt5, messzirõl közelítés: [polert] = HFP4_2 ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 30, 3);
% Teszt6, tesztgenerátor: [polert] = HFP4_2 (rand(19,1), rand(20,1), rand(19,1), rand*10-10, 5);

n = length(alfa);

if n ~= length(beta)+1 || n ~= length(gamma)+1
    error('bad dimension');
end 

p = zeros(n+1, n+1);
pd = zeros(n+1, n+1);

p(1, n+1) = 1;
p(2, n+1) = alfa(1);
p(2, n) = -1;

pd(2, n+1) = -1;

for i = 2:n
    p(i+1,:) = p(i+1,:) + alfa(i)*p(i,:);
    p(i+1, 1:n) = p(i+1, 1:n) - p(i, 2:n+1);
    p(i+1,:) = p(i+1,:) - (p(i-1,:)*beta(i-1)*gamma(i-1));
    
    pd(i+1, :) = pd(i+1, :) - p(i, :);
    pd(i+1,:) = pd(i+1,:)  + alfa(i)*pd(i,:);
    pd(i+1, 1:n) = pd(i+1, 1:n) - pd(i, 2:n+1);
    pd(i+1,:) = pd(i+1,:)  - (pd(i-1,:)*beta(i-1)*gamma(i-1));
    
end

polert = p(n+1, :);
polder = pd(n+1, :);

lambda = zeros(N+1, 1);
lambda(1) = x;

for i = 1:N
    lambda(i+1) = lambda(i) - polyval(polert, lambda(i)) / polyval(polder, lambda(i));
end



