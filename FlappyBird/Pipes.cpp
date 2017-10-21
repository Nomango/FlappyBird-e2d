#include "Pipes.h"
#include "ImageLoader.h"


Pipes::Pipes()
{
	// 添加三根水管
	addPipe();
	addPipe();
	addPipe();
}


Pipes::~Pipes()
{
}

void Pipes::start()
{
	auto timer = new ETimer([=](int) {
		// 移动所有水管
		for (int i = 0; i < number; i++) {
			pipes[i][0]->move(-2, 0);
			pipes[i][1]->move(-2, 0);
		}
		if (pipes[0][0]->getPosX() <= -pipes[0][0]->getWidth()) {
			// 若第一个水管出界，删除这个水管
			this->removeChild(pipes[0][0]);
			this->removeChild(pipes[0][1]);
			// 释放水管占用的资源
			pipes[0][0]->autoRelease();
			pipes[0][1]->autoRelease();
			// 移动数组中指针的位置
			pipes[0][0] = pipes[1][0]; pipes[0][1] = pipes[1][1];
			pipes[1][0] = pipes[2][0]; pipes[1][1] = pipes[2][1];
			// 水管数量减一
			number--;
			// 添加一个新水管
			addPipe();
		}
	});
	timer->bindWith(this);
}

void Pipes::stop()
{
	ETimerManager::stopAllTimersBindedWith(this);
}

void Pipes::addPipe()
{
	// 水管最大数量为 3
	if (this->number == 3) return;
	// 随机水管位置
	float pipeY = ERandom::between(100, EApp::getHeight() - ImageLoader::getImage(L"land")->getHeight() - 100);
	// 创建上水管
	auto pipe1 = new ESprite(ImageLoader::getImage(L"pipe_above"));
	pipe1->setAnchor(0.5f, 1);
	pipe1->setPosY(pipeY - 60);
	this->addChild(pipe1);
	// 创建下水管
	auto pipe2 = new ESprite(ImageLoader::getImage(L"pipe_below"));
	pipe2->setAnchor(0.5f, 0);
	pipe2->setPosY(pipeY + 60);
	this->addChild(pipe2);
	// 设置水管横坐标
	if (number == 0) {
		// 第一个水管在屏幕外130像素处
		pipe1->setPosX(EApp::getWidth() + 130);
		pipe2->setPosX(EApp::getWidth() + 130);
	}
	else {
		// 其他水管在前一个水管后方200像素处
		pipe1->setPosX(pipes[number - 1][0]->getPosX() + 200);
		pipe2->setPosX(pipes[number - 1][1]->getPosX() + 200);
	}
	// 保存到数组
	pipes[number][0] = pipe1;
	pipes[number][1] = pipe2;
	// 水管数量加一
	number++;
}
