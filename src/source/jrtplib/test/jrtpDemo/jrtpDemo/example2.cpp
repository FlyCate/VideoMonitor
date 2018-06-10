#include "rtpsession.h"
#include "rtpsessionparams.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtptimeutilities.h"
#include "rtppacket.h"
#include <stdlib.h>
#include <iostream>

using namespace jrtplib;

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		printf(" ‰»Î≤Œ ˝¥ÌŒÛ!\n");
		system("pause");
		return -1;
	}

	int nLocalPort = atoi(argv[1]);
	int nClientPort = atoi(argv[2]);

#ifdef RTP_SOCKETTYPE_WINSOCK
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
#endif // RTP_SOCKETTYPE_WINSOCK
		
	RTPSession session;
	
	RTPSessionParams sessionparams;
	sessionparams.SetOwnTimestampUnit(1.0/8000.0);
			
	RTPUDPv4TransmissionParams transparams;
	transparams.SetPortbase(nLocalPort);
			
	int status = session.Create(sessionparams,&transparams);
	if (status < 0)
	{
		std::cerr << RTPGetErrorString(status) << std::endl;
		exit(-1);
	}
	
	uint8_t localip[]={127,0,0,1};
	RTPIPv4Address addr(localip, nClientPort);
	
	status = session.AddDestination(addr);
	if (status < 0)
	{
		std::cerr << RTPGetErrorString(status) << std::endl;
		exit(-1);
	}
	
	session.SetDefaultPayloadType(96);
	session.SetDefaultMark(false);
	session.SetDefaultTimestampIncrement(160);
	
	uint8_t silencebuffer[160];
	for (int i = 0 ; i < 160 ; i++)
		silencebuffer[i] = 128;

	RTPTime delay(1);
	RTPTime starttime = RTPTime::CurrentTime();

	memset(silencebuffer, 0, 160);
	std::cin >> silencebuffer;
	bool done = false;
	while (!done)
	{
		printf("sendData: %s\n", silencebuffer);
		status = session.SendPacket(silencebuffer, strlen((const char *)silencebuffer));
		if (status < 0)
		{
			std::cerr << RTPGetErrorString(status) << std::endl;
			exit(-1);
		}
		
// 		session.BeginDataAccess();
// 		if (session.GotoFirstSource())
// 		{
// 			do
// 			{
// 				RTPPacket *packet;
// 
// 				while ((packet = session.GetNextPacket()) != 0)
// 				{
// 					std::cout << "Got packet with " 
// 					          << "extended sequence number " 
// 					          << packet->GetExtendedSequenceNumber() 
// 					          << " from SSRC " << packet->GetSSRC() 
// 					          << std::endl;
// 					session.DeletePacket(packet);
// 				}
// 			} while (session.GotoNextSource());
// 		}
// 		session.EndDataAccess();
			
		RTPTime::Wait(delay);
		
		RTPTime t = RTPTime::CurrentTime();
		t -= starttime;
		if (t > RTPTime(60.0))
			done = true;
	}
	
	delay = RTPTime(10.0);
	session.BYEDestroy(delay,"Time's up",9);
	
#ifdef RTP_SOCKETTYPE_WINSOCK
	WSACleanup();
#endif // RTP_SOCKETTYPE_WINSOCK
	return 0;
}

