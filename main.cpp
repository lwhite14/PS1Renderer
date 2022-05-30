#include "src/runner.h"
#include "src/scenes/render_texture_scene.h"

int main()
{
	//Runner runner = Runner("First-Person Render Pipeline", 800, 600);
	Runner runner = Runner("Render Texture", 1600, 900);
	Scene* base;
	//Basic_Scene derived;
	RenderTexture_Scene derived;
	base = &derived;
	return runner.Run(*base);
}