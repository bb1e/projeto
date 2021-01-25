#ifndef GESTAOUC_H_INCLUDED
#define GESTAOUC_H_INCLUDED

#define MAXUCS 40

#define MAXSTRING 50

#include "funcoes_auxiliares.h"



typedef struct
{
    int num;
    int acesso;
    char designacaoAula[MAXSTRING];

} alunos;



typedef struct
{
    int t;
    int tp;
    int pl;

} duracao;




typedef struct
{
    int t;
    int tp;
    int pl;

} tipoAula;



typedef struct
{
  int codigo;
  char designacao[MAXSTRING];
  int semestre;
  int tipo;
  int regime;
  tipoAula quantidade;
  duracao duracao;
  int totalAulas; //quantidade de t + tp + pl
  int quantAulasRe; //total de aulas realizadas da uc
  int gravacoes; //total de acessos a gravacoes da uc

} tipoUc;




typedef struct
{
    char designacao[MAXSTRING];
    int codigo;
    int tipo;
    char docente[MAXSTRING];
    tipoHora horaInicio;
    tipoHora horaFinal;
    tipoData data;
    int estadoAula;
    int gravacao; //se tem gravação ou não
    int quantAlunos; //n de alunos q acedeu à aula
    int quantAcessos; //n de acessos à gravacao

} aulaOnline;








tipoUc leDadosUc ();
void inserirUc (tipoUc vetorUc[], int *quantUcs);
int procuraUc (tipoUc vetorUc[], int quantUcs, int codigoUc);
void alterarUc (tipoUc vetorUc[], int quantUcs);
int menu2 ();
void listarUc (tipoUc vetorUc[], int quantUcs, aulaOnline aulas[], int quantAulas);
void rankingUcs (tipoUc vetorUc[], int quantUcs);

#endif // GESTAOUC_H_INCLUDED
