#include <easy2d.h>
#include "SplashScene.h"
#include "ImageLoader.h"

int main()
{
	App app;
	app.createWindow(_T("FlappyBird"), 288, 512);
	app.setAppName(_T("flappybird_nomango"));
	if (ImageLoader::init())
	{
		app.enterScene(new SplashScene());
		return app.run();
	}
	return 0;
}