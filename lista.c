#include "lista.h"

// Funcao de MENU
int menu(){
	int opcao;
	system("@cls||clear");
	printf("\n\t|=========== MENU ===========|\n\n");
	printf("0 - sair (Sair da aplicacao)\n");
	printf("1 - Inserir novo valor.\n");
	printf("2 - Remover Valor.\n");
	printf("3 - Buscar Valor.\n");
	printf("4 - Imprimir em PRE-ORDEM.\n");
	printf("5 - Imprimir EM-ORDEM.\n");
	printf("6 - Imprimir em POS-ORDEM. \n");
	printf("Escolha uma opcao: ");
	scanf("%d" ,&opcao);
	
	return opcao;
}

// ====================================================================

// Funcao para Inicializar a raiz da arvore
TNo *inicializaArvore(){

	//Inicializa a arvore retornado apenas null para a raiz
	return NULL;
}

// ====================================================================

void inserirValor(TNo **raiz)
{
	int valor;
	printf("\n\n\n");
    printf("\t=== | INSERIR USUARIO | ===\n\n");
    printf("Informe a valor: ");
    scanf("%d", &valor);

    inserirArvore(&(*raiz), valor); 
}

// Funcao usada para descobrir qual subarvore tem a maior altura
int max(int a, int b)
{
	if(a > b){

		return a;
	}

	return b;
}

// Funcao usada para descobrir a altura de um NO
int alturaNO(TNo *raiz) 
{
	if(raiz == NULL){
		// O retorno eh 1 porque caso o Nodo nao possua filho na direita e esquerda, ele entrara no else e a altura retornada sera zero
		return -1;
	}

	// Contar a quantidade de ligacoes entre os Nodos tanto na esquerda quanto na direita
	// Como eh recursiva, ela percorre cada Nodo conferindo quais tem filhos a direita e esquerda
	int esq = alturaNO(raiz->esq); 
	int dir = alturaNO(raiz->dir); 

	if (esq > dir){
		return esq += 1;
	} else {
		return dir += 1; 
	}
	
}

int fatorBalanceamento(TNo **nodo)
{
	// Retorna a diferenca entre a altura da direita e da esquerda. Essa resultado sera utilizado para balancear a arvore.
	return alturaNO((*nodo)->dir) - alturaNO((*nodo)->esq);
}

TNo *inserirArvore(TNo **raiz, int valor)
{
	int altura = 0;

	if ((*raiz) == NULL){ // Conferi se a arvore ja possui uma raiz

		// Se a arvore estiver vazia, insere o valor na raiz da arvore
		(*raiz) = inserirNO(&(*raiz), valor);
	} else {

		// Insere o valor na sua respectiva posicao na arvore
		inserirNO(&(*raiz), valor);
	}

	// Apos calcular a altura do Nodo a esquerda e direita, os valores sao passados como parametros para descobrir qual a maior altura
	// A esse resultado eh somado 1 e, assim, eh obtido a altura
	altura = max(alturaNO((*raiz)->esq), alturaNO((*raiz)->dir)) + 1;

	// A raiz da arvore e passada como parametro para caso haja necessidade, a arvore seja balanceada
	// Apos o balanceamento, eh retornado a nova (ou nao) raiz da arvore.
	(*raiz) = balancear(&(*raiz));

	return (*raiz);

}

// Funcao para balancear a arvore
TNo *balancear(TNo **raiz)
{

	// Se a diferenca da altura da direita com a da esquerda for maior que 1, significa que o lado direito possui altura maior que a esquerda
	if (fatorBalanceamento(&(*raiz)) > 1){

		// Eh feito um calculo para descobrir se o Nodo a direita possui filhos e se tiver, calcular a diferenca de altura entre os dois
		if (fatorBalanceamento(&(*raiz)->dir) >= 0){

			// Se nao tiver filhos ou tiver filho a direita, ira ocorrer uma rotacao para a ESQUERDA
			(*raiz) = rotEsquerda(&(*raiz));
		} else {

			// Se tiver filhos na esquerda, ocorre uma rotacao para DIREITA ESQUERDA
			(*raiz) = rotDireitaEsquerda(&(*raiz));
		}
	}  
	
	// Se a diferenca de altura da direita com a da esquerda for menor que -1, significa que o lado esquerdo possui altura maior que o direito
	if (fatorBalanceamento(&(*raiz)) < -1){

		// Eh feito um calculo para descobrir se o Nodo a esquerda possui filhos e se tiver, calcular a diferenca da altura entre os dois
		if (fatorBalanceamento(&(*raiz)->esq) <= 0){

			// Se nao tiver filhos ou tiver filho a esquerda, ira ocorrer uma rotacao para a DIREITA
			(*raiz) = rotDireita(&(*raiz));
		} else {

			// Se tiver filhos na direita, ocorre uma rotacao ESQUERDA DIREITA
			(*raiz) = rotEsquerdaDireita(&(*raiz));
		}
	}

	// Retorna a RAIZ da arvore
	return (*raiz);

}

TNo *criarNO(int valor)
{
	// Sera inserido as informacoes do Nodo (NO)
	TNo *novo = (TNo *)malloc(sizeof(TNo)); // Alocar um novo espaco na memoria para o valor ser inserido na arvore
	novo->valor = valor;
	novo->esq = NULL; // Defini o lado esquerdo do Nodo como NULL, ou seja, podera ser inserido filhos
	novo->dir = NULL; // Defini o lado direito do Nodo como NULL, ou seja, podera ser inserido filhos
	return novo; // Retorna o Nodo com suas informacoes
}

TNo *inserirNO(TNo **nodo, int valor)
{

	if ((*nodo) == NULL){ 

		// Cria um No para o elemento na arvore contento a valor
		return criarNO(valor);

	} else if (valor < (*nodo)->valor){  

		// Se o valor for menor que o do Nodo atual da arvore chama a funcao novamente passando o Nodo da esquerda
		// como parametro. Ou seja, a arvore ira percorrer a esquerda
		(*nodo)->esq = inserirNO(&(*nodo)->esq, valor);

	} else {
		// Se o valor for maior que o do Nodo atual da arvore chama a funcao novamente passando o Nodo da direita
		// como parametro. Ou seja, a arvore ira percorrer a direita
		(*nodo)->dir = inserirNO(&(*nodo)->dir, valor);

	}

	return (*nodo);

}

// ====================================================================

// Rotacao a DIREITA
TNo *rotDireita(TNo **nodo){

	// o X sera a nova raiz.
	TNo *x = (*nodo)->esq;
	// O valor na direita do X passa para o lado Esquerdo da "antiga" raiz
	(*nodo)->esq = x->dir;
	// A raiz "anterior", passa para a direta do X
	x->dir = (*nodo);
	return x;

}

// Rotacao a ESQUERDA
TNo *rotEsquerda(TNo **nodo){
	
	// o X sera a nova raiz
	TNo *x = (*nodo)->dir;
	// O valor na esquerda do X passa para o lado direito da "antiga" raiz
	(*nodo)->dir = x->esq;
	// A raiz "anterior", passa para a esquerda do X
	x->esq = (*nodo);
	return x;
	
}

// Rotacao DIREITA ESQUERDA
TNo *rotEsquerdaDireita(TNo **nodo){

	// Primeiro eh feito uma rotacao para a esquerda no Nodo esquerdo da raiz
	(*nodo)->esq = rotEsquerda(&(*nodo)->esq);
	// Realiza a rotacao a DIREITA
	return rotDireita(&(*nodo));

}

// Rotacao ESQUERDA DIREITA
TNo *rotDireitaEsquerda(TNo **nodo){

	// Primeiro eh feito uma rotacao para a direita no Nodo direito da raiz
	(*nodo)->dir = rotDireita(&(*nodo)->dir);
	// Realiza a rotacao a ESQUERDA
	return rotEsquerda(&(*nodo));

}


// ====================================================================

TNo *removerArvore(TNo **nodo, int *argumento)
{
	int altura;
	// Se encontrar NULL, significa que o valor nao consta na arvore ou que a arvore esta vazia
	if ((*nodo) == NULL){ 
		printf("\n\n\tELEMENTO NAO ENCONTRADO\n\n");
		return NULL;

	} else if ((*nodo)->valor > *argumento){

		// Se o valor procurado for menor que o valor do Nodo atual, desce pela ESQUERDA
		(*nodo)->esq = removerArvore(&(*nodo)->esq, argumento);

	} else if ((*nodo)->valor < *argumento){

		// Se o valor procurado for maior que o valor do Nodo atual, desce pela DIREITA
		(*nodo)->dir = removerArvore(&(*nodo)->dir, argumento);

	} else {

		// Encontrou o Nodo que sera removido
		if ((*nodo)->dir == NULL && (*nodo)->esq == NULL){

			// Nodo que sera removido nao tem filhos
			free((*nodo)); // Libera o espaco que o elemento estava ocupando na memoria
			(*nodo) = NULL; // Atribui NULL ao Nodo

		} else if ((*nodo)->esq == NULL){

			// Nodo que sera removido tem apenas filho a direita
			TNo *temporario = (*nodo);
			(*nodo) = (*nodo)->dir; // O Nodo da direita volta atras uma posicao
			free(temporario); // O Nodo achado eh excluido e seu espaco na memoria liberado

		} else if ((*nodo)->dir == NULL){

			// Nodo que sera removido tem apenas filho a esquerda
			TNo *temporario = (*nodo);
			(*nodo) = (*nodo)->esq; // O Nodo da esquerda volta atras uma posicao 
			free(temporario); // O Nodo achado eh excluido e seu espao na memoria liberado

		} else {

			// Nodo possui dois filhos
			TNo *prov = (*nodo)->esq; // Criacao de um provisorio que recebe o Nodo da esquerda
			while (prov->dir != NULL){ // Percorre os Nodo da direita ate for igual a NULL
				prov = prov->dir;
			}

			// Trocando os valores entre os Nodos
			(*nodo)->valor = prov->valor; // O Nodo que sera excluido recebe o valor provisorio
			prov->valor = *argumento; // O valor do Nodo e atualizado
			(*nodo)->esq = removerArvore(&(*nodo)->esq, argumento);

		}
	}

	return (*nodo);

}

void removerValor(TNo **raiz)
{

	int altura, valor;

	printf("\n\n\n");
    printf("\t=== | REMOVER USUARIO | ===\n\n");
    printf("Informe a valor: ");
    scanf("%d", &valor);

	removerArvore(&(*raiz), &valor);

	altura = max(alturaNO((*raiz)->esq), alturaNO((*raiz)->dir)) + 1;

	(*raiz) = balancear(&(*raiz));
}

// ====================================================================

void buscarValor(TNo *raiz)
{
	int valor;

	printf("\n\n\n");
    printf("\t=== | BUSCAR USUARIO | ===\n\n");
    printf("Informe a valor: ");
    scanf("%d", &valor);

    buscarArvore(raiz, valor); 
}

void buscarArvore(TNo *nodo, int argumento)
{

	// Se o NO encontrado for NULL significa o valor nao foi encontrado
	if (nodo == NULL){
		printf("\n\n\n\tVALOR NAO ENCONTRADO\n\n");

	} else if (nodo->valor == argumento) {
		// Quando encontrar e valor, mostrar ele no prompt
		printf("\n\t%d\n", argumento);

	} else if (nodo->valor > argumento){
		// Se o valor do NO atual for maior que o valor buscado, desce o NO pela esquerda e chama a funcao de 
		// busca novamente
		buscarArvore(nodo->esq, argumento);

	} else {
		// Se o valor do NO atual for menor que o valor buscado, desce o NO pela direira e chama a funcao de busca
		// novamente
		buscarArvore(nodo->dir, argumento);

	}
}

// ====================================================================

void caminhamento_em_ordem(TNo *nodo, int nivel)
{
	// Mostrar no terminal os os valores em sua respectiva posicao na arvore
	int i;
	if (nodo != NULL){
		// Percorre a arvore pela esquerda de forma simetrica, ou seja, do menor valor para o maior
		caminhamento_em_ordem(nodo->dir, nivel + 1);
		// Mostrar no prompt o valor do NO da arvore
		printf("\n\n");
		for(i = 0; i < nivel; i++){
			printf("\t");
		}
		printf("%d", nodo->valor);
		// Percorre a arvore pela direita de forma simetrica, ou seja, do menor valor para o maior
		caminhamento_em_ordem(nodo->esq, nivel + 1);
	}
}

// ====================================================================

void caminhamento_pre_ordem(TNo *nodo)
{
	// A raiz sempre eh a primeira a ser mostrada na arvore
	if (nodo != NULL)
	{
		// Mostrar no prompt o valor do NO da arvore
		printf("\n\t%d\n",nodo->valor);
		// Percorre a arvore pela esquerda 
		caminhamento_pre_ordem(nodo->esq);
		// Percorre a arvore pela direita 
		caminhamento_pre_ordem(nodo->dir);
	}
}

// ====================================================================

void caminhamento_pos_ordem(TNo *nodo)
{
	// A raiz sempre eh mostrada por ultimo na arvore
	if (nodo != NULL)
	{	
		// Percorre a arvore pela esquerda 
		caminhamento_pos_ordem(nodo->esq);
		// Percorre a arvore pela direita 
		caminhamento_pos_ordem(nodo->dir);
		// Mostrar no prompt o valor do NO da arvore
		printf("\n\t%d\n",nodo->valor);
	}
}

