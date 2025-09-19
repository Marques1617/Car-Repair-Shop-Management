#ifndef PPP_H
#define PPP_H 
#define TAM_NOME 50


typedef struct{
    int id;
    char nome[TAM_NOME];
    int horaInicial;
    int minutoInicial;
    int horaFinal;
    int minutoFinal;
    int tipo; //tipo == 0 ->lavagem    tipo == 1-> manutençao
    int dia,mes,ano;
} Reserva;

typedef struct noR{
    Reserva reserva;
    struct noR *prox;
} noReserva;

// typedef struct noPR{
//     Reserva prereserva;
//     struct noPR *prox;
// } noPreReserva;

typedef struct{
    noReserva* inicio;
    noReserva* fim;
} tipoReserva;


// Function declarations
tipoReserva* criaTipo();
noReserva* cria();
int adiciona(noReserva* novo, noReserva* inicio, noReserva* aux);
void insere(tipoReserva* tipo, noReserva* novo);
void eliminar(tipoReserva* tipo, int id);
void verificaPreReservas(tipoReserva* pre, tipoReserva* res);
void imprimeOrdenado(noReserva* inicio);
void imprimeCliente(noReserva* inicio);
void gravarFicheiro(tipoReserva *tipoRes,char nomeficheiro[]);
void carregarFicheiroReservas(tipoReserva *tipoRes,tipoReserva *tipoPreRes, char nomeficheiro[]);
void carregarFicheiroPreReservas(tipoReserva *tipoPreRes, char nomeficheiro[]);
#endif