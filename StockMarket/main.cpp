#include <iostream>
#include <stddef.h>
#include "Market.h"
#include "menus.h"



int main()
{
	Market::instance();

	initialMenu();
	 
	return EXIT_SUCCESS;
}
