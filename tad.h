#define MAXPILHA 100

struct TpPilha
{
	char PILHA[MAXPILHA];
	int TOPO;
};

void Inicializar(TpPilha &P);
void Inserir(TpPilha &P, char Elemento);
char Retirar(TpPilha &P);
char ElemenTopo(TpPilha P);
char Cheia(int TOPO);
char Vazia(int TOPO);
void Remover(TpPilha &P , char Elemento);

void Inicializar(TpPilha &P)
{
	P.TOPO = -1;
}

void Inserir(TpPilha &P, char Elemento)
{
	P.PILHA[++P.TOPO] = Elemento;
}

char Retirar(TpPilha &P)
{
	return P.PILHA[P.TOPO--];
}

char ElemenTopo(TpPilha P)
{
	return P.PILHA[P.TOPO];
}

char Cheia(int TOPO)
{
	return TOPO == MAXPILHA;
}

char Vazia(int TOPO)
{
	return TOPO == -1;
}

void Exibir(TpPilha P)
{
	
	while(!Vazia(P.TOPO)){
		printf("\n %c ",Retirar(P));
	}
}

void Remover(TpPilha &P , char Elemento)
{
	char Elemento2;
	TpPilha P2;
	Inicializar(P2);
	P2.TOPO=0;
	while(!Vazia(P.TOPO))
	{
		P2.PILHA[P2.TOPO] = P.PILHA[P.TOPO];
		P2.TOPO;
		P.TOPO--;
	}
	while(!Vazia(P.TOPO))
		Retirar(P);

	while(!Vazia(P2.TOPO)){
		Elemento2=Retirar(P2);
		if(Elemento2!=Elemento){
			Inserir(P,Elemento2);
		}
	}
		
}

//pilha float


