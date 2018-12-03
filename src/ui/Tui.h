#ifndef EE_TUI_H
#define EE_TUI_H

#include <unistd.h>
#include <termios.h>
#include <memory>

namespace ee {
class Tui
{
public:
	Tui();
	~Tui();
	//ToDo: copy- and move- ctors/operator= methods

	int exec();

private:
	class TuiImpl;
	std::unique_ptr<TuiImpl> impl_;
}; // class Tui
} // namespace ee

#endif // EE_TUI_H
