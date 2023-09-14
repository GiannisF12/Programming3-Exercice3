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
    	for(;;){
    		int mul=0,div=0,rem=0,add=0,result=0,a,b,pl=0,i;
	    	read(client_sock,buffer,sizeof(buffer));
	    	for(i=0;i<256;i++){
	    		if(buffer[i]!='\0'){
	    			if(buffer[i]=='*'){
	    				mul++;
	    			}else if(buffer[i]=='/'){
	    				div++;
	    			}else if(buffer[i]=='+'){
	    				add++;
	    			}else if(buffer[i]=='-'){
	    				rem++;
	    			}
	    		}else{
	    			break;
	    		}
	    	}
	    	for(i=0;i<256;i++){
	    		pl++;
	    		if(buffer[i]=='\0' || buffer[i]=='*' || buffer[i]=='/' || buffer[i]=='+' || buffer[i]=='-'){
	    			break;
	    		}
	    	}
	    	a = atoi(buffer);
	    	for(i=0;i<256;i++){
	    		if(i>=pl){
	    			buffer[i-pl]=buffer[i];
	    		}
	    	}
	    	b = atoi(buffer);
	    	if(mul>0){
	    		result = a*b;
	    		write(client_sock,&result,sizeof(result));
	    	}else if(div>0){
	    		result = a/b;
	    		write(client_sock,&result,sizeof(result));
	    	}else if(add>0){
	    		result = a+b;
	    		write(client_sock,&result,sizeof(result));
	    	}else if(rem>0){
	    		result = a-b;
	    		write(client_sock,&result,sizeof(result));
	    	}
	    	
	    	sleep(2);
    	}
	close(client_sock);
     //4+10*7+3*100
  }

  return 0;
}
