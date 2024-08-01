#include <iostream>
#include "shared_ptr.h"
int main()
{

	shared_ptr<int> ptr1(new int(42));
	shared_ptr<int> ptr2 = ptr1;
	*ptr2 = 100;
	std::cout<<"Corect";
 	return 0;
}
