#include "PacketListener.h"


PacketListener::PacketListener(void)
{
}


PacketListener::~PacketListener(void)
{
}


void PacketListener::onRecvPacket(AVPacket* packet) {
	//printf("PacketListener onRecvPacket");
}
void PacketListener::onVideoFrame(AVFrame* frame){
	//printf("PacketListener onVideoFrame");
}
void PacketListener::onAudioFrame(AVFrame* frame){
	//printf("PacketListener onAudioFrame");
}

void PacketListener::onVideoSize(int width, int height,AVPixelFormat format)
{
	printf("PacketListener onVideoSize! width = %d height = %d\n", width, height);

}
