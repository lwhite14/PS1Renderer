#include "src/runner.h"
#include "src/scenes/render_texture_scene.h"

int main()
{
	Runner runner = Runner("First-Person Render Pipeline", 1080, 864);
	Scene* base;
	Basic_Scene derived;
	base = &derived;
	return runner.Run(*base);
}