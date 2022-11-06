#include "lista.h"

int main(int argc, char *argv[]){
    
    int op, valor;

    do{
        op = menu();
        switch (op){

            case 0: break; // Sair

            case 1: inserirValor(&raiz); break; // Inserir novo valor

            case 2: removerValor(&raiz); break; // remover valor

            case 3: buscarValor(raiz); break; // Buscar valor

            case 4: caminhamento_pre_ordem(raiz); break; // Imprimir em PRE-ORDEM

            case 5: caminhamento_em_ordem(raiz, 1); break; // Imprimir em ORDEM

            case 6: caminhamento_pos_ordem(raiz); break; // Imprimir em POS-ORDEM

            default:
                printf("\n\n\tOPCAO INVALIDA. TENTE NOVAMENTE\n\n");
                break;
            
        } 

        printf("\n\n");
        system("pause");

    } while (op != 0);
    
    return 0;
}