#include <cstdio>
#include <cctype>

#include "Tui.h"

Tui::Tui()
{
	// enable raw mode
	tcgetattr(STDIN_FILENO, &_orig_termios);

	struct termios raw = _orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= ~(CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

	puts("Tui obiect constructed\r\n");
}

Tui::~Tui()
{
	// disable raw mode
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &_orig_termios);
	puts("Tui obiect destructed");
}

int Tui::exec()
{
	while (1){
		char c = '\0';
		read(STDIN_FILENO, &c, 1);
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		if (c == 'q') break;
	}
	return 0;
}

