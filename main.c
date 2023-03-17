//adição de bibliotecas utilizados//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição da estrutura dos aplicativos//

struct ListaApp{
	char app[20];
	struct ListaApp * appProx;
};

typedef struct ListaApp lista;

//definição da estrutura das telas//

struct TelaApp{
	lista *apps;
	int contApp;
	struct TelaApp *telaProx;
	struct TelaApp *telaAnt;
};

typedef struct TelaApp tela;

//funcao para testar os endereços durante a criação do código//
void teste(tela * cabeca){
	lista *auxp;
	printf("entrou no teste");
	getchar();
	getchar();
	for(auxp = cabeca->apps; auxp != NULL; auxp = auxp->appProx){
		printf("entrou no teste2\n");
		puts(auxp->app);
		printf("auxp-%x \t auxp-prox-%x\n", auxp, auxp->appProx);
	}
	return;
}

//criação da função que inicia a primeira tela//

tela *iniciar(){
	tela * novo;
	novo = (tela *)malloc(sizeof(tela));
	novo->telaProx = NULL;
	novo->telaAnt = NULL;
	novo->contApp = 0;
	novo->apps = NULL;
	return novo;
}

//função para ler a ação do usuário//

int action(){
	int acao;	
	printf("\t\tQual acao deseja realizar? \n");
	printf("\t0 - Sair \n");
	printf("\t1 - Ver Apps \n");
	printf("\t2 - Instalar App \n");
	printf("\t3 - Excluir App \n");
	scanf("%d", &acao);
	system("cls");
	return acao;
}

//função para mostrar os apps na tela//

void mostrarApps(tela *cabeca){
	tela *aux;
	lista *auxp;
	aux = cabeca;
	if(aux->contApp==0){ //verifica quantidade de aplicativos inseridos na tela//
		printf("\t\tNao existem apps.\n");
		getchar();
		getchar();
		return;
	}else if(aux->telaProx == NULL){  //verifica a existência de apenas uma tela//
		auxp = aux->apps;
 	    for(int i = 0; auxp != NULL; i++){
 	    	puts(auxp->app);
 	    	auxp = auxp->appProx;
		 }
		 getchar();
		 getchar();
	}else{ // mostra todas as telas, desde a primeira até a última inserida, de acordo  com a opções do usuário//
		int chose;
		do{
			auxp = aux->apps;
			for(int i = 0; i < aux->contApp; i++){
 	    		puts(auxp->app);
 	    		auxp = auxp->appProx;
		 	}
			if(aux->telaProx != NULL){
				printf("\t\tOque deseja realizar?\n");
				printf("\t0 - sair.\n");
				printf("\t1 - ver pagina anterior.\n");
				printf("\t2 - ver proxima pagina.\n");
				scanf("%d", &chose);
				system("cls");
				switch(chose){
					case 0:
						return;
						break;
					case 1:
						if(aux->telaAnt == NULL){
							printf("\t\tImpossivel retornar.\n");
							getchar();
							getchar();
						}else{
							aux = aux->telaAnt;
						}
						break;
					case 2:
							aux = aux->telaProx;
						break;
				}
			}else{
				printf("\t\tOque deseja realizar?\n");
				printf("\t0 - sair.\n");
				printf("\t1 - ver pagina anterior.\n");
				printf("\t2 - ver proxima pagina.\n");
				scanf("%d", &chose);
				system("cls");
				switch(chose){
					case 0:
						return;
						break;
					case 1:
							aux = aux->telaAnt;
						break;
					case 2:
						if(aux->telaProx == NULL){
							printf("\t\tImpossivel avancar para proxima tela.\n");
							getchar();
							getchar();
						}else{
							aux = aux->telaProx;
						}
						break;
				}
			}
			system("cls");
		}while(chose != 0);
	}
}

//função que cria nova página caso seja necessário//

void novaPagina(tela *aux){
	tela *novo;
	lista *novoApp, *auxp;
	novo=(tela*)malloc(sizeof(tela));
	novoApp = (lista*)malloc(sizeof(lista));
	novo->telaAnt = aux;
	novo->telaProx = NULL;
	aux->telaProx = novo;
	novo->apps = novoApp;
	for(auxp = aux->apps; auxp->appProx != NULL; auxp = auxp->appProx){} //procura o último aplicativo para ajustar o novo último//
	auxp->appProx = novoApp;
	novoApp->appProx = NULL;
	novo->contApp = 0;
	printf("\t\tdeseja instalar qual app?\n");
	getchar();
	gets(novoApp->app);
	novo->contApp++;
	printf("\tapp instalado com sucesso!\n");
	getchar();
	return;
}

//função para instalar apps nas telas//

void instalarApp(tela *cabeca){
	tela *aux = NULL;
	lista *novoApp = NULL;
	lista *auxp = NULL;
	for(aux = cabeca; aux->telaProx != NULL; aux = aux->telaProx){} //procura a última tela para que o aplicativo seja adicionado nela//
	if(aux->contApp == 0){ // se não existirem apps na tela//
		printf("\t\tdeseja instalar qual app?\n");
		novoApp = (lista *)malloc(sizeof(lista));
		aux->apps = novoApp;
		novoApp->appProx = NULL;
		getchar();
		gets(novoApp->app);
		aux->contApp++;
		printf("\tapp instalado com sucesso!\n");
		getchar();
	}else if(aux->contApp < 3){ // se ja existirem apps na tela mas ela não está cheia//
		printf("\t\tdeseja instalar qual app?\n");
		novoApp = (lista *)malloc(sizeof(lista));
		for(auxp = aux->apps; auxp->appProx != NULL;auxp = auxp->appProx){}
		auxp->appProx = novoApp;
		novoApp->appProx = NULL;
		getchar();
		gets(novoApp->app);
		aux->contApp++;
		printf("\tapp instalado com sucesso!\n");
		getchar();
	}else{
		novaPagina(aux); // caso a tela esteja cheia cria uma nova tela//
	}	
	return;
}

//função que procura aplicativos//

lista * procuraApp(tela *cabeca){
	char excluido[20];
	int x;
	lista *auxp;
	printf("\t\tdeseja excluir qual app (ultilize os mesmos caracteteres usados no momento da instalacao)\n");
	getchar();
	gets(excluido);
	getchar();
	for(auxp = cabeca->apps; auxp != NULL; auxp = auxp->appProx){
			x = strcmp(excluido, auxp->app); //  compara a string a ser excluida e as existentes na lista//
			if(x == 0){
				return auxp;
			}
	}
}

//função para ajustar os apps//

void ajustarApp(lista *excluido, tela *cabeca){
	tela *aux, *aux2;
	lista *auxp;
	if(cabeca->apps == excluido){ //testa se o app a ser excluido é o primeiro da lista//
		if(excluido->appProx == NULL){ // teste a existência de um só app//
			cabeca->apps = NULL;
			free(excluido);
			cabeca->contApp = 0;
		}else{ //se existirem mais de um app //
			cabeca->apps = excluido->appProx;
			free(excluido);
		}
	}else{ // se o app a ser excluído não é o primeiro da lista//
		for(auxp = cabeca->apps; auxp != NULL; auxp = auxp->appProx){
			if(auxp->appProx == excluido){
				auxp->appProx = excluido->appProx;
				free(excluido);
			}
		}
	}
	if(cabeca->telaProx != NULL){ // testa a existência de uma tela ou mais//
		for(aux = cabeca; aux != NULL; aux = aux->telaProx){
			auxp = aux->apps;
			for(int i = 0; i <= 3; i++){
				if(i == 3){
					if(aux->telaProx == NULL){
						break;
					}else{
						aux2 = aux->telaProx; // ajusta a lista de aplicativos após a exclusão de algum deles, sendo o limite de 3 apps por tela//
						aux2->apps = auxp;
					}
				}else{
					if(auxp->appProx != NULL){
						auxp = auxp->appProx;
					}else{
						break;
					}	
				}
			}
		}	
	}
	if(cabeca->telaProx != NULL){ // testa a existência de uma tela ou mais//
		for(aux = cabeca; aux->telaProx != NULL; aux = aux->telaProx){}
		switch(aux->contApp){
			case 1:
				aux2 = aux->telaAnt;
				aux2->telaProx = NULL;
				free(aux); // caso tivesse um só app na tela e algum fosse excluído, esta tela seria liberada da memória//
				break;
			case 2:
				aux->contApp--; // ajusta a quantidade de apps na tela//
				break;
			case 3:
				aux->contApp--;
				break;
		}
	}
}

//função para exluir apps//

void excluir(lista *excluido, tela *cabeca){
	lista *auxp;
		for(auxp = cabeca->apps; auxp != NULL; auxp = auxp->appProx){
			if(auxp == excluido){
				ajustarApp(excluido, cabeca); //procura o endereço de memória do app a ser excluído//
			}
		}
}

//função main//

int main(){

	tela * cabeca;
	lista *excluido;
	cabeca = NULL;
	int acao;
	cabeca = iniciar();
	acao = action();
	do{
		switch(acao){
			case 0:
				return 0;
				break;
			case 1:
				 mostrarApps(cabeca);	
				 break;
			case 2:
				instalarApp(cabeca);
				break;
			case 3:
			excluido = procuraApp(cabeca);
			excluir(excluido, cabeca);
				break;
		}
		system("cls");
		acao = action();
	}while(acao != 0);
	return 0;
}
