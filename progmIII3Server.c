#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <unistd.h>  
#include <time.h>
#include <string.h>

struct flights{
    int  flight_id,from_city,to_city,TotalR;
    int available_seats,TotalSuccess,price;
};


int main(int argc, char *argv[])
{

	//Arxikopoihseis twn pthsewn
	int i,NumT,NumST,Income;
	srand(time(NULL) ^ (getpid()<<16));
    	struct flights flight[10];
    	for(i=0;i<10;i++){
        	flight[i].available_seats = (rand() % (5 + 1 - 1)) + 1;
        	flight[i].price = (rand() % (250 + 1 - 1)) + 1;
        	flight[i].flight_id=i;
        	flight[i].TotalSuccess = 0;
        	flight[i].TotalR=0;
        	flight[i].from_city = (rand() % (50 + 1 - 1)) + 1;
        	flight[i].to_city = (rand() % (50 + 1 - 1)) + 1;
    	}
    	
    	//SErver Code
  if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
  }
  char *ip = "127.0.0.1";
  int port;
  port = atoi(argv[1]);

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[256];
  int data;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

  listen(server_sock, 5);
  printf("Listening...\n");
	
//Infinte Loop Server
  while(1){
    	addr_size = sizeof(client_addr);
    	client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    	printf("\n\n\n\n\n\n===============================================================================\n");
    	printf("Client connected.\n");
    	int tickets=0,Flight=0,TicketCost=0;
    	for(;;){
	    	read(client_sock,&tickets,sizeof(data));
	    	read(client_sock,&Flight,sizeof(data));
	    	NumT+=tickets;
		flight[Flight].TotalR+=tickets;
		if(flight[Flight].available_seats>0){
		        if(flight[Flight].available_seats - tickets >=0){
		        	write(client_sock,&tickets,sizeof(tickets));
		        	NumST+=tickets;
		        	flight[Flight].TotalSuccess+=tickets;
				flight[Flight].available_seats -= tickets;
				TicketCost+=tickets*flight[Flight].price;
				Income+=TicketCost;
		        }else{
		        	write(client_sock,&flight[Flight].available_seats,sizeof(Flight));
				NumST+= flight[Flight].available_seats;
				TicketCost = flight[Flight].price* (flight[Flight].available_seats);
				Income+=TicketCost;
				flight[Flight].TotalSuccess += flight[Flight].available_seats;
				flight[Flight].available_seats =0;
			}
		}else{
			TicketCost=0;
		        int zero=0;
		        write(client_sock,&zero,sizeof(zero));
		}
		sleep(1);
		write(client_sock,&TicketCost,sizeof(TicketCost));
	    	printf("Client Disconnect\n");
	    	printf("------------------------------------------------------------------------\n");
	    	for(i=0;i<10;i++){
			printf("The Flight ID:%d From: %d To: %d Had %d TotalReserves\n",flight[i].flight_id,flight[i].from_city,flight[i].to_city,flight[i].TotalR);
			printf("With Successefull Reserves: %d And Rejected REserves: %d\n",flight[i].TotalSuccess,(flight[i].TotalR-flight[i].TotalSuccess));
		}
    		printf("Total Tickets : %d\n",NumT);
    		printf("Total Success Tickets : %d\n",NumST);
    		printf("Total Income : %d\n",Income);
	    	break;
    	}
	close(client_sock);

  }

  return 0;
}
