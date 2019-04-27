/*#include <iostream>
#include "enor.h"

using namespace std;

int main(){
	Enor e("inp.txt");
	bool l = false;
	e.first();
	while(!l && !e.end()){
		l = e.current() == "Kocsis Abel";
		//cout << e.current() << endl << l << endl;
		e.next();
	}
	cout << (l?"Benne vagy":"Nem vagy benne") << endl;
	return 0;
}*/

#include <iostream>
#include "enor2.h"

int main(){
	Enor2 e("inp.txt");
	bool l = false;
	e.first();
	while(!l && !e.end()){
		l = e.current() == "Kocsis Abel";
		std::cout << e.current() << std::endl;
		//cout << e.current() << endl << l << endl;
		e.next();
	}
	std::cout << (l?"Benne vagy":"Nem vagy benne") << std::endl;
	return 0;
}