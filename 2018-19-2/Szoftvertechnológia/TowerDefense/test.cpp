// #include "pch.h"
#include "TowerDefense/GameModel.h"
#include <gtest/gtest.h>

TEST(InitTest, CastleHpTest) {
	GameModel m;
	m.init(0,"1.1.1.1","12345");
	int hp1 = m.getCastleHp(p1);
	int hp2 = m.getCastleHp(p2);
	EXPECT_EQ(hp1, 300);
	EXPECT_EQ(hp2, 300);
}

TEST(InitTest, MapInitTest) {
	GameModel m;
	m.init(0,"1.1.1.1","12345");
	
	EXPECT_EQ(m.getMap()[12][12].Status, Free);
	EXPECT_EQ(m.getMap()[8][7].Obj, Empty);
	EXPECT_EQ(m.getMap()[7][7].Whose, nobody);
}

TEST(InitTest, PlayerInit) {
	GameModel m;
	m.init(0,"1.1.1.1","12345");
	EXPECT_EQ(m.getCurrentPlayer(), p1);
	EXPECT_EQ(m.getMoney(p1), 100);
	EXPECT_EQ(m.getMoney(p2), 100);
}

TEST(InitTest, CastlePlaceInit) {
	GameModel m;
	m.init(0,"1.1.1.1","12345");
	EXPECT_EQ(m.getMap()[7][0].Obj, Castle1);
	EXPECT_EQ(m.getMap()[7][0].Whose, p1);
	EXPECT_EQ(m.getMap()[7][0].Status, Occupied);
	EXPECT_EQ(m.getMap()[8][0].Status, Unobtainable);

	EXPECT_EQ(m.getMap()[7][24].Obj, Castle2);
	EXPECT_EQ(m.getMap()[7][24].Whose, p2);
	EXPECT_EQ(m.getMap()[7][24].Status, Occupied);
	EXPECT_EQ(m.getMap()[6][23].Status, Unobtainable);
}


TEST(TestCaseName2, TestName2) {
	GameModel m;
	m.init(0,"1.1.1.1","12345");
}

TEST(ToStringTest, FieldTest) {
	Field f;
	std::string s = f.toString();
	EXPECT_EQ(s, "0;7;2.");

	Field f2(Occupied, Tower2, p2);
	std::string s2 = f2.toString();
	EXPECT_EQ(s2, "2;1;1.");
}
TEST(FromStringTest, FieldTest) {
	Field myf("3;2;1.");
	myf.Status == Unobtainable;
	myf.Obj == Tower3;
	myf.Whose == p2;
}


TEST(ToStringTest, SoldierTest) {
	Soldier sol(Soldier1, 50, 10, Coordinate(3, 5));

	std::string s = sol.toString();
	EXPECT_EQ(s, "3;1;50;10;3;5.");

}

TEST(FromStringTest, SoldierTest) {
	Soldier sol("3;1;50;10;3;5.");
	EXPECT_EQ(sol.getDamage(), 10);
	EXPECT_EQ(sol.getPos(), Coordinate(3,5));

}

TEST(ToStringTest, TowerTest) {
	Tower t(3,10,Coordinate(3, 5));

	std::string s = t.toString();
	EXPECT_EQ(s, "3;10;3;5.");

}

TEST(FromStringTest, TowerTest) {
	Tower t("3;10;3;5.");
	std::string s = t.toString();
	EXPECT_EQ(s, "3;10;3;5.");
	
}

TEST(ToStringTest, PlayerTest) {
	Player p;
	p.castle_hp = 250;
	p.money = 178;
	p.soldiers.push_back(Soldier(Soldier1, 50, 10, Coordinate(3, 5)));
	p.soldiers.push_back(Soldier(Soldier3, 50, 30, Coordinate(8, 6)));
	p.soldiers.push_back(Soldier(Soldier2, 100, 10, Coordinate(4, 6)));

	p.towers.push_back(Tower(3, 10, Coordinate(5, 5)));
	p.towers.push_back(Tower(4,6,Coordinate(12,5)));


	std::string s = p.toString();

	EXPECT_EQ(s, "178|250|3;10;5;5.4;6;12;5.|3;1;50;10;3;5.5;1;50;30;8;6.4;1;100;10;4;6.#");

}


TEST(FromStringTest, PlayerTest) {
	Player p("178|250|3;10;5;5.4;6;12;5.|3;1;50;10;3;5.5;1;50;30;8;6.4;1;100;10;4;6.#");
	
	EXPECT_EQ(p.toString(), "178|250|3;10;5;5.4;6;12;5.|3;1;50;10;3;5.5;1;50;30;8;6.4;1;100;10;4;6.#");



}


