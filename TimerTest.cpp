
#include "stdafx.h"
#include "TimerTest.h"
#include "windows.h"
#include "conio.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#include <string>


#include<WinSock2.h>
#include<WS2tcpip.h.>


#pragma comment(lib,"Ws2_32.lib")
#define PORT "1235"
#define BUFFERSIZE 512


#define No_of_Bytes 		3

using namespace std;

int test = 5, Adj_Value = 0, Adj_mode=1;
volatile int x_cor = 0, pos=0;

//String for getting the output from arduino
char output[No_of_Bytes];

//Portname must contain these backslashes
char *port_name = "\\\\.\\COM10";

//String for incoming data
char incomingData[No_of_Bytes];

SerialPort arduino(port_name);


void CTimerTest::OnTimedEvent1()
{
	int x, j,i=0, decimal;
	char  total[No_of_Bytes];
	char total_recv[No_of_Bytes] = { 0 };
	char arr[3];


	char total1[No_of_Bytes] = { 0, 2, 5 };
	char total2[No_of_Bytes] = { 0, 5, 0 };
	char total3[No_of_Bytes] = { 0, 2, 5 };
	char total4[No_of_Bytes] = { 0, 0, 0 };





	if (arduino.isConnected()) 
	{

			//printf("Connection Established\n");

			//Creating a c string
			char *c_string = new char[4];

			//if (!Adj_mode)
			//{

			printf("\r\nTimer  Called (count=%i)", timer1.GetCount());



			/*

			if (test % 4 == 0)
			{
				printf("\nPoistion 1: 025");
				c_string[0] = '0';
				c_string[1] = '2';
				c_string[2] = '5';

			}


			else if (timer1.GetCount() % 4 == 1)
			{
				printf("\nPoistion 2: 050");
				c_string[0] = '0';
				c_string[1] = '5';
				c_string[2] = '0';
			}


			else if (test % 4 == 2)
			{
				printf("\nPoistion 3: 025");
				c_string[0] = '0';
				c_string[1] = '2';
				c_string[2] = '5';
			}


			else if (test % 4 == 3)
			{
				printf("\nPoistion 4: 000");
				c_string[0] = '0';
				c_string[1] = '0';
				c_string[2] = '0';
			}	

			*/



			if (x_cor < 0)
				x_cor = 0;

			if (x_cor > 100)
				x_cor = 100;


				printf("\nx:%d        - ", x_cor);
				std::string s = std::to_string(x_cor);
				
				printf("String lenght: %d", s.length());
				

				
				if (s.length() == 1)
				{
					c_string[0] = '0' ;
					c_string[1] = '0';
					c_string[2] = s[0];
				}
				else  if (s.length() == 2)
				{
					c_string[0] = '0';
					c_string[1] = s[0];
					c_string[2] = s[1];
				}
				else if (s.length() == 3)
				{
					c_string[0] = s[0];
					c_string[1] = s[1];
					c_string[2] = s[2];
				}

				//Adding the delimiter
				c_string[3] = '\n';

			
				printf("CString: ");
			
				
			
				for (i = 0; i < 3; i++)
					printf("%c", c_string[i]);

				//std::cout << "length of string is " << strlen(c_string);
				std::cout << "\nSize of string is " << sizeof(c_string);
		//		printf("Total_Recv: ");

	//			for (j = 0; j < No_of_Bytes; j++)
	//			{
	//				printf("%c", total_recv[j]);
	//			}

				
				printf("\n End");

				//}

				
				switch (Adj_Value)
				{
				case 510:
					printf("\nPoistion Adj: 510");
					c_string[0] = '5';
					c_string[1] = '1';
					c_string[2] = '0';
					Adj_Value = 0;
					break;

				case 520:
					printf("\nPoistion Adj: 520");
					c_string[0] = '5';
					c_string[1] = '2';
					c_string[2] = '0';
					Adj_Value = 0;
					break;

				case 530:
					printf("\nPoistion Adj: 530");
					c_string[0] = '5';
					c_string[1] = '3';
					c_string[2] = '0';
					Adj_Value = 0;
					break;

				case 540:
					printf("\nPoistion Adj: 540");
					c_string[0] = '5';
					c_string[1] = '4';
					c_string[2] = '0';
					Adj_Value = 0;
					break;

				case 550:
					printf("\nPoistion Adj: 550");
					c_string[0] = '5';
					c_string[1] = '5';
					c_string[2] = '0';
					Adj_Value = 0;
					break;

				case 560:
					printf("\nPoistion Adj: 560");
					c_string[0] = '5';
					c_string[1] = '6';
					c_string[2] = '0';
					Adj_Value = 0;
					break;
				}
				
			
		//Getting reply from arduino
		//arduino.readSerialPort(total_recv, No_of_Bytes);

		//Writing string to arduino
		arduino.writeSerialPort(c_string, No_of_Bytes);


		//freeing c_string memory
		delete[] c_string;


		
	}
		else cout << "ERROR, check port name\n";

}

void CTimerTest::RunTest()
{
	
	timer1.SetTimedEvent(this, &CTimerTest::OnTimedEvent1);
	timer1.Start(1000); // Start timer 1 every 1s



	int input_key, Adjust_Mode_Status = 1;


	cout << "Does the Slider Need any adjustement?" << endl;

	input_key = _getch();
	if (input_key == 121)
	{
		cout << "Adjustment Mode ON" << endl;
		while (Adjust_Mode_Status)
		{
			input_key = _getch();
			cout << input_key << endl;
			switch (input_key)
			{
			case 27:						// ESC
				Adjust_Mode_Status = 0;
				break;

			case 4:							// CTRl+Right
				cout << "CR" << endl;
				Adj_Value = 510;
				break;

			case 1:							// CTRl+Left
				cout << "CL" << endl;
				Adj_Value = 520;
				break;

			case 100:						// Right
				cout << "R" << endl;
				Adj_Value = 530;
				break;

			case 97:						// Left
				cout << "L" << endl;
				Adj_Value = 540;
				break;

			case 68:						// Shift+Right
				cout << "SR" << endl;
				Adj_Value = 550;
				break;

			case 65:						// Shift+Left
				cout << "SL" << endl;
				Adj_Value = 560;
				break;



			}
		}
	}


	cout << "Adjustment Mode OFF" << endl;
	timer1.Stop();      // Stop timer 1
	Adj_mode = 0;


	timer1.SetTimedEvent(this, &CTimerTest::OnTimedEvent1);
	timer1.Start(1000); // Start timer 1 every 1s

	
	struct addrinfo *result = NULL, ref;
	WSADATA wsdata;
	WSAStartup(MAKEWORD(2, 2), &wsdata); // Intialization of Server
	// Setting up address
	ZeroMemory(&ref, sizeof(ref));
	ref.ai_family = AF_INET;
	ref.ai_socktype = SOCK_STREAM;
	ref.ai_protocol = IPPROTO_TCP;
	ref.ai_flags = AI_PASSIVE;
	getaddrinfo("127.78.67.34", PORT, &ref, &result);

	// Listen for the Client
	//init listening socket
	SOCKET lSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(lSocket, result->ai_addr, result->ai_addrlen);
	listen(lSocket, SOMAXCONN);

	//Setting up my client
	SOCKET CSocket;
	CSocket = accept(lSocket, NULL, NULL);

	int status;
	int count = 0;
	char revBuffer[BUFFERSIZE];
	int signZ = 0;
	int signX = 0;
	int signY = 0;
	int temp;
	int z = 0;
	int x = 0;
	int y = 0;
	int frame = 0;
	// 0    1   2  3   4 5678  9 10-11-12-13   14-15-16-17-18
	// S    N   P  N   Z 1111  X 1111          Y 
	int ddd = 0;

	while (1)
	{
		count++;
		memset(&revBuffer[0], 0, sizeof(revBuffer));
		status = recv(CSocket, revBuffer, BUFFERSIZE, 0);

		if (status > 0)
		{

			printf_s(revBuffer);


			z = ((revBuffer[5] - '0') * 1000 + (revBuffer[6] - '0') * 100 + (revBuffer[7] - '0') * 10 + (revBuffer[8] - '0') * 1) - 1000;
			x = ((revBuffer[10] - '0') * 1000 + (revBuffer[11] - '0') * 100 + (revBuffer[12] - '0') * 10 + (revBuffer[13] - '0') * 1) - 1000;
			y = ((revBuffer[15] - '0') * 1000 + (revBuffer[16] - '0') * 100 + (revBuffer[17] - '0') * 10 + (revBuffer[18] - '0') * 1) - 1000;

			if (revBuffer[1] == 'N')
			{
				z = z*-1;
			}
			if (revBuffer[2] == 'N')
			{
				x = x*-1;
			}
			if (revBuffer[3] == 'N')
			{
				y = y*-1;
			}

		
	
			pos = (int)y;

			if (pos >= 0 && pos < 10)
				x_cor = 0;
			else if (pos >= 10 && pos < 20)
				x_cor = 10;
			else if (pos >= 20 && pos < 30)
				x_cor = 20;
			else if (pos >= 30 && pos < 40)
				x_cor = 30;
			else if (pos >= 40 && pos < 50)
				x_cor = 40;
			else if (pos >= 50 && pos < 60)
				x_cor = 50;
			else if (pos >= 60 && pos < 70)
				x_cor = 60;
			else if (pos >= 70 && pos < 80)
				x_cor = 70;

			else if (pos >= 80 && pos < 90)
				x_cor = 0;
			else if (pos >= 90 && pos < 100)
				x_cor = 10;
			else if (pos >= 100 && pos < 110)
				x_cor = 20;
			else if (pos >= 110 && pos < 120)
				x_cor = 30;
			else if (pos >= 120 && pos < 130)
				x_cor = 40;
			else if (pos >= 130 && pos < 140)
				x_cor = 50;
			else if (pos >= 140 && pos < 150)
				x_cor = 60;


			std::cout << x;
			std::cout << "\n";


			//printf("Z=   %d   , X=    %d   , Y=    %d   \n", z, x, y);
			//frame++;
			//printf("Frame= %d", frame);
			/*
			for (int q = 0; q < 20; q++)
			{
			printf("Index = %d  ", q);
			printf("%c", revBuffer[q]);
			printf("\n");
			}
			*/
			//printf_s(revBuffer);


		}
		else
		{
			break;
			
		}


	}
	
	shutdown(CSocket, SD_SEND);
	closesocket(CSocket);
	WSACleanup;





//    getchar();          // Wait for return (stop)
//    timer1.Stop();      // Stop timer 1
}
