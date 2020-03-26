#include <bits/stdc++.h>

using namespace std;

class Port{
	int com;
	public:
		virtual void notice()const = 0;
}; 

class Inhernt : public Port{
	public:
		virtual void notice() const {
			cout << "Inhernt notice" << endl;
		}
};

class Subject{
	Port s;
	public:
		void exert(){
			s.notice();
		}
};

int main(){
	Subject s;
	s.exert();
}
