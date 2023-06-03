//статический стек неупорядоченных двунаправленных динамических списков
//торговая фирма (название) - композиция поставщиков (имена)
//поставщик - композиция товаров (название, количество)

#include <iostream>
#include "Firm.h"
#include "Provider.h"
#include "Product.h"
#include "Menu.h"
#include <string>

int main()
{
	run();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}

