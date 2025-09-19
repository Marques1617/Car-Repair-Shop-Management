#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "PPP.h"
#define MAX_LINE_LENGTH 1000

//Cria o Tipo em memória
tipoReserva *criaTipo(void){
    tipoReserva *aux;
    aux = (tipoReserva *)malloc(sizeof(tipoReserva));
    aux->inicio = NULL;
    aux->fim = NULL;

    return aux;
}

//Cria um nó em memória e inicializa as suas propriedades
noReserva *cria(void){
    noReserva *aux;
    aux=(noReserva *)malloc(sizeof(noReserva));
    if(aux !=NULL){
        aux->reserva.id=0;
        aux->reserva.dia=0;
        aux->reserva.mes=0;
        aux->reserva.ano=0;
        aux->reserva.horaInicial=0;
        aux->reserva.minutoInicial=0;
        aux->reserva.horaFinal=0;
        aux->reserva.minutoFinal=0;
        aux->reserva.tipo=0;

        aux->prox=NULL;
    }
    return aux;
}

void imprime(noReserva *no){
        printf("\n\nID:%d", no->reserva.id);
        printf("\nNome:%s", no->reserva.nome);
        printf("\nHoras:%d:%02d", no->reserva.horaInicial, no->reserva.minutoInicial);
        printf("\nData:%d/%d/%d", no->reserva.dia, no->reserva.mes, no->reserva.ano);
        if(no->reserva.tipo==0){
            printf("\nTipo Lavagem");
        }else{
            printf("\nTipo Manutenção");
        }
}

void imprimeOrdenado(noReserva *no){
    noReserva *aux = no;

    while(aux != NULL){ 
        imprime(aux);
        aux=aux->prox;
    }
}

void imprimeCliente(noReserva *no){
    printf("Insira o nome do cliente: ");
    char nome[100];
    scanf("%s",nome);
    printf("%s",nome);
    noReserva *aux = no;
    while(aux != NULL){ 
        if(strcmp(nome, aux->reserva.nome) == 0){
            imprime(aux);
        }
        
        aux=aux->prox;
    }
}

int verificaHorario(noReserva *novoNo){
    if(novoNo->reserva.horaInicial < 8){
        printf("Hora Inválida!\n");
        return -1;
    }

    if(novoNo->reserva.horaInicial>=18){//NOVO
        printf("Hora Inválida\n");
        return -1;
    }

    if(novoNo->reserva.horaInicial == 17 && novoNo->reserva.minutoInicial > 30){
        printf("Hora Inválida!\n");
        return -1;
    }

    if(novoNo->reserva.horaInicial == 17 && novoNo->reserva.minutoInicial > 0  && novoNo->reserva.tipo==1){
        printf("Hora Inválida!\n");
        return -1;
    }

    return 0;
}

int verificaMes(noReserva *novoNo){
    if(novoNo->reserva.ano>=1900 && novoNo->reserva.ano<=9999)
    {
        if(novoNo->reserva.mes>=1 && novoNo->reserva.mes<=12)
        {
            if((novoNo->reserva.dia>=1 && novoNo->reserva.dia<=31) && (novoNo->reserva.mes==1 || novoNo->reserva.mes==3 || novoNo->reserva.mes==5 || novoNo->reserva.mes==7 || novoNo->reserva.mes==8 || novoNo->reserva.mes==10 || novoNo->reserva.mes==12)){
                printf("Data é valida\n");
            }
            else if((novoNo->reserva.dia>=1 && novoNo->reserva.dia<=30) && (novoNo->reserva.mes==4 || novoNo->reserva.mes==6 || novoNo->reserva.mes==9 || novoNo->reserva.mes==11)){
                printf("Data é valida..\n");
            }
            else if((novoNo->reserva.dia>=1 && novoNo->reserva.dia<=28) && (novoNo->reserva.mes==2)){
                printf("Data é valida.\n");
            }
            else if(novoNo->reserva.dia==29 && novoNo->reserva.mes==2 && (novoNo->reserva.ano%400==0 ||(novoNo->reserva.ano%4==0 && novoNo->reserva.ano%100!=0))){
                printf("Data é valida.\n");
            }
            else{
                printf("Data é invalida.\n");
                return -1;
            }
        }
        else
        {
            printf("Mês inválido.\n");
            return -1;
        }
    }
    else
    {
        printf("Ano inválido");
        return -1;
    }
 
    return 0;    
}

