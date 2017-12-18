#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<unistd.h>

int main(int argc, char** argv){
	int s,p,Pf;
	char* ipv4;
	struct sockaddr_in addr;
	struct hostent* host;
	if(argc!=4){
		perror("Número incorrecto de argumentos\n");
		exit(1);
	}
	ipv4=argv[1];
	p=atoi(argv[2]);
	Pf=atoi(argv[3]);
	if(p>Pf){
		perror("Argumentos incorrectos\n");
		exit(1);
	}
	
	host=gethostbyname(argv[1]);
	if(host==NULL){
		perror("No se ha podido resolver el nombre");
		exit(1);
	}
	bzero((char*)&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	bcopy((char*)host->h_addr,(char*)&addr.sin_addr.s_addr,host->h_length);
	for(p;p<=Pf;p++){
		s=socket(AF_INET,SOCK_STREAM,0);	
		addr.sin_port=htons(p);
		if(connect(s,(struct sockaddr*)&addr,sizeof(addr))<0){
			printf("-- %d CERRADO\n",p);
		}else{
			printf("++ %d ABIERTO\n",p);
		}
		close(s);
	}
}
