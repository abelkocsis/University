-- Basis: tutorial code
create database if not exists deviceData;
use deviceData;

drop table if exists d1;
create table d1(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    timestamp varchar(255),
    magnetoX float(8, 2),
    magnetoY float(8, 2),
    magnetoZ float(8, 2),
    gyroX float(8, 2),
    gyroY float(8, 2),
    gyroZ float(8, 2),
    acceleroX float(8, 2),
    acceleroY float(8, 2),
    acceleroZ float(8, 2)
);

drop user 'd1_user'@'localhost';
create user 'd1_user'@'localhost' identified by 'R4EzqtcqY4Nz669sSmjja2d8tCyTNu';
grant select, update, insert, delete on deviceData.d1 to 'd1_user'@'localhost';

drop table if exists activitySum;
create table activitySum(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    idle INT,
    walk INT,
    run INT,
    stair INT,
    elevator INT
);

grant select, update, insert, delete on deviceData.activitySum to 'd1_user'@'localhost';

drop table if exists dailyActivity;
create table dailyActivity(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    userId INT,
    activityDate date,
    idle INT,
    walk INT,
    run INT,
    stair INT,
    elevator INT
);

grant select, update, insert, delete on deviceData.dailyActivity to 'd1_user'@'localhost';