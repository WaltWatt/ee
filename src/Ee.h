#ifndef EE_EE_H
#define EE_EE_H

namespace ee {
class Ee
{
public:
	Ee(const int &argc, char **argv);
	~Ee();

	int exec();
private:
};
} // namespace ee

#endif // EE_EE_H
