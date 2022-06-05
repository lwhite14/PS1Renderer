#include "src/runner.h"
#include "src/scenes/render_texture_scene.h"

int main()
{
	Runner runner = Runner("PS1 Renderer", 1200, 900);
	Scene* base;
	Basic_Scene derived;
	base = &derived;
	return runner.Run(*base);
}