int verificaSobreposicao(noReserva *no, noReserva *noinicial){///if (no->reserva.mes== aux ->reserva.mes && no->reserva.ano==aux ->reserva.ano && no->reserva.dia && aux->reserva.dia)
    //aquele if serve para ver se há sobreposiçao , ouseja têm que ter mesmo dia mesmo mes e mesmo ano
    noReserva *aux=noinicial;
    int minutosiniciais = no->reserva.horaInicial*60 + no->reserva.minutoInicial;//conversao para minutos
    int minutosfinais = no->reserva.horaFinal*60 + no->reserva.minutoFinal;//conversao para minutos
   
    while(aux != NULL){
        if(no->reserva.ano != aux->reserva.ano || no->reserva.mes != aux->reserva.mes || no->reserva.dia != aux->reserva.dia){
            aux=aux->prox;
            continue;
        }

        int auxMinutosiniciais = aux->reserva.horaInicial*60 + aux->reserva.minutoInicial;
        int auxMinutosfinais = aux->reserva.horaFinal*60 + aux->reserva.minutoFinal;

        if((minutosfinais > auxMinutosiniciais && minutosfinais < auxMinutosfinais) 
            || (minutosiniciais > auxMinutosiniciais && minutosiniciais < auxMinutosfinais) 
            || (minutosiniciais < auxMinutosiniciais && minutosfinais > auxMinutosfinais)
            || (minutosiniciais > auxMinutosiniciais && minutosfinais < auxMinutosfinais)
            || (minutosiniciais == auxMinutosiniciais)//NOVO
            || (minutosfinais == auxMinutosfinais)){//NOVO

            return -1;
        }

        aux=aux->prox;
    }

    return 0;
}

