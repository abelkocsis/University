function [polert] = HFP4_2_ell (beta, alfa, gamma, x, N)
% Kocsis �bel - FGSDV2
% A program egy trifiagon�lis m�trix (alfa f��tl�j�, b�ta �s gamma mell�k�tl�j�) egy saj�t�rt�k�t hat�rozza meg a Newton m�dszer seg�ts�g�vel.
% Teszt1: [polert] = HFP4_2_ell([1,2,3],[1,2,3,4],[1,2,3], 0, 3);
% Teszt2: [polert] = HFP4_2_ell([1,2,3],[1,2,3,4],[1,2,3], 0, 10);
% Teszt3, nagyobb teszt : [polert] = HFP4_2_ell([4,1,6,2,4,0,3,1],[12,0,34,12,5,4,0,11,19],[12,3,42,3,11,0,7,17], 3, 5);
% Teszt4, speci�lis teszt (szimmetrikus, vel�s saj�t�rt�kek) : [polert] = HFP4_2_ell ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 3, 5);
% Teszt5, messzir�l k�zel�t�s: [polert] = HFP4_2_ell ([1,6,2,4], [3,7,1,4,2], [1,6,2,4], 30, 3);
% Teszt6, tesztgener�tor: [polert] = HFP4_2_ell (rand(19,1), rand(20,1), rand(19,1), rand*10-10, 5);

[polert, lambda] = HFP4_2(beta, alfa, gamma, x, N);
n = length(alfa);
%Ellen�rz�s:
A = zeros(n, n);
A = diag(alfa);
B = diag(beta, -1);
C = diag(gamma, 1);
A = A + B + C;
e = eig(A);
%Megadja a megtal�lni v�lt saj�t�rt�k elt�r�s�t a k�zelben tal�lhat� val�s saj�t�rt�kt�l.
hiba = min(abs(e-lambda(N+1)))



