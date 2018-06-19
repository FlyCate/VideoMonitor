#include "MyListener.h"


MyListener::MyListener(void)
{
	win = new CSDLVideo();
}


MyListener::~MyListener(void)
{
}

void MyListener::onVideoFrame(AVFrame* frame){
	//printf("MyListener onVideoFrame!\n");
	win->ShowAVFrame(frame);
}

void MyListener::onVideoSize(int width, int height,AVPixelFormat format)
{
	printf("MyListener onVideoSize! width = %d height = %d\n", width, height);
	win->OpenVideo(width,height,format);

}