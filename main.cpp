#include "src/runner.h"

int main()
{
	Runner runner = Runner("New Window", 800, 600);
	Scene* base;
	Basic_Scene derived;
	base = &derived;
	return runner.Run(*base);
}