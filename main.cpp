#include"stdio.h"
//This all mess for binary file reading
#include"stdlib.h"
#include"string.h"
//#include<C:\Dev-Cpp\MinGW32\include\sys\stat.h>
//#include"C:\Dev-Cpp\MinGW32\include\sys\types.h"
#include"fcntl.h"
//Mess ends here
#include"conio.h"
#include"WinSock.h"
void dostuff(SOCKET comm)
{
	char recvbuff[1024];
	char sendbuff[5000];
	int nret;
	//We have assumed that request may not be longer than 1024 bytes,For a full fledge server this may not be true.
	nret=recv(comm,recvbuff,1023,0);
	puts(recvbuff);
	//This is a handcoded response;Gonna fix it some day
	if(strstr(recvbuff,"favicon.ico")!=0){
		int inhandle;
		inhandle=open("favicon.png",O_RDONLY|O_BINARY);
		if(inhandle==-1)printf("what is happening to me?");
		int bytes;
		//Possible candidates for content type:-   image/ico unknown      image/png       image/bmp      image/x-icon
		strcpy(sendbuff,"HTTP/1.1 200 OK \r\nContent-Type: image/png; \r\nContent-Length:284 \r\nContent-Encoding: deflate\r\n\r\n ");
		int n=strlen("HTTP/1.1 200 OK \r\nContent-Type: image/png; \r\nContent-Length:284 \r\nContent-Encoding: deflate\r\n\r\n ");
		bytes=read(inhandle,sendbuff+n,5000);
		nret=send(comm,sendbuff,bytes+n,0);
		puts(sendbuff);
		return;
	}
	strcpy(sendbuff,"HTTP/1.1 200 OK \r\nContent-Type: text/html; charset=UTF-8 \r\nContent-Encoding: UTF-8\r\n\r\n Hello World!\r\n\r\n This is one simple website made by Mueez-ul-Haq. Wrote the whole darn server from scratch.\r\n");
	nret=send(comm,sendbuff,strlen(sendbuff),0);
	puts(sendbuff);
}
int main()
{
	WSADATA ws;
	int nret;
	//Initialise stuff
	WSAStartup(0x0101,&ws);
	SOCKET Listening;
	//Create a socket
	Listening=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(Listening==INVALID_SOCKET)return 1;
	SOCKADDR_IN serverinfo;
	//Fill in some info
	serverinfo.sin_family=AF_INET;
	serverinfo.sin_addr.s_addr=inet_addr("192.168.1.2");//The localhost,meaning the computer on which this program is running
	serverinfo.sin_port=htons(8002);//HTTP uses port 80,8000 or 8080. I am using port 8002 for no specific reason.
	//Tell the computer that this socket is a listening one
	nret=bind(Listening,(SOCKADDR*)&serverinfo,sizeof(serverinfo));
	if(nret==SOCKET_ERROR)return 2;
	while(1){
		//Listen on the socket,only one at a time,you can change it to multiple
		nret=listen(Listening,1);
		if(nret==SOCKET_ERROR)return 3;
		SOCKET comm;
		//Found one? accept it on another socket
		comm=accept(Listening,0,0);
		if(comm==INVALID_SOCKET)return 4;
		//DoStuff on the socket
		dostuff(comm);
		closesocket(comm);
	}
	closesocket(Listening);
	WSACleanup();
	getch();
	return 0;
}
