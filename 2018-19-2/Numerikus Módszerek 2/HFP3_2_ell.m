function [polert] = HFP3_2_ell(beta, alfa, gamma, x)
% Kocsis �bel - FGSDV2
% A program egy tridiagon�lis m�trix (alfa f��tl�j�, b�ta �s gamma mell�k�tl�j�) karakterisztikus polinomj�t hat�rozza meg.
% Egyszer� teszt: [polert] = HFP3_2_ell([1,2,3],[1,2,3,4],[1,2,3]);
% Nagyobb teszt : [polert] = HFP3_2_ell([4,1,6,2,4,0,3,1],[12,0,34,12,5,4,0,11,19],[12,3,42,3,11,0,7,17]);
% Speci�lis teszt (szimmetrikus, val�s saj�t�rt�kek) : [polert] = HFP3_2_ell ([1,6,2,4], [3,7,1,4,2], [1,6,2,4]);
% Teszt gener�tor: [polert] = HFP3_2_ell (rand(19,1), rand(20,1), rand(19,1));

polert = HFP3_2(beta, alfa, gamma);
n = length(alfa);

%Ellen�rz�s:

A = zeros(n, n);
A = diag(alfa);
B = diag(beta, -1);
C = diag(gamma, 1);
A = A + B + C;
polert2 = poly(A);

polert2 = double(polert2);


%A k�t polinom legfeljebb konstans szorz�ban t�r el.
polert
polert2


end
