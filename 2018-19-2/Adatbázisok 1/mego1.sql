DROP TABLE Gyerek;
DROP TABLE Jatekos;
DROP TABLE Focicsapat;



CREATE TABLE Focicsapat (
    fazon CHAR(5) UNIQUE,
    mez CHAR(20),
    csapatnev CHAR(30)

);

CREATE TABLE Jatekos (
    jid CHAR(20) PRIMARY KEY,
    szuletesi_nev CHAR(40) NOT NULL,
    golok_szama NUMBER DEFAULT 0 CONSTRAINT maxGolszam
                CHECK (golok_szama <= 100),
    lapok_szama NUMBER DEFAULT 0 CONSTRAINT maxLapszam
                CHECK (lapok_szama <= 100),
    merkozesek_szama NUMBER DEFAULT 0,
    fazon CHAR(5) REFERENCES Focicsapat(fazon),
    gyereknev VARCHAR(100)
);

CREATE TABLE Gyerek (
    szulo CHAR(20),
    nev CHAR(20) NOT NULL,
    SzulDat DATE,
    FocistaLesz CHAR(1) CONSTRAINT IgenVagyNem
                        CHECK (FocistaLesz IN ('I', 'N')),
    FOREIGN KEY (szulo) REFERENCES Jatekos(jid)
);

INSERT INTO Focicsapat (fazon, mez, csapatnev)
VALUES ('RM', 'feher', 'Real Madrid');

INSERT INTO Focicsapat (fazon, mez, csapatnev)
VALUES ('PE', 'zold', 'Pereszteg');

INSERT INTO Focicsapat (fazon, mez, csapatnev)
VALUES ('SOP', 'piros', 'Spanyolország');

INSERT INTO Jatekos (jid, szuletesi_nev, golok_szama, lapok_szama, merkozesek_szama, fazon, gyereknev)
VALUES ('0012', 'Kovács Béla', 12, 29, 42, 'PE', 'Kovács János, Kovács Erika, Kovács Eszter');

INSERT INTO Jatekos (jid, szuletesi_nev, golok_szama, lapok_szama, merkozesek_szama, fazon, gyereknev)
VALUES ('0069', 'Horváth Géza', 7, 4, 35, 'PE', 'Horváth Ádám');

INSERT INTO Jatekos (jid, szuletesi_nev, merkozesek_szama, fazon)
VALUES ('0124', 'Lakatos József', 6, 'PE');


INSERT INTO Jatekos (jid, szuletesi_nev, golok_szama, lapok_szama, merkozesek_szama, fazon, gyereknev)
VALUES ('2314', 'Marcelo', 46, 87, 99, 'RM', 'Kis Marcelo, Nagyonkis Marcelo');

INSERT INTO Jatekos (jid, szuletesi_nev, golok_szama, lapok_szama, merkozesek_szama, fazon, gyereknev)
VALUES ('2414', 'Baela', 11, 2, 99, 'RM', 'Kis Baela');

INSERT INTO Jatekos (jid, szuletesi_nev, golok_szama, lapok_szama, merkozesek_szama, fazon, gyereknev)
VALUES ('2394', 'Sergio Ramos', 50, 99, 99, 'RM', 'Gareth Ramos');

INSERT INTO Jatekos(jid, szuletesi_nev, merkozesek_szama, fazon)
VALUES ('0001', 'Huszti Szabolcs', 41, 'SOP');

INSERT INTO Jatekos(jid, szuletesi_nev, merkozesek_szama, fazon)
VALUES ('0002', 'Holzmann Zoltán', 6, 'SOP');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('0012', 'Kovács János', TO_DATE('1998-03-12', 'YYYY-MM-DD'), 'I');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('0012', 'Kovács Erika', TO_DATE('2000-05-21', 'YYYY-MM-DD'), 'I');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('0012', 'Kovács Eszter', TO_DATE('2002-07-30', 'YYYY-MM-DD'), 'N');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('0069', 'Horváth Ádám', TO_DATE('1995-08-31', 'YYYY-MM-DD'), 'N');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('2314', 'Kis Marcelo', TO_DATE('2008-06-09', 'YYYY-MM-DD'), 'I');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('2414', 'Kis Baela', TO_DATE('2012-01-31', 'YYYY-MM-DD'), 'I');

INSERT INTO Gyerek (szulo, nev, SzulDat, FocistaLesz)
VALUES ('2394', 'Gareth Ramos', TO_DATE('2016-02-14', 'YYYY-MM-DD'), 'I');



GRANT SELECT
ON Focicsapat
TO Sila;

GRANT SELECT
ON Jatekos
TO Sila;

GRANT SELECT
ON Gyerek
TO Sila;


