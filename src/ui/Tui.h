#ifndef EE_TUI_H
#define EE_TUI_H

#include <unistd.h>
#include <termios.h>

class Tui 
{
public:
	Tui();
	~Tui();

	int exec();

private:
	struct termios _orig_termios;
};

#endif // EE_TUI_H
