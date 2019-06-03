
--1
SELECT szuletesi_nev, golok_szama
FROM Jatekos
WHERE golok_szama = 
    (SELECT MAX (J.golok_szama)
    FROM Jatekos J)

--2
SELECT jid, szuletesi_nev
FROM Jatekos
WHERE jid = (
    SELECT szulo
    FROM Gyerek
    WHERE SzulDat = 
        ( SELECT MIN(Gy.SzulDat)
        FROM Gyerek Gy
        )
);


--3
SELECT jid, szuletesi_nev
FROM Jatekos
WHERE fazon =
    (SELECT J.fazon
    FROM Jatekos J
    WHERE J.jid = '0001')
    AND
    jid != '0001';

--4
SELECT szulo SzuloId, COUNT(nev) NemLeszFocista
FROM Gyerek
WHERE FocistaLesz = 'N'
GROUP BY szulo;

--5
DECLARE 
   CURSOR curs1 IS SELECT * FROM Focicsapat;
   rec1 curs1%ROWTYPE;
   CURSOR curs2 IS SELECT * FROM Jatekos;
   rec2 curs2%ROWTYPE;
   CURSOR curs3 IS SELECT * FROM Gyerek;
   rec3 curs3%ROWTYPE;
   gyerekNum NUMBER;
   maxGyerek NUMBER;
   maxCsapat CHAR(30);
BEGIN 
    gyerekNum := 0;
    maxGyerek := 0;
    OPEN curs1;
    LOOP
        FETCH curs1 INTO rec1;
        EXIT WHEN curs1%NOTFOUND;
        gyerekNum := 0;
        OPEN curs2;
        LOOP
            FETCH curs2 INTO rec2;
            EXIT WHEN curs2%NOTFOUND;
            IF rec2.fazon = rec1.fazon THEN
                OPEN curs3;
                LOOP
                    FETCH curs3 INTO rec3;
                    EXIT WHEN curs3%NOTFOUND;
                    IF rec3.szulo = rec2.jid THEN
                        gyerekNum := gyerekNum + 1;
                    END IF;
                END LOOP;
                CLOSE curs3;
            END IF;
        END LOOP;
        CLOSE curs2;
        
        IF gyerekNum > maxGyerek THEN
            maxGyerek := gyerekNum;
            maxCsapat := rec1.csapatnev;
        END IF;
    END LOOP;
    CLOSE curs1;
    dbms_output.put_line(maxCsapat);
END;

--6
DECLARE 
   maxEltiltas NUMBER;
   jatekosEltiltas NUMBER;
   maxCsapat CHAR(30);
   eltiltas NUMBER;
   CURSOR curs1 IS SELECT * FROM Focicsapat;
   rec1 curs1%ROWTYPE;
BEGIN 
    maxEltiltas := 0;
    OPEN curs1;
    LOOP
        FETCH curs1 INTO rec1;
        EXIT WHEN curs1%NOTFOUND;
        
        
        SELECT SUM(FLOOR(lapok_szama / 5)) INTO eltiltas
        FROM Jatekos
        WHERE fazon = rec1.fazon;
    
        IF eltiltas > maxEltiltas THEN
            maxEltiltas := eltiltas;
            maxCsapat := rec1.csapatnev;
        END IF;
        
    END LOOP;
    dbms_output.put_line(maxCsapat);
END;



--7
CREATE OR REPLACE VIEW Testverek AS
SELECT gy1.nev nev1, gy2.nev nev2
FROM Gyerek gy1, Gyerek gy2
WHERE   gy1.nev != gy2.nev AND
        gy1.szulo = gy2.szulo;
        
SELECT *
FROM Testverek;
        
--8
SELECT gy1.nev, gy2.nev
FROM  Gyerek gy1, Gyerek gy2
WHERE
        (
            SELECT fazon
            FROM Jatekos J
            WHERE J.jid = gy1.szulo
        )
        =
        (
            SELECT fazon
            FROM Jatekos J
            WHERE J.jid = gy2.szulo
        )
        AND
        gy2.nev NOT IN(
            SELECT nev2
            FROM Testverek
            WHERE nev1 = gy1.nev
        )
        AND
        gy2.nev != gy1.nev;
        
        
        
