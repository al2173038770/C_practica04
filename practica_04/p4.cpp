#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
	char valor[10];
	struct nodo *izq;
	struct nodo *der;
	struct nodo *cen;
}Nodo;

Nodo* estadoA(char cad[]);
Nodo* estadoB(char cad[]);
Nodo* estadoC(char cad[]);

int main(){
	char stringAna[100];
	gets(stringAna);

	//scanf("%s",&stringAna);
	Nodo *arbol = estadoA(stringAna);
	
	return 0;
}

Nodo* estadoA(char cad[]){
	fflush(stdout);
	fflush(stdin);
	printf("\nEstado A: ");
	Nodo *nodo = (Nodo *) malloc (sizeof(Nodo *));

	int tamCad = strlen(cad);			//Medimos el tamaño de la cadena principal
	char cadEnv[20];

	char *tokenA,*tokenB;				
	tokenA=strtok(cad,"+");				//Obtemeos el token hasta el simbolo '+'
	
	int tamTokenA=strlen(tokenA);		//Medimos el tamaño de la cadena con token 

	if(tamCad==tamTokenA){				//Si son del mismo tamaño significa que no existe el signo '+'
		strcpy(nodo->valor,"<term>");	//Po lo tanto enviamos toda la cadena directamente a B
		nodo->der=NULL;
		nodo->cen=estadoB(cad);			
		nodo->izq=NULL;
	}
	else if(tamCad>tamTokenA){
		tokenB=strtok(NULL,"\0");		//Tomamos el siguiente token hasta fin de cadena
		strcpy(cadEnv,tokenA);
		nodo->izq = estadoA(cadEnv);	//Enviamos la parte izquierda de la cadena 
		
		strcpy(nodo->valor,"+");
		nodo->cen=NULL;

		strcpy(cadEnv,tokenB);
		nodo->der = estadoB(cadEnv);	//Enviamos la parte derecha
	}
	return nodo;
}

Nodo* estadoB(char cad[]){
	fflush(stdout);
	fflush(stdin);
	printf("\nEstado B: ");
	Nodo *nodo = (Nodo *) malloc (sizeof(Nodo *));

	int tamCad = strlen(cad);			//Medimos el tamaño de la cadena principal
	char cadEnv[20];

	char *tokenA,*tokenB;				
	tokenA=strtok(cad,"*");				//Obtemeos el token hasta el simbolo '+'
	
	int tamTokenA=strlen(tokenA);		//Medimos el tamaño de la cadena con token 

	if(tamCad==tamTokenA){				//Si son del mismo tamaño significa que no existe el signo '+'
		strcpy(nodo->valor,"<unit>");	//Po lo tanto enviamos toda la cadena directamente a B
		nodo->der=NULL;
		nodo->cen=estadoC(cad);			
		nodo->izq=NULL;
	}
	else if(tamCad>tamTokenA){
		tokenB=strtok(NULL,"\0");		//Tomamos el siguiente token hasta fin de cadena
		strcpy(cadEnv,tokenA);
		nodo->izq = estadoB(cadEnv);	//Enviamos la parte izquierda de la cadena 
		
		strcpy(nodo->valor,"*");
		nodo->cen=NULL;

		strcpy(cadEnv,tokenB);
		nodo->der = estadoC(cadEnv);	//Enviamos la parte derecha
	}
	return nodo;
}

Nodo* estadoC(char cad[]){	
	fflush(stdout);
	fflush(stdin);
	printf("\nEstado C: ");
	Nodo* nodo= (Nodo *) malloc (sizeof(Nodo *));
	
	if(cad[0]=='('){
		char cadEnv[100];
		Nodo* nodoD=  (Nodo *) malloc (sizeof(Nodo *));
		Nodo* nodoI=  (Nodo *) malloc (sizeof(Nodo *));
		
		nodoD->izq=nodoI->der=NULL;
		nodoD->cen=nodoI->der=NULL;
		nodoD->der=nodoI->der=NULL;
		strcpy(nodoI->valor,"(");
		strcpy(nodoD->valor,")");

		char *tokenP;					//Separamos la parte de adentro de los parentecis de la cadena

		tokenP=strtok(cad,"(");
		tokenP=strtok(tokenP,")");		
		
		nodo->izq = nodoI;
		nodo->der = nodoD;

		strcpy(nodo->valor,"<expr>");
		nodo->izq = NULL;			
		strcpy(cadEnv,tokenP);
		nodo->cen = estadoA(cadEnv);	//Envimos el contenido de vuelta al estado A
		nodo->der = NULL;
		 
	}else{
		nodo->cen=NULL;
		nodo->der=NULL;
		nodo->izq=NULL;
		strcpy(nodo->valor,cad);		//Agragamos la cadena
	}
	return nodo;
}
