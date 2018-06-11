#include "CFFMpeg.h"
#include <tchar.h>
#include "MyListener.h"

#define __STDC_CONSTANT_MACROS

int _tmain(int argc, _TCHAR* argv[]){
	printf("ss");
	MyListener listener;
	CFFMpeg mpeg(&listener);
	//mpeg.OpenInput("gdigrab","desktop");
	mpeg.OpenInput(NULL,"rtsp://192.168.0.13:8554/myData.264");
	//mpeg.OpenInput("vfwcap","0");
	mpeg.FindAV();
	mpeg.Process();
	mpeg.CloseInput();

	system("pause");
	return 0;
}