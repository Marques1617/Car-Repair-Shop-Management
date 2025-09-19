#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>  
#include "PPP.h"
#define TAM 100

int main(){
    tipoReserva* tipoRes = criaTipo();//cria da reserva lista com inicio e fim 
    tipoReserva* tipoPreRes = criaTipo();//cria da pre-reserva lista com inicio e fim 
    int option=0; 
    int id;

    //carregarFicheiro(tipoRes,"Reservas.txt");
    //carregarFicheiro(tipoPreRes,"Prereserva.txt");

    while(option != 7){
        printf("\n1-Adiciona reserva\n2-Cancelar reserva\n3-Cancelar Pre-reserva\n4-Listar reservas ordenadas\n5-Listar pre-Reservas ordenadas\n6-Listar reservas de cliente\n7-Listar Pre-reserva de cliente\n8-Realizar Reserva\n9-Gravar ficheiro\n10-Carregar Ficheiro\n11-Sair\n");
        printf("Opção: ");
        scanf("%d",&option);

        switch(option){
            case 1:{
                noReserva *novoNo = cria();//cria uma reserva
                noReserva *aux=cria();//cria um aux caso essa reserva esteja sobreposta noutra,assim passa para pre-reserva passando para aux
                int valido = adiciona(novoNo, tipoRes->inicio,aux); 
                  
                if(valido == -1){
                    break;
                } else if(valido == 0){
                    insere(tipoPreRes,aux);
                    printf("\nRealizada Pré-Reserva");
                    break;
                } else {
                    insere(tipoRes,novoNo);
                }

                break;
            }
            case 2:
                printf("Insira o id a eliminar: ");
                scanf("%d",&id);
                eliminar(tipoRes,id);
                verificaPreReservas(tipoPreRes,tipoRes);
                break;
            case 3:
                printf("Insira o id a eliminar: ");
                scanf("%d",&id);
                eliminar(tipoPreRes,id);
                break;
            case 4:
                printf("\nLISTA DE RESERVAS");
                imprimeOrdenado(tipoRes->inicio);
                break;
            case 5:
                printf("\n LISTA DE PRE RESERVAS");
                imprimeOrdenado(tipoPreRes->inicio);
                break;
            case 6:
               
                imprimeCliente(tipoRes->inicio);
                break;
            case 7:
                
                imprimeCliente(tipoPreRes->inicio);
                break;
            case 8:
                printf("Insira o id da tarefa a realizar: ");
                scanf("%d",&id);
                eliminar(tipoRes, id);
                verificaPreReservas(tipoPreRes, tipoRes);
                break;
            case 9:
                gravarFicheiro(tipoRes, "Reservas.txt");
                gravarFicheiro(tipoPreRes,"Prereserva.txt");
                break;
            case 10:
                carregarFicheiroReservas(tipoRes, tipoPreRes, "Reservas.txt");
                carregarFicheiroPreReservas(tipoPreRes,"Prereserva.txt");
                break;
            case 11:
                exit(0);
                break;
            default:
                printf("por favor introduza uma opçao valida");
                break;
        }

    }

    return 0;
}
