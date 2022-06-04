#include "src/runner.h"
#include "src/scenes/render_texture_scene.h"

int main()
{
	Runner runner = Runner("First-Person Render Pipeline", 800, 600);
	Scene* base;
	Basic_Scene derived;
	base = &derived;
	return runner.Run(*base);
}