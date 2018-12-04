#include <unistd.h>
#include <termios.h>

#include "Tui.h"

using namespace ee;

#define CTRL_KEY(k) ((k) & 0x1f)

class Tui::TuiImpl
{
public:
	TuiImpl()
	{
		// enable raw mode
		if (tcgetattr(STDIN_FILENO, &orig_termios_) == -1) {
			throw std::runtime_error(
					"Tui::Tui(): "\
					"tcsetattr(tcgetattr(STDIN_FILENO, &_e.origTermios) "\
					"returned -1");
		}

		struct termios raw = orig_termios_;

		raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		raw.c_oflag &= ~(OPOST);
		raw.c_cflag |= ~(CS8);
		raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		raw.c_cc[VMIN] = 0;
		raw.c_cc[VTIME] = 1;

		tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

		// ToDo: remove:
		puts("Tui object constructed\r\n");
	}

	~TuiImpl()
	{
		try {
			disableRawMode();
		}
		catch (...) {} // prevents exceptions thrown from disableRawMode
		               // from propagating beyond TuiImpl's destructor
	    // http://bin-login.name/ftp/pub/docs/programming_languages/cpp/cffective_cpp/MEC/MI11_FR.HTM

		// ToDo: remove:
		puts("Tui object destructed");
	}

	int exec()
	{
		while (uiReadKey() != CTRL_KEY('q')){
			//uiProcessKeypress();
		}
		return 0;
	}

private:
	struct termios orig_termios_;

	void disableRawMode()
	{
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios_) == -1) {
			throw std::runtime_error(
					"Tui::disableRawMode(): tcsetattr() returned -1");
		}
	}

	char uiReadKey()
	{
		int nread;
		char c;
		while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
			if (nread == -1 && errno != EAGAIN) {
				throw std::runtime_error("Tui::exec(): read() returned -1");
			}
		}
		return c;
	}

	/*
	void uiProcessKeypress()
	{
		char c = uiReadKey();
		switch (c) {
			case CTRL_KEY('q'):
				//ToDo: pass to mode_
				exit(0);
				break;
		}
	}
	*/
};

Tui::Tui() : impl_(new TuiImpl) {}
Tui::~Tui() = default;

int Tui::exec() {
	return impl_->exec();
}
