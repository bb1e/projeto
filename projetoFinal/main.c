#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#include "gestaoUc.h"
#include "gestaoAulas.h"
#include "funcoes_auxiliares.h"



int menu (void);



int main()
{

    setlocale (LC_ALL, "Portuguese");
    tipoUc vetorUc [MAXUCS];
    aulaOnline *aulas=NULL;
    alunos *aluno=NULL;
    int quantUcs=0;
    int quantAulas=0;
    int totalAcessos=0;
    int opcao, op;
    int aulasRe=0;
    int gravacoes=0;



do
{

    printf("\n\n*********************** INFORMAÇÕES GLOBAIS ************************\n\n");
    printf("\t\tQuantidade de UCs:%d", quantUcs);
    printf("\n\t\tQuantidade de aulas agendadas:%d", quantAulas);
    printf("\n\t\tQuantidade de aulas realizadas:%d", aulasRe);
    printf("\n\t\tQuantidade de aulas gravadas:%d\n\n", gravacoes);




    opcao = menu();

    switch (opcao)
    {
   case 1:
       inserirUc(vetorUc, &quantUcs);
    break;
   case 2:
       alterarUc(vetorUc, quantUcs);
    break;
   case 3:
       listarUc(vetorUc, quantUcs, aulas, quantAulas);
    break;
   case 4:
       aulas = lerDadosAula(aulas, vetorUc, quantUcs, &quantAulas);
    break;
   case 5:
       aulas = alteraAulaAgendada(aulas, vetorUc, quantUcs, &quantAulas);
    break;
   case 6:
       aulas = eliminaAulaAgendada(aulas, &quantAulas);
    break;
   case 7:

       do
       {
          op = menu3 ();
          switch (op)
          {
          case 1:
              aulas = inicioAula(aulas, quantAulas, &gravacoes, vetorUc, quantUcs);
            break;
          case 2:
              aulas = fimAula(aulas, quantAulas, &aulasRe);
            break;
          case 0:
            break;
          }
       } while (op != 0);

    break;
   case 8:
     do{
       op = menuFicheiros();
       switch (op)
       {
       case 1:
           aluno = registarAcesso(aluno, aulas, vetorUc, &totalAcessos, quantAulas, quantUcs);
        break;
       case 2:
           aluno = leFicheiroAluno(aluno, &totalAcessos);
        break;
       case 3:
           gravaFicheiroAluno(aluno, totalAcessos);
        break;
       case 4:
           ficheiroTexto(aluno, totalAcessos);
        break;
       case 0:
        break;
       }
     } while (op != 0);
    break;
   case 9:
       do
       {
           op = menu4();
           switch (op)
           {
           case 1:
               aulas = leFicheiroAula(aulas, &quantAulas);
            break;
           case 2:
               leFicheiroUc(vetorUc, &quantUcs);
            break;
           case 3:
               gravaFicheiroAula(aulas, quantAulas);
            break;
           case 4:
               gravaFicheiroUc(vetorUc, quantUcs);
            break;
           case 0:
            break;
           }
       } while (op != 0);
       break;
   case 10:
       apresentaAula(aulas, vetorUc, quantUcs, quantAulas);
    break;
   case 11:
       rankingUcs(vetorUc, quantUcs);
    break;
   case 12:
       dadosEstatisticos(aulas, quantAulas, vetorUc, quantUcs, aulasRe);
    break;
   case 13:
       listarAlunos(aluno, totalAcessos, aulas, quantAulas);
    break;
   case 0:
    break;
    }

}
    while (opcao != 0);



    free(aulas);
    free(aluno);
    return 0;
}






int menu () //------------------------------------------------------------------------------------------------------------------------------------
{
    int opcao;


        printf("\n\n************************** MENU PRINCIPAL **************************\n\n");
        printf("\t(1)   Inserir informação de uma UC\n");
        printf("\t(2)   Alterar informação de uma UC\n");
        printf("\t(3)   Listar informação das UCs\n");
        printf("\t(4)   Agendar aula online\n");
        printf("\t(5)   Alterar aula agendada\n");
        printf("\t(6)   Eliminar aula agendada\n");
        printf("\t(7)   Registar o início da aula online\n");
        printf("\t(8)   Registar acesso do estudante\n");
        printf("\t(9)   Armazenar ou ler informação em ficheiro binario\n");
        printf("\t(10)  Listar informação de uma aula online\n");
        printf("\t(11)  Ranking das UCs\n");
        printf("\t(12)  Dados Estatísticos\n");
        printf("\t(13)  Listagem de estudantes presentes na aula online\n");
        printf("\t(0)   Sair");

        opcao=lerInteiro("\n\n\tIndique uma opção", 0, 13);


    return opcao;
}





