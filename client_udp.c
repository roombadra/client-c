#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int compare_string(char a[],char b[]){
	int c=0;
	while(a[c]==b[c]){
		if(a[c]=='\0' || b[c]=='\0')
			return 0;
		else{
			return -1;	
		}	
	}

}
int main(){
struct sockaddr_in serverAdd;
int clientSock;
int sortir=1;
char message[1024];//Message envoyé
socklen_t longueur;
char buffer[1024]; //Message Reçu
int nbreOctet;
//----------------- Creation Du Socket
if((clientSock=socket(PF_INET,SOCK_DGRAM,0))<0){

perror("Création du Socket Echouée");
exit(1);
}
//-------------------Fin Creation du Socket

//Parametrage du Socket
serverAdd.sin_family=AF_INET; // Famille d'adresse d'internet 
//serverAdd.sin_addr.s_addr=htonl(INADDR_ANY);//N'importe quelle interface de la station
serverAdd.sin_addr.s_addr=inet_addr("192.168.194.70");  
serverAdd.sin_port=htons(5010); //Port Local doit être identique au port server


while(1){

//----------------------Message Envoyé au Serveur
 printf("Entrez votre message:");
    fgets(message,1024,stdin);

nbreOctet=sendto(clientSock, message, strlen(message)+1, 0,(struct sockaddr *) &serverAdd,sizeof(serverAdd));

if(nbreOctet!=strlen(message)+1){
perror("send() a envoyé un nombre différent d'octet prévu");}

//----------------------Fin Message Envoyé au Serveur 


longueur=sizeof(struct sockaddr); 

//-----------------------Message Reçu du Serveur
nbreOctet=recvfrom(clientSock,buffer,1024,0,(struct sockaddr *)&serverAdd, &longueur); 
buffer[nbreOctet]='\0';
	
if(nbreOctet==-1){
perror("Erreur Serveur !");}

printf("Reponse du Serveur: %s \n",buffer);
//------------------------Fin Message Reçu du Serveur


}
close(clientSock);



}
