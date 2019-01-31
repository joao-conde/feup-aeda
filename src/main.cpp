#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "Market.h"
#include "menus.h"



int main()
{
	Market::instance();

	initialMenu();
	 
	return EXIT_SUCCESS;
}