int adiciona(noReserva *no,noReserva *noinicial,noReserva *aux){   
    printf("Nome: ");
    scanf("%s", no->reserva.nome);

    printf("Introduza a data no formato (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &no->reserva.dia, &no->reserva.mes, &no->reserva.ano);

    if(verificaMes(no) == -1){
        free(no);
        return -1;
    }

    printf("\nIntroduza as horas no formato (HH:MM): ");
    scanf("%d:%d", &no->reserva.horaInicial, &no->reserva.minutoInicial);

    if(verificaHorario(no) == -1){
        free(no);
        return -1;
    }

    int opcao;
    printf("1:Lavagem / 2:Manutenção ");
    scanf("%d", &opcao);

    if(opcao == 1){
        int minutosfinais = no->reserva.minutoInicial + 30;
        int horasfinais = no->reserva.horaInicial;

        if(minutosfinais >= 60){
            minutosfinais = minutosfinais-60;
            horasfinais++;
        }

        no->reserva.tipo = 0;//lavagem
        no->reserva.minutoFinal = minutosfinais;
        no->reserva.horaFinal = horasfinais;
    }else{
        no->reserva.tipo = 1;//manutençao
        no->reserva.minutoFinal = no->reserva.minutoInicial;
        no->reserva.horaFinal = no->reserva.horaInicial + 1;
    }

    if(noinicial != NULL && verificaSobreposicao(no, noinicial) == -1){
        *aux=*no;
        free(no);

        return 0;
    }

    return 1;
}

void eliminar(tipoReserva *tipoRes,int id){
    if(tipoRes->inicio == NULL){
        printf("\nNão existe uma lista deste tipo!");
        return;
    }

    noReserva *aux=tipoRes->inicio;

    if(tipoRes->inicio->reserva.id == id){
        tipoRes->inicio=tipoRes->inicio->prox;

        if(tipoRes->inicio==NULL){
            tipoRes=criaTipo();
        } 

        printf("\nEliminação com sucesso!");
        return;
    }

    noReserva *anterior=aux;

    while(aux != NULL){ 
        if(id == aux->reserva.id){
            if(id==tipoRes->fim->reserva.id){
                tipoRes->fim=anterior;
            }
            
            anterior->prox=aux->prox;
            printf("Eliminação com sucesso!");
            return;
        }

        anterior=aux;
        aux=aux->prox;
    }
}

int obtemMaiorId(tipoReserva *tipoRes){
    int id=0;
    if(tipoRes->inicio == NULL){
        return id;
    }
    noReserva *aux=tipoRes->inicio;

    while(aux !=NULL){
        if(aux->reserva.id > id){
            id=aux->reserva.id;
        }

        aux=aux->prox;
    }

    id++;

    return id;
}

void insere(tipoReserva *tipoRes, noReserva *novoNo){
    if(tipoRes->inicio == NULL){
        novoNo->prox = NULL;
        tipoRes->inicio = novoNo;
        tipoRes->fim = novoNo;
        return;
    }

    noReserva *aux = tipoRes->inicio;
    noReserva *anterior = aux;

    while(aux != NULL){
        if((novoNo->reserva.ano < aux->reserva.ano) 
        || (novoNo->reserva.ano == aux->reserva.ano && novoNo->reserva.mes < aux->reserva.mes) 
        || (novoNo->reserva.ano == aux->reserva.ano && novoNo->reserva.mes == aux->reserva.mes && novoNo->reserva.dia < aux->reserva.dia)
        || (novoNo->reserva.ano == aux->reserva.ano && novoNo->reserva.mes == aux->reserva.mes && novoNo->reserva.dia == aux->reserva.dia && novoNo->reserva.horaInicial < aux->reserva.horaInicial)
        || (novoNo->reserva.ano == aux->reserva.ano && novoNo->reserva.mes == aux->reserva.mes && novoNo->reserva.dia == aux->reserva.dia && novoNo->reserva.horaInicial == aux->reserva.horaInicial && novoNo->reserva.minutoInicial < aux->reserva.minutoInicial)){

            novoNo->reserva.id=obtemMaiorId(tipoRes);
            
            if(aux == tipoRes->inicio){
                tipoRes->inicio=novoNo;
                novoNo->prox=aux;
                break;
            }

            anterior->prox = novoNo;
            novoNo->prox = aux;

            break;
        }

        if(aux->prox == NULL){
            novoNo->reserva.id = obtemMaiorId(tipoRes);
            aux->prox=novoNo;
            tipoRes->fim=novoNo;

            break;
        }

        anterior=aux;
        aux=aux->prox;
    }
}

void verificaPreReservas(tipoReserva *tipoPreRes, tipoReserva *tipoRes){
    noReserva *auxPreRes=tipoPreRes->inicio;

    while(auxPreRes != NULL){
        int verifica = verificaSobreposicao(auxPreRes, tipoRes->inicio);

        if(verifica == 0){
            eliminar(tipoPreRes, auxPreRes->reserva.id);
            insere(tipoRes, auxPreRes);
            auxPreRes = tipoPreRes->inicio;
        }else{
            auxPreRes=auxPreRes->prox;
        }
    }
}

void gravarFicheiro(tipoReserva *tipoRes,char nomeficheiro[]){
    FILE *fptr = fopen(nomeficheiro, "w+");
    noReserva *aux=tipoRes->inicio;

    while(aux != NULL){
        fprintf(fptr, "%s;%d;%d;%02d;%02d;%d;%d;%d;%d\n", 
                aux->reserva.nome,
                aux->reserva.horaInicial,
                aux->reserva.horaFinal, 
                aux->reserva.minutoInicial,
                aux->reserva.minutoFinal,
                aux->reserva.dia,
                aux->reserva.mes,
                aux->reserva.ano,
                aux->reserva.tipo);

        aux=aux->prox;
    }

    fclose(fptr);
}

noReserva *carregaReserva(char line[]){
    noReserva *aux=cria();
    char *token = strtok(line, ";");

    strcpy(aux->reserva.nome, token);
    aux->reserva.horaInicial = atoi(strtok(NULL, ";"));
    aux->reserva.horaFinal = atoi(strtok(NULL, ";"));
    aux->reserva.minutoInicial = atoi(strtok(NULL, ";"));
    aux->reserva.minutoFinal = atoi(strtok(NULL, ";"));
    aux->reserva.dia = atoi(strtok(NULL, ";"));
    aux->reserva.mes = atoi(strtok(NULL, ";"));
    aux->reserva.ano = atoi(strtok(NULL, ";"));
    aux->reserva.tipo = atoi(strtok(NULL, ";"));

    return aux;
}

void carregarFicheiroReservas(tipoReserva *tipoRes,tipoReserva *tipoPreRes, char nomeficheiro[]){
    char line[MAX_LINE_LENGTH];
    FILE *fp = fopen(nomeficheiro, "a+");
    
    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){
        noReserva* aux=carregaReserva(line);

        if(verificaSobreposicao(aux,tipoRes->inicio) == 0){
            insere(tipoRes, aux);
        }else{
            insere(tipoPreRes,aux);
        }
    }

    fclose(fp);
}

void carregarFicheiroPreReservas(tipoReserva *tipoPreRes, char nomeficheiro[]){
    char line[MAX_LINE_LENGTH];
    FILE *fp = fopen(nomeficheiro, "a+");
    
    while(fgets(line, MAX_LINE_LENGTH, fp) != NULL){
        noReserva* aux=carregaReserva(line);

        insere(tipoPreRes,aux);
    }

    fclose(fp);
}
