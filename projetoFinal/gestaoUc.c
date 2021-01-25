#include <stdio.h>

#include "funcoes_auxiliares.h"
#include "gestaoUc.h"

#define MIN_NRUCS 0
#define MAX_NRUCS 40


int menu2 () //-----------------------------------------------------------------------------------------------------------------------------------------
{
    int opcao2;

    printf("\n\n * O que deseja alterar? * \n\n");
    printf("\t(1) Código da uc\n");
    printf("\t(2) Designação da uc\n");
    printf("\t(3) Semestre\n");
    printf("\t(4) Tipo de UC\n");
    printf("\t(5) Regime\n");
    printf("\t(6) Quantidade de aulas\n");
    printf("\t(7) Duração das aulas\n");
    printf("\t(0) Sair");

    opcao2=lerInteiro("\n\nIndique a opção", 0, 7);

    return opcao2;
}




void alterarUc (tipoUc vetorUc[], int quantUcs) //------------------------------------------------------------------------------------------------------
{

    int pos, cod, opcao;

    do
    {

    cod = lerInteiro("Código da UC que pretende alterar: ", 1, 9999);
    pos = procuraUc(vetorUc, quantUcs, cod);

    if (pos == -1)
    {
        printf("\n\nImpossivel alterar, essa UC nao existe!! Volte a tentar\n\n");
    }
    else
    {
      printf("\n\n*******Informações da aula a alterar*******\n\n");
      printf("\nCódigo:%d", vetorUc[pos].codigo);
      printf("\nDesignação:%s", vetorUc[pos].designacao);
      printf("\nSemestre:%d", vetorUc[pos].semestre);
      printf("\nTipo de UC(1-obrigatoria 2-opcional):%d\n", vetorUc[pos].tipo);
      printf("\nRegime(1-diurno 2-pos-laboral):%d\n", vetorUc[pos].regime);
      printf("\nQuantidade de aulas:\nT->%d\nTP->%d\nPL->%d\n", vetorUc[pos].quantidade.t, vetorUc[pos].quantidade.tp, vetorUc[pos].quantidade.pl);
      printf("\nDuração das aulas(em minutos):\nT->%d\nTP->%d\nPL->%d\n", vetorUc[pos].duracao.t, vetorUc[pos].duracao.tp, vetorUc[pos].duracao.pl);

    do
    {
        opcao = menu2();
        switch (opcao)
        {
        case 1:
            vetorUc[pos].codigo = lerInteiro("\nCódigo: ", 1, 9999);
            break;
        case 2:
            lerString("Designação da UC: ", vetorUc[pos].designacao, MAXSTRING);
            break;
        case 3:
            vetorUc[pos].semestre = lerInteiro("Semestre: ",1 ,6);
            break;
        case 4:
            vetorUc[pos].tipo = lerInteiro("(1)Obrigatoria\n(2)Opcional\n-> ",1 ,2);
            break;
        case 5:
            vetorUc[pos].regime = lerInteiro("(1)Diurno\n(2)Pos-laboral\n-> ",1 ,2);
            break;
        case 6:
            vetorUc[pos].quantidade.t = lerInteiro("Quantidade de aulas T: ", 0 , 100);
            vetorUc[pos].quantidade.tp = lerInteiro("Quantidade de aulas TP: ", 0, 100);
            vetorUc[pos].quantidade.pl = lerInteiro("Quantidade de aulas PL: ", 0, 100);
            break;
        case 7:
            vetorUc[pos].duracao.t = lerInteiro("Duração das aulas T(em minutos): ", 0, 360);
            vetorUc[pos].duracao.tp = lerInteiro("Duração das aulas TP(em minutos): ", 0, 360);
            vetorUc[pos].duracao.pl = lerInteiro("Duração das aulas PL(em minutos): ", 0, 360);
            break;
        case 0:
            break;
        }
    }
    while (opcao != 0);


    }

    } while (pos == -1);

}





void listarUc (tipoUc vetorUc[], int quantUcs, aulaOnline aulas[], int quantAulas) //------------------------------------------------------------------------------------------------------------------------------------
{
    int pos, i, j;
    //int cod;
    int t=0, tp=0, pl=0;

    printf("\n\n*******Informações das UCs*******\n\n");

    for (pos=0; pos<quantUcs; pos++)
    {

      printf("\nCódigo:%d", vetorUc[pos].codigo);
      //vetorUc[pos].codigo = cod;
      printf("\nDesignação:%s", vetorUc[pos].designacao);
      printf("\nSemestre:%d", vetorUc[pos].semestre);
      printf("\nTipo de UC(1-obrigatoria 2-opcional):%d\n", vetorUc[pos].tipo);
      printf("\nRegime(1-diurno 2-pos-laboral):%d\n", vetorUc[pos].regime);
      printf("\nQuantidade de aulas:\nT->%d\nTP->%d\nPL->%d\n", vetorUc[pos].quantidade.t, vetorUc[pos].quantidade.tp, vetorUc[pos].quantidade.pl);
      printf("\nDuração das aulas(em minutos):\nT->%d\nTP->%d\nPL->%d\n", vetorUc[pos].duracao.t, vetorUc[pos].duracao.tp, vetorUc[pos].duracao.pl);


      for (i=0; i < quantAulas; i++)
      {
          if ( aulas[i].codigo == vetorUc[pos].codigo)
          {
              switch (aulas[i].tipo)
              {
              case 1: printf("\nAula T");
                break;
              case 2: printf("\nAula TP");
                break;
              case 3: printf("\nAula PL");
                break;
              }

            printf("\nData: %02d-%02d-%d", aulas[i].data.dia, aulas[i].data.mes, aulas[i].data.ano);
            printf("\nHora de inicio: %02d:%02d\n\n", aulas[i].horaInicio.hora, aulas[i].horaInicio.minuto);

          }
      }

      for (j=0; j<quantAulas; j++)
      {
          if (aulas[j].codigo == vetorUc[pos].codigo && aulas[j].tipo == 1 && aulas[j].estadoAula == 3)
          {
              t++;
          }
          else
          {
              if (aulas[j].codigo == vetorUc[pos].codigo && aulas[j].tipo == 2 && aulas[j].estadoAula == 3)
              {
                  tp++;
              }
              else
              {
                  if (aulas[j].codigo == vetorUc[pos].codigo && aulas[j].tipo == 3 && aulas[j].estadoAula == 3)
                  {
                      pl++;
                  }
              }
          }

      }

      printf("\nAulas T realizadas:%d", t);
      printf("\nAulas TP realizadas:%d", tp);
      printf("\nAulas PL realizadas:%d\n\n\n", pl);

    }


    }







int procuraUc (tipoUc vetorUc[], int quantUcs, int codigoUc) //-----------------------------------------------------------------------------------
{
    int i, pos=-1;

    for (i=0; i < quantUcs; i++)
    {
        if (vetorUc[i].codigo == codigoUc)
        {
            pos = i;
            i = quantUcs;
        }
    }

    return pos;
}




void inserirUc (tipoUc vetorUc[], int *quantUcs) //-----------------------------------------------------------------------------------------------
{
    tipoUc dados;
    int pos;

    if (*quantUcs == MAXUCS)
    {
        printf("\nImpossivel inserir UC\n");
    }
    else
    {
        dados = leDadosUc();
        pos = procuraUc(vetorUc, *quantUcs, dados.codigo);
        if (pos != -1)
        {
            printf("\nA UC já existe\n");
        }
        else
        {
            vetorUc[*quantUcs] = dados;
            (*quantUcs)++;
        }
    }
}






tipoUc leDadosUc () //--------------------------------------------------------------------------------------------------------------------------
{
    tipoUc uc;

        printf("\n\n************ Nova UC ************\n\n");
        uc.codigo = lerInteiro("\nCódigo", 1, 9999);
        lerString("\nDesignação da UC: ", uc.designacao, MAXSTRING);
        uc.semestre = lerInteiro("\nSemestre",1 ,6);
        uc.tipo = lerInteiro("\n(1)Obrigatoria\n(2)Opcional\nOpcao",1 ,2);
        uc.regime = lerInteiro("\n(1)Diurno\n(2)Pos-laboral\nOpcao",1 ,2);
        uc.quantidade.t = lerInteiro("\nQuantidade de aulas T", 0 , 100);
        uc.quantidade.tp = lerInteiro("\nQuantidade de aulas TP", 0, 100);
        uc.quantidade.pl = lerInteiro("\nQuantidade de aulas PL", 0, 100);
        uc.duracao.t = lerInteiro("\nDuração das aulas T(em minutos)", 0, 360);
        uc.duracao.tp = lerInteiro("\nDuração das aulas TP(em minutos)", 0, 360);
        uc.duracao.pl = lerInteiro("\nDuração das aulas PL(em minutos)", 0, 360);
        uc.quantAulasRe = 0;
        uc.totalAulas = uc.quantidade.t + uc.quantidade.tp + uc.quantidade.pl;
        uc.gravacoes = 0;



        return uc;
}





void rankingUcs (tipoUc vetorUc[], int quantUcs) //------------------------------------------------------------------------------------------
{
    int i, j, haTrocas, a;
    tipoUc aux;

    haTrocas=1;
    for(i=0; i < quantUcs-1 && haTrocas!=0; i++)
    {
        haTrocas=0;
        for (j=0; j < quantUcs-i-1; j++)
        {
            if(vetorUc[j+1].gravacoes > vetorUc[j].gravacoes) //decrescente (se o elemento seguinte é inferior, efetua troca - haTrocas=1)
            {
                haTrocas=1;
                aux=vetorUc[j];
                vetorUc[j]=vetorUc[j+1];
                vetorUc[j+1]=aux;
            }
        }
    }

    printf("\n\nRanking de acessos as gravacoes das UCs por ordem decrescente\n\n");

    for (a=0; a<quantUcs; a++)
    {
        printf("\n%s\n", vetorUc[a].designacao);
    }



}


