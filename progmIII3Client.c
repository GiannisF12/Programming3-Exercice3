#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>



int main(int argc, char *argv[])
{
	//Client Code
  char *ip,buffer[256];
  int port,status=1,sock,n;
  if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
  }
  port = atoi(argv[2]);
  ip = argv[1];

  struct sockaddr_in addr;
  socklen_t addr_size;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
  printf("\n\n============================================================================\n");
  status=1;
  	//Client Code
  	srand(time(NULL));
  while(1){
  	int tickets=0,flight=0,data=0;
	tickets = (rand() % (3 + 1 - 1)) + 1;
	write(sock,&tickets,sizeof(tickets));
	sleep(1);
	flight = rand() % 10;
	write(sock,&flight,sizeof(flight));
	sleep(1);
	read(sock,&data,sizeof(data));
	if(tickets==data){
		printf("Client: Success Reserves!!\n");
	}else if(data>0){
		printf("Client: Success Reserves:%d And Failed Reserves:%d.\n",data,tickets-data);
	}else{
		printf("Client: Failed Reserves.\n");
	}
	sleep(1);
	read(sock,&data,sizeof(data));
	printf("With Total Tickets Cost:%d\n",data);
	close(sock);
	break;
  }

  close(sock);
  printf("-----------------------------------------------------------\n");
  printf("Disconnected from the server.\n");

  return 0;

}
