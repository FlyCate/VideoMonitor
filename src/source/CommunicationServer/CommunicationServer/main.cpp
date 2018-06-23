#include <stdio.h>
#include <windows.h>
#include "common.h"

CFreeLogBase * g_Log = NULL;

int main(int argc, char ** argv)
{
	g_Log = CFreeLogBase::CreateFreeLogObject();
	g_Log->SetLogFileName("CommunicationServer");
	g_Log->LogMessage(LOG_LEVEL_INFO, "CommunicationServer Start!");

	g_Log->LogMessage(LOG_LEVEL_ERROR, "CommunicationServer error1!");
	g_Log->LogMessage(LOG_LEVEL_CRITICLE, "CommunicationServer CRITICAL!");

	//g_Log->SetLogLevel(LOG_LEVEL_ERROR);

	while (1)
	{
		g_Log->LogMessage(LOG_LEVEL_INFO, "CommunicationServer CRITICAL!");
		Sleep(1000);
	}

	g_Log->LogMessage(LOG_LEVEL_INFO, "CommunicationServer End!");

  	return 0;
}