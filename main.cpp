// Daniel ELias Fonseca Rumin RA:102113149
// Thales jorge da silva      RA:102012253
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio2.h>
#include <ctype.h>
#include "tad.h"
#define TF 27

struct TpCria{
	
	char var;
	float valor;
};

void Moldura(int CI, int LI, int CF, int LF, int corFrente, int corFundo)
{
	int i;
	textcolor(corFrente);
	textbackground(corFundo);
	textcolor(BLUE);
	gotoxy(CI,LI), printf("%c",201); //QUADRANTE SUPERIOR ESQUERDO = 201 = X1 Y1
	gotoxy(CF,LI), printf("%c",187); //QUADRANTE SUPERIOR DIREITA = 187 = X2 Y1
	gotoxy(CI,LF), printf("%c",200); //QUADRANTE INFERIOR ESQUERDO = 200 = X1 Y2
	gotoxy(CF,LF), printf("%c",188); //QUADRANTE INFERIOR DIREITA = 188 = X2 Y2
	
	//LINHA HORIZONTAL = 205
	for(i=CI+1; i<CF ; i++){
		gotoxy(i,LI), printf("%c",205);
		//Sleep(50);
		gotoxy(i,LF), printf("%c",205);
	}
	
	//LINHA VERTICAL = 186
	for(i=LI+1; i<LF ; i++){
		gotoxy(CI,i), printf("%c",186);
		//Sleep(50);
		gotoxy(CF,i), printf("%c",186);
	}
	textcolor(GREEN);
}

void formulario (void)
{
	
	Moldura(1,1,120,40,15,0);
	Moldura(2,2,119,4,15,0);
	gotoxy(55,3);
    textcolor(RED);
	printf("## MENU ##");
	Moldura(2,35,60,39,15,0);
	textcolor(YELLOW);
	gotoxy(64,36);
	printf("NOME: Daniel ELias Fonseca Rumin RA:102113149");
    gotoxy(64,37);
	printf("NOME: Thales jorge da silva      RA:102012253"); 
	Moldura(2,5,60,34,15,0);
	Moldura(61,5,119,34,15,0);	
	
}

void limpaArq(char Arq[])
{
	FILE *Ptr=fopen(Arq,"r");
		fclose(Ptr);
		FILE *PtrArq=fopen(Arq,"w");
	
	fclose(Ptr);
}

void verificaArq(char Arq1[],char Arq3[])
{
	FILE *PtrArq=fopen(Arq1,"r");
	FILE *PtrArq2=fopen(Arq3,"r");
	
	if(Arq1==NULL)
	{
		fclose(PtrArq);
		FILE *PtrArq=fopen(Arq1,"w");
	
	}
	if(Arq1==NULL)
	{
		fclose(PtrArq2);
		FILE *PtrArq2=fopen(Arq3,"w");	
	}
	fclose(PtrArq);
	fclose(PtrArq2);
}

void polon(TpPilha &p,char NomeArquivo3[])
{
		FILE *PtrArq2=fopen(NomeArquivo3,"a");
		char num;
		TpPilha p2;
		Inicializar(p2);
		int val=0,val2=0,soma=0,val3,val4;
		//rewind(PtrArq);  
		while(!Vazia(p.TOPO))
		{
			num=Retirar(p);
			//X = A * B + C / D
			//BJK*AD-C++=
			//40 (
			//41 )
			//42 *
			//43 +
			//45 -
			//47 /
			//61 =
			//65-90 A a Z
			//  = 1      + e - 2      * e / 3 
		
			//se for vatiavel coloca diretamente dentro do arquivo saida
			if(num>=65 && num <=90) //variaveis A a Z
            {
            	fprintf(PtrArq2,"%c",num);
            }
            else if(num!=32) //se for diferente de espaço 
			{
				if(num == 42 || num == 47) //  se *  /  insere na PILHA
				{
					Inserir(p2,num);
				}
				else
				{
					if(num==43 || num==45) // se + -  verifica se eh vazia ou se o topo eh diferente de = ou (
					{
						if(!Vazia(p2.TOPO) && p2.PILHA[p2.TOPO] != 61 && p2.PILHA[p2.TOPO] != 40)
						{
							fprintf(PtrArq2,"%c",Retirar(p2)); // coloca no arquivo saida e retira
						}
						Inserir(p2,num); // insere p + ou = na pilha 
					}
					else if(num == 40) // se ( insere na pilha
					{
						Inserir(p2,num);
					}
					else if(num == 41) // se ) insere na pilha 
					{
						Inserir(p2,num);
						while(p2.PILHA[p2.TOPO] != 40 && !Vazia(p2.TOPO)) // enquanto topo diferente de ( retira da pilha e coloca no arquivo saida
						{
							num=Retirar(p2);
							if(num!=40 && num != 41)
								fprintf(PtrArq2,"%c",num);
							else if(num==40 && num == 41) // se for ( ou ) retira da pilha 
								Retirar(p2);
						}	
					}
					else if(num == 61) // se = insere na pilha 
						Inserir(p2,num);
				}
				
			}
		}
		while(!Vazia(p2.TOPO))//caso tenha algo na pilha retira e coloca no arquivo de saida
		{
			num=Retirar(p2);
			if(num!=40)
				fprintf(PtrArq2,"%c",num);
		}	
		fprintf(PtrArq2,"\n");
					
    fclose(PtrArq2);
  
}

int Busca (TpCria v[TF], int TL,char elemento)
{
	int i=0;
	
	while(i<TL && elemento!=v[i].var)
		i++;
		
	if(i<TL)
		return i;
	else
		return -1;
}

void inverte (TpPilha &p, TpPilha &p2)
{
	while(!Vazia(p.TOPO) && !Cheia(p2.TOPO))
		Inserir(p2,Retirar(p)); 
	
}

void Operacao(TpCria v1[TF],int TL)
{
	FILE*Arq = fopen("saida.txt","r");
	TpPilha p;
	Inicializar(p);
	char aux[30],operador;
	float valor,aux1=0;
	int i,cont=0;
	
	fscanf(Arq,"%s",aux);
	while(!feof(Arq))
	{
		
		for(i=0;i<strlen(aux);i++)
		{
			if(aux[i] >=65 && aux[i] <=90)
			{
				if(!Cheia(p.TOPO))
					Inserir(p,aux[i]);    
			}	
			else
			
			if(aux[i]==42)
			{
				if(cont < 1)
					valor = v1[Busca(v1,TL,Retirar(p))].valor * v1[Busca(v1,TL,Retirar(p))].valor; 
					
				if(!Vazia(p.TOPO) && cont >= 1)
				{
					operador = Retirar(p);
					
					aux1 = v1[Busca(v1,TL,operador)].valor * valor;	
				}	
				cont++;
			}
			else
			
			if(aux[i]==43)
			{
				if(cont < 1)
					valor = v1[Busca(v1,TL,Retirar(p))].valor + v1[Busca(v1,TL,Retirar(p))].valor; 	
				if(!Vazia(p.TOPO) && cont >=1)
				{
					operador = Retirar(p);
					aux1 = 	v1[Busca(v1,TL,operador)].valor + valor;
					
				}	
				cont++;
			}
			else
			if(aux[i]==45)
			{
				if(cont < 1)
					valor = v1[Busca(v1,TL,Retirar(p))].valor - v1[Busca(v1,TL,Retirar(p))].valor; 	
				if(!Vazia(p.TOPO) && cont >=1)
				{
					operador = Retirar(p);
					aux1 = v1[Busca(v1,TL,operador)].valor - valor;
					
				}		
				cont++;
			}
			else
			if(aux[i]==47)
			{
				if(cont < 1)
					valor = v1[Busca(v1,TL,Retirar(p))].valor / v1[Busca(v1,TL,Retirar(p))].valor; 	
				if(!Vazia(p.TOPO) && cont >=1)
				{
					operador = Retirar(p);
				 	aux1 = 	v1[Busca(v1,TL,operador)].valor / valor;
					
				}		
				cont++;
			}
			else
			
			if(aux[i]==61)
			{
				if(!Vazia(p.TOPO) && aux1 ==0)
					v1[Busca(v1,TL,Retirar(p))].valor = valor;
				else
				{
					if(!Vazia(p.TOPO) && aux1 !=0)
						v1[Busca(v1,TL,Retirar(p))].valor = aux1;
					else
						v1[Busca(v1,TL,operador)].valor = aux1;
				}	
				cont=0;
			}			
		}
	
		fscanf(Arq,"%s",aux);
	}
	
	
	fclose(Arq);
}

