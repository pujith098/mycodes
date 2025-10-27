#include<iostream>

class peddabbulu{
	private:
		int fame;
	protected:
		float home;
	public:
		int assets;

		void will_of_law(int a,float b , int c )
		{
			fame = a;
			home =b;
			assets =c;
		}
};
class raju{
	private:
		int strength;
	protected:
		int loan;
	public:
		peddabbulu xyz;
		
		void his_value()
		{
			strength = 100;
			loan = 150;
			xyz.will_of_law(12,13,15);
		}
};


using namespace std;

int main()
{
	raju var;
	var.his_value();
	return 0;
}



