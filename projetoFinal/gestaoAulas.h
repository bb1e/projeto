#ifndef GESTAOAULAS_H_INCLUDED
#define GESTAOAULAS_H_INCLUDED


#include "gestaoUc.h"
#include "funcoes_auxiliares.h"


void dadosEstatisticos (aulaOnline aulas[], int quantAulas, tipoUc vetorUc[], int quantUcs, int aulasRe);
void lerHora (tipoHora *horaInicio, tipoHora *horaFinal, aulaOnline aulas[], int quantAulas, tipoUc vetorUc[], int quantUcs, int cod, int tipo, tipoData data);
void listarAlunos (alunos aluno[], int totalAcessos, aulaOnline aulas[], int quantAulas);
alunos *registarAcesso(alunos aluno[], aulaOnline aulas[], tipoUc vetorUc[], int *totalAcessos, int quantAulas, int quantUcs);
aulaOnline *lerDadosAula (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int *quantAulas);
int procuraAulaAgendada (aulaOnline aulas[], int quantAulas, char procDesignacao[]);
aulaOnline *eliminaAulaAgendada (aulaOnline aulas[], int *quantAulas);
aulaOnline *alteraAulaAgendada (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int *quantAulas);
int menuAlterar2 (void);
aulaOnline *inicioAula (aulaOnline aulas[], int quantAulas, int *gravacoes, tipoUc vetorUc[], int quantUcs);
aulaOnline *fimAula (aulaOnline aulas[], int quantAulas, int *aulasRe);
int menuAlterar ();
int menu3 ();
void apresentaAula (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int quantAulas);


aulaOnline *leFicheiroAula (aulaOnline e[], int *num);
void leFicheiroUc (tipoUc e[], int *num);
void gravaFicheiroAula (aulaOnline e[], int num);
void gravaFicheiroUc (tipoUc e[], int num);
void gravaFicheiroAluno (alunos e[], int num);
void ficheiroTexto (alunos e[], int num);
alunos *leFicheiroAluno (alunos e[], int *num);
int menu4 ();
int menuFicheiros ();

#endif // GESTAOAULAS_H_INCLUDED