void fc()
{
    formulario();
    gotoxy(4,7);
    printf("[A] - AUTOMATICO");
    gotoxy(4,9);	
    printf("[ESC] - Sair");
    gotoxy(4,37);
    printf("Digite a opcao desejada: ");
}

void comandos(TpPilha &p,char NomeArquivo[],char NomeArquivo3[],TpCria v1[TF], int &TL)
{
	FILE*Arq = fopen(NomeArquivo,"r");
	
	char aux[30];
	int i,k=0,pos,cont=0;
	float aux1,aux2,valor,a;
	char flag=1;
	char variavel,operador;
	TpPilha p2;
	//Inicializar(p);
	Inicializar(p2);
	rewind(Arq);

	
	while(!feof(Arq))
	{
		fscanf(Arq,"%s",aux);
		
		if(strstr(aux,"limpa") || 7+k>=31)
		{
			if(7+k>=31)
			{
				gotoxy(63,7+k);textcolor(RED);
				printf("Limite da tela atingido");
				k++;
				Sleep(500);
			}
			gotoxy(63,7+k);textcolor(RED);
			printf("Limpando Tela");textcolor(GREEN);
			Sleep(800);
			system("cls");
			k=0;
			formulario();
			fc();
			
			
		}
		else if(strstr(aux,"exibe") && !strstr(aux,"exibeln"))
		{
			
			for(i=0;i<strlen(aux);i++)
			{
				if(aux[i]==40)
					variavel = aux[i+1];
			}
			
			pos =Busca(v1,TL,variavel);
			
			if(pos!=-1)
			{
				Operacao(v1,TL);
				gotoxy(63,7+k);
				printf("Exibe: %c  valor: %.1f",v1[pos].var,v1[pos].valor);
				Sleep(600);
				k++;
			}
			
		}
		else if(strstr(aux,"exibeln"))
		{
			for(i=0;i<strlen(aux);i++)
			{
				if(aux[i]==40)
					variavel = aux[i+1];
			}
			
			pos = Busca(v1,TL,variavel);
			if(pos!=-1)
			{
				Operacao(v1,TL);
			
				gotoxy(63,7+k);
				printf("%c  valor: %.1f",v1[pos].var,v1[pos].valor);
				k=k+2;
				gotoxy(63,7+k);	
				
				Sleep(600);
			
			}
			
			
		}
		else
		{
			
			v1[TL].var = aux[0];
			for(i=0;i<strlen(aux) && flag ;i++)
			{
				if(aux[i]>=48 && aux[i]<= 57)
				{
					
					aux1 = aux[i]-48;

				}		
				
				if(aux[i]== 46) 
				{
					flag =0;
					aux2 = aux[i+1]-48;
				}
					
			}
			
			if(flag==0)
			{
				aux2 = aux2/10;
				v1[TL].valor =(float) aux1+aux2; 
				//printf("%c = %.1f\n",v1[TL].var,v1[TL].valor); 
				
			}
			else
			{
				v1[TL].var = aux[0];
				for(i=0;i<strlen(aux);i++)
				{
						Inserir(p,aux[i]);
						operador = aux[i];
						cont++;
				}
				if(!Vazia(p.TOPO))
				{
					inverte(p,p2);			
					polon(p2,NomeArquivo3);
				}
				
			}
			TL++;
			flag=1;
		}
	}
	
			fclose(Arq);
			gotoxy(63,7+k+1);
			textcolor(RED);
			printf("APERTE ALGUMA TECLA PARA CONTINUAR");textcolor(GREEN);
			getch();
			
	
			
}

char menu(void)
{
    system("cls");
    formulario();
    gotoxy(4,7);
    printf("[A] - AUTOMATICO");
    gotoxy(4,9);	
    printf("[ESC] - Sair");
    gotoxy(4,37);
    printf("Digite a opcao desejada: ");
    return toupper(getch());
}

int main (void)
{  
    TpPilha P;
    TpCria v1[TF];
    Inicializar(P);
    int TL=0;
    char op,Arq1[30],Arq3[30],aux[100];
    do
    {
        op = menu();
        
        switch(op)
        {	
        
            case 'A':
					strcpy(Arq1,"comandos.txt");
					strcpy(Arq3,"saida.txt");
					verificaArq(Arq1,Arq3);
					limpaArq(Arq3);
					comandos(P,Arq1,Arq3,v1,TL);
            	break;
        }

    }while(op!=27);
    return 0;
}


