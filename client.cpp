#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	//윈속 초기화
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//소켓 생성
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//서버 설정 
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(1234);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	FILE* ofp = fopen("meat2.jpg", "wb");
	char Buffer[2049];
	while (1)
	{
		int recvLength = recv(ServerSocket, Buffer, 2048, 0);
		if (recvLength == 0) //close
		{
			break;
		}
		else
		{
			fwrite(Buffer, sizeof(char), recvLength, ofp);
		}
	}

	fclose(ofp);

	closesocket(ServerSocket);


	
	WSACleanup();

	return 0;
}