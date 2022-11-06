#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoNo
{
    int valor;
    struct tipoNo *pai;
    struct tipoNo *esq, *dir;
}TNo;

TNo *raiz;

// Funcoes utilizadas
int menu();
TNo *inicializaArvore();

void inserirValor(TNo **raiz);
int max(int a, int b);
int alturaNO(TNo *nodo);
int fatorBalanceamento(TNo **nodo);
TNo *inserirArvore(TNo **raiz, int valor);
TNo *balancear(TNo **raiz);
TNo *criarNO(int valor);
TNo *inserirNO(TNo **nodo, int valor);

TNo *rotEsquerda(TNo **nodo);
TNo *rotDireitaEsquerda(TNo **nodo);
TNo *rotDireita(TNo **nodo);
TNo *rotEsquerdaDireita(TNo **nodo);

TNo *removerArvore(TNo **nodo, int *argumento);
void removerValor(TNo **raiz);

void buscarArvore(TNo *nodo, int argumento);
void buscarValor(TNo *raiz);

void caminhamento_pre_ordem(TNo *nodo);
void caminhamento_em_ordem(TNo *nodo, int nivel);
void caminhamento_pos_ordem(TNo *nodo);