#include <cstdio>
#include <cctype>

#include "Tui.h"

Tui::Tui()
{
	// enable raw mode
	tcgetattr(STDIN_FILENO, &_orig_termios);

	struct termios raw = _orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

	puts("Tui obiect constructed");
}

Tui::~Tui()
{
	// disable raw mode
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &_orig_termios);
	puts("Tui obiect destructed");
}

int Tui::exec()
{
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\n", c);
		} else {
			printf("%d ('%c')\n", c, c);
		}
	}
	return 0;
}

