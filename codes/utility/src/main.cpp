/*
 * 测试utility中的函数
 */

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "utility.h"
#include "ProcessFork.h"
#include "StringTrans.h"
#include "Alarm.h"
#include "String.h"
#include "Clock.h"
#include "HeartBeat.h"
#include "Timer.h"
#include "Network.h"
#include "INetSocket.h"
#include "Partner.h"
#include "PartnerCallback.h"

using namespace utility;

int main(int argc, char* argv[])
{
	//CopyFile("main.c", "main.c.bak");
	//Execute("ps aux");
	
	//Test_ProcessFork();
	//Test_StringTrans();
	//Test_Alarm();
	//Test_String();
	//Test_Clock();
	//Test_HeartBeat();
	//Test_Timer();
	
	/*
	if (argc > 1 && strcmp(argv[1], "1") == 0)
		Test_Network_Server();
	else
		Test_Network_Client();
	*/

	/*
	if (argc > 1 && strcmp(argv[1], "1") == 0)
		Test_INetSocket_Server();
	else
		Test_INetSocket_Client();
	*/

    if (argc < 2) {
        printf("usage: %s [server|client]\n", argv[0]);
        exit(1);
    }
    else {
        Test_Partner(argv[1]);
    }

	exit(0);
}
