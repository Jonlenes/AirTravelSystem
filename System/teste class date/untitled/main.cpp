#include <iostream>
#include "Date.h"
using namespace std;

int main() {
	string s1, s2;
	int h, m;
	
	while(1) {
        /*cin >> s1 >> s2;
		
		Date d1(s1), d2(s2);
		
		cout << d1.getHours() << endl;
		cout << d1.getMinutes() << endl;
		cout << d2.getHours() << endl;
		cout << d2.getMinutes() << endl;
        cout << d2 - d1 << endl;*/
		
		cin >> h >> m;
		
		Date d3(h, m);
		cout << d3.getHours() << endl;
		cout << d3.getMinutes() << endl;
		cout << d3.toString() << endl;  
	}
	return 0;
}
