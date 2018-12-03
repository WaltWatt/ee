#include <cstdio>

#include "Ee.h"
#include "ui/Tui.h"

using namespace ee;

Ee::Ee(const int &argc, char **argv)
{
	puts("Ee constructor called...");
	printf("  ...arguments count: %d\n", argc);
	printf("  ...program name: %s\n", argv[0]);
	puts("Ee object constructed");
}

Ee::~Ee()
{
	puts("Ee object destructed");
}

int Ee::exec()
{
	Tui tui;
	return tui.exec();
}
