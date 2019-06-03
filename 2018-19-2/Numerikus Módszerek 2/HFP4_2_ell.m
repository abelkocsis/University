function [polert] = HFP4_2_ell (beta, alfa, gamma, x, N)
% Kocsis Ábel - FGSDV2
% A program egy trifiagonális mátrix (alfa fõátlójú, béta és gamma mellékátlójú) egy sajátértékét határozza meg a Newton módszer segítségével.
% Teszt1: [polert] = HFP4_2_ell([1,2,3],[1,2,3,4],[1,2,3], 0, 3);
% Teszt2: [polert] = HFP4_2_ell([1,2,3],[1,2,3,4],[1,2,3], 0, 10);
% Teszt3, nagyobb teszt : [polert] = HFP4_2_ell([4,1,6,2,4,0,3,1],[12,0,34,12,5,4,0,11,19],[12,3,42,3,11,0,7,17], 3, 5);
% Teszt4, speciális teszt (szimmetrikus, velós sajátértékek) : [polert] = HFP4_2_ell ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 3, 5);
% Teszt5, messzirõl közelítés: [polert] = HFP4_2_ell ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 30, 3);
% Teszt6, tesztgenerátor: [polert] = HFP4_2_ell (rand(19,1), rand(20,1), rand(19,1), rand*10-10, 5);

[polert, lambda] = HFP4_2(beta, alfa, gamma, x, N);
n = length(alfa);
%Ellenõrzés:
A = zeros(n, n);
A = diag(alfa);
B = diag(beta, -1);
C = diag(gamma, 1);
A = A + B + C;
e = eig(A);
%Megadja a megtalálni vélt sajátérték eltérését a közelben található valós sajátértéktõl.
hiba = min(abs(e-lambda(N+1)))



