#include<iostream>

using namespace std;

namespace one {
int x =10;
}

namespace two {
int x = 20;
}

int main()
{

using namespace one;
//cout<<one::x<<endl;
//cout<<two::x<<endl;

cout<<x<<endl;
using namespace two;
cout<<x<<endl;
return 0;
}