TEST(ToStringTest, GameModelTest) {
	// todo
}


TEST(FromStringTest, GameModelTest) {
	// todo
	std::string input = "50|300|2;5;7;4.|3;1;40;10;6;4.4;1;100;10;7;3.#35|300|4;5;8;21.|3;1;40;10;7;20.3;1;40;10;7;22.#0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.3;7;2.3;7;2.0;7;2.0;7;2.1;3;0.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.3;7;2.3;7;2.3;8;0.3;7;2.0;7;2.1;4;0.2;0;0.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.1;3;1.0;7;2.1;3;1.3;7;2.3;9;1.3;7;2.3;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.2;1;1.0;7;2.3;7;2.3;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.0;7;2.#0#";
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	gm.fromString(input);
	EXPECT_EQ(gm.getMap()[7][7].Status, Free);
	EXPECT_EQ(gm.getMoney(p1), 50);
	EXPECT_EQ(gm.getCurrentPlayer(), p1);
	EXPECT_EQ(gm.toString(), input);
}

TEST(RoundTest, passTest) {
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	S s = gm.getMap()[7][1].Status;
	S s2 = gm.getMap()[7][23].Status;
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.getMap()[7][1].Status, s);
	EXPECT_EQ(gm.getMap()[7][23].Status, s2);
}

TEST(RoundTest, calcRoutesTest) {
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	gm.getField(8,0).Status = Occupied;
	gm.getField(6, 1).Status = Occupied;
	gm.getField(7, 1).Status = Occupied;
	gm.getField(8, 1).Status = Occupied;
	gm.getField(0, 3).Status = Occupied;
	gm.getField(1, 3).Status = Occupied;
	gm.getField(2, 3).Status = Occupied;
	gm.getField(4, 3).Status = Occupied;
	gm.getField(6, 3).Status = Occupied;
	gm.getField(7, 3).Status = Occupied;
	gm.getField(8, 3).Status = Occupied;
	gm.getField(9, 3).Status = Occupied;
	gm.getField(10, 3).Status = Occupied;
	gm.getField(11, 3).Status = Occupied;

	EXPECT_EQ(gm.getMap()[8][0].Status, Occupied);
	
	gm.round(0, Coordinate());

	EXPECT_EQ(gm.getParentToC1()[6][0].row, 7);
	EXPECT_EQ(gm.getParentToC1()[6][0].col, 0);
	EXPECT_EQ(gm.getParentToC1()[3][0].row, 4);
	EXPECT_EQ(gm.getParentToC1()[3][0].col, 0);
	EXPECT_EQ(gm.getParentToC1()[5][2].row, 5);
	EXPECT_EQ(gm.getParentToC1()[5][2].col, 1);
	EXPECT_EQ(gm.getParentToC1()[9][0].row, 9);
	EXPECT_EQ(gm.getParentToC1()[9][0].col, 1);

}


TEST(RoundTest, checkTowerTest) {
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	gm.getField(7, 3).Status = Occupied;
	EXPECT_EQ(gm.round(1, Coordinate(7,3)), false);
	gm.getField(8, 0).Status = Occupied;
	gm.getField(6, 1).Status = Occupied;
	gm.getField(7, 1).Status = Occupied;
	gm.getField(8, 1).Status = Occupied;
	EXPECT_EQ(gm.round(1, Coordinate(6, 0)), false);
	
}


TEST(RoundTest, createTowerTest) {
 	GameModel gm;
 	gm.init(0,"1.1.1.1","12345");
 	gm.round(1, Coordinate(7, 2));
 	EXPECT_EQ(gm.getField(7, 2).Status, Occupied);
 	EXPECT_EQ(gm.getField(7, 2).Obj, Tower1);
 	EXPECT_EQ(gm.getField(7, 2).Whose, p1);
 	gm.init(0,"1.1.1.1","12345");
 	ASSERT_FALSE(gm.round(2, Coordinate(7, 20)));
 	gm.round(2, Coordinate(7, 20));
 	EXPECT_EQ(gm.getField(7, 20).Status, Occupied);
 	EXPECT_EQ(gm.getField(7, 20).Obj, Tower2);
 	EXPECT_EQ(gm.getField(7, 20).Whose, p1);
 	gm.init(0,"1.1.1.1","12345");
 	gm.round(3, Coordinate(7, 20));
 	EXPECT_EQ(gm.getField(7, 20).Status, Occupied);
 	EXPECT_EQ(gm.getField(7, 20).Obj, Tower3);
 	EXPECT_EQ(gm.getField(7, 20).Whose, p1);
 }

 TEST(SoldierTest, createSoldierTest){
	GameModel gm;
 	gm.init(0,"1.1.1.1","12345");
	gm.round(4, Coordinate());
	EXPECT_EQ(gm.getField(7, 2).Status, Sol);
 	EXPECT_EQ(gm.getField(7, 2).Obj, Soldier1);
 	EXPECT_EQ(gm.getField(7, 2).Whose, p1);
	
	gm.round(5, Coordinate());
	EXPECT_EQ(gm.getField(7, 22).Status, Sol);
 	EXPECT_EQ(gm.getField(7, 22).Obj, Soldier2);
 	EXPECT_EQ(gm.getField(7, 22).Whose, p2);
	
	gm.round(6, Coordinate());
	EXPECT_EQ(gm.getField(7, 2).Status, Sol);
 	EXPECT_EQ(gm.getField(7, 2).Obj, Soldier3);
 	EXPECT_EQ(gm.getField(7, 2).Whose, p1);
 }

 TEST(SoldierTest, setPosTest){
	GameModel gm;
 	gm.init(0,"1.1.1.1","12345");
	gm.round(4, Coordinate());
	gm.player1.soldiers[0].setPos(Coordinate(9,12));
	EXPECT_EQ(gm.player1.soldiers[0].getPos().col, 12);
	EXPECT_EQ(gm.player1.soldiers[0].getPos().row, 9);
 }

TEST(SoldierTest, hitTest){
	GameModel gm;
 	gm.init(0,"1.1.1.1","12345");
	gm.round(4, Coordinate());
	gm.round(6, Coordinate());

	gm.player1.soldiers[0].setPos(Coordinate(7,23));
	gm.player2.soldiers[0].setPos(Coordinate(7,1));

	int hp1 = gm.getCastleHp(p1);
	int hp2 = gm.getCastleHp(p2);
	EXPECT_EQ(hp1, 300);
	EXPECT_EQ(hp2, 300);
	gm.round(0, Coordinate());

	hp1 = gm.getCastleHp(p1);
	hp2 = gm.getCastleHp(p2);
	EXPECT_EQ(hp1, 280);
	EXPECT_EQ(hp2, 290);
}

TEST(SoldierTest, soldiersStepTest){
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	gm.round(0, Coordinate());
	gm.round(4, Coordinate());
	gm.getField(8,0).Status = Occupied;
	gm.getField(6, 1).Status = Occupied;
	gm.getField(7, 1).Status = Occupied;
	gm.getField(8, 1).Status = Occupied;
	gm.getField(0, 3).Status = Occupied;
	gm.getField(1, 3).Status = Occupied;
	gm.getField(2, 3).Status = Occupied;
	gm.getField(4, 3).Status = Occupied;
	gm.getField(6, 3).Status = Occupied;
	gm.getField(7, 3).Status = Occupied;
	gm.getField(8, 3).Status = Occupied;
	gm.getField(9, 3).Status = Occupied;
	gm.getField(10, 3).Status = Occupied;
	gm.getField(11, 3).Status = Occupied;

	gm.player2.soldiers[0].setPos(Coordinate(5,2));

	gm.round(0, Coordinate());

	EXPECT_EQ(gm.getField(5, 2).Status, Free);
 	EXPECT_EQ(gm.getField(5, 2).Obj, Empty);
 	EXPECT_EQ(gm.getField(5, 2).Whose, nobody);

	EXPECT_EQ(gm.getField(5, 1).Status, Sol);
 	EXPECT_EQ(gm.getField(5, 1).Obj, Soldier1);
 	EXPECT_EQ(gm.getField(5, 1).Whose, p2);

}

TEST(TowerTest, TowersFireTest){
	GameModel gm;
	gm.init(0,"1.1.1.1","12345");
	gm.round(4, Coordinate());
	gm.player1.soldiers[0].setPos(Coordinate(5,20));
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 40);
	gm.round(1, Coordinate(4,20));
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 35);
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 35);
	
	gm.player1.soldiers[0].setPos(Coordinate(7,21));
	gm.round(2, Coordinate(7,22));
	
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 30);
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 25);
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 20);
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 15);


	gm.init(0,"1.1.1.1","12345");
	gm.round(4, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 40);
	gm.player1.soldiers[0].setPos(Coordinate(7,15));
	gm.round(3, Coordinate(7,16));
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 30);
	gm.round(0, Coordinate());
	EXPECT_EQ(gm.player1.soldiers[0].getHp(), 20);



}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}