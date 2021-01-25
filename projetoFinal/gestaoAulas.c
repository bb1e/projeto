#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "gestaoUc.h"
#include "gestaoAulas.h"


void listarAlunos (alunos aluno[], int totalAcessos, aulaOnline aulas[], int quantAulas)
{
    char designacao[MAXSTRING];
    int i, pos;

    lerString("\nAula(designação): ", designacao, MAXSTRING);
    pos = procuraAulaAgendada(aulas, quantAulas, designacao);

    if (pos != -1)
    {
        for (i=0; i<totalAcessos; i++)
        {
            if(strcmp(aluno[i].designacaoAula, designacao) == 0 && aluno[i].acesso == 1)
            {
                printf("\nAluno %d", aluno[i].num);
            }
        }
    }
    else
    {
        printf("\nA aula não existe");
    }

}




void dadosEstatisticos (aulaOnline aulas[], int quantAulas, tipoUc vetorUc[], int quantUcs, int aulasRe)
{
    int i, j, t;
    int a, b, soma=0;
    int mediaPresencas, percentUcs, med;
    int somaT=0, somaTp=0, somaPl=0;
    int ucGravacao=0;
    int v, u, haTrocas;
    tipoUc aux;


    for (i=0; i<quantAulas; i++)
    {
        if (aulas[i].estadoAula == 3)
        {
        a = aulas[i].quantAlunos;
        soma = soma + a;
        }
    }

    mediaPresencas = soma / aulasRe;

    printf("\nQuantidade média de presenças por aula:%d\n", mediaPresencas);

    for (j=0; j<quantUcs; j++)
    {
        if (vetorUc[j].gravacoes != 0)
        {
            ucGravacao++;
        }
    }

    percentUcs = (ucGravacao*100) / quantUcs;

    printf("\nPercentagem de UCs com aulas gravadas: %d%%\n", percentUcs);



    haTrocas=1;
    for(v=0; v < quantUcs-1 && haTrocas!=0; v++)
    {
        haTrocas=0;
        for (u=0; u < quantUcs-v-1; u++)
        {

            if(vetorUc[u+1].quantAulasRe < vetorUc[u].quantAulasRe)
            {
                haTrocas=1;
                aux=vetorUc[u];
                vetorUc[u]=vetorUc[u+1];
                vetorUc[u+1]=aux;
            }
        }
    }


        med = quantUcs / 2;

        printf("\n* UCs com menor quantidade de aulas realizadas *\n");

        for (t=0; t<med; t++)
        {
            printf("%s\n", vetorUc[t].designacao);
        }

        for (i=0; i<quantAulas; i++)
        {
            if (aulas[i].tipo==1)
            {
                b = aulas[i].quantAcessos + aulas[i].quantAlunos;
                somaT = somaT + b;
            }
            else
            {
                if (aulas[i].tipo==2)
                {
                    b = aulas[i].quantAcessos + aulas[i].quantAlunos;
                    somaTp = somaTp + b;
                }
                else
                {
                    if (aulas[i].tipo==3)
                    {
                        b = aulas[i].quantAcessos + aulas[i].quantAlunos;
                        somaPl = somaPl + b;
                    }
                }
            }
        }

        if (somaT > somaTp && somaT > somaPl)
        {
            printf("\nAs aulas com mais quantidade de acessos sao as T\n");
        }
        else
        {
            if (somaTp > somaT && somaTp > somaPl)
            {
                printf("\nAs aulas com mais quantidade de acessos sao as TP\n");
            }
            else
            {
                if (somaPl > somaT && somaPl > somaTp)
                {
                    printf("\nAs aulas com mais quantidade de acessos sao as PL\n\n");
                }
            }
        }




    haTrocas=1;
    for(v=0; v < quantAulas-1 && haTrocas!=0; v++)
    {
        haTrocas=0;
        for (u=0; u < quantAulas-v-1; u++)
        {

            if(aulas[u+1].data.ano < aulas[u].data.ano && aulas[u+1].data.mes < aulas[u].data.mes && aulas[u+1].data.dia < aulas[u].data.dia)
            {
                haTrocas=1;
                aux=vetorUc[u];
                vetorUc[u]=vetorUc[u+1];
                vetorUc[u+1]=aux;
            }
        }
    }

    med = quantAulas / 2;

    printf("\n * Aulas realizadas à mais tempo * \n");

    for (i=0; i<med; i++)
    {
        printf("\n%s", aulas[i].designacao);
    }


}






alunos *registarAcesso(alunos aluno[], aulaOnline aulas[], tipoUc vetorUc[], int *totalAcessos, int quantAulas, int quantUcs) //-------------------------------------------------------------------------------------------------------------------
{
    alunos *pAluno;
    int pos, cod, pos2;
    char designacao[MAXSTRING];

    pAluno=aluno;

    lerString("\nDesignação da aula: ", designacao, MAXSTRING);
    pos = procuraAulaAgendada(aulas, quantAulas, designacao);
    cod = aulas[pos].codigo;
    pos2 = procuraUc(vetorUc, quantUcs, cod);

    if (pos != -1)
    {
        aluno=realloc(aluno, (*totalAcessos+1)*sizeof(alunos));
        if (aluno==NULL)
        {
            printf("\nERRO - Impossivel registar acesso");
            aluno=pAluno;
        }
        else
        {

        printf("*************** REGISTAR ACESSO **************");
        printf("\n\nDigite os seguintes dados\n\n");
        aluno[*totalAcessos].num = lerInteiro("Nr. Estudante:", 0, 9999);
        strcpy(aluno[*totalAcessos].designacaoAula, designacao);


        if (aulas[pos].estadoAula == 1)
        {
            printf("\nA aula ainda nao comecou");
        }
        else
        {
            if (aulas[pos].estadoAula == 2)
            {
                aluno[*totalAcessos].acesso = 1;
                (aulas[pos].quantAlunos)++;
                (*totalAcessos)++;
            }
            else
            {
                if (aulas[pos].estadoAula == 3 && aulas[pos].gravacao == 1)
                {
                    aluno[*totalAcessos].acesso = 2;
                    (aulas[pos].quantAcessos)++;
                    (vetorUc[pos2].gravacoes)++;
                    (*totalAcessos)++;
                }
                else
                {
                    printf("\nNão existe gravação desta aula!\n");
                }
            }


        }



        }
    }
    else
    {
        printf("\n\nERRO - Aula nao encontrada\n\n");
    }


        return aluno;

}




void apresentaAula (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int quantAulas)
{
    int pos, i, cod;
    char procDesignacao[MAXSTRING];


    lerString("Designação da aula: ", procDesignacao, MAXSTRING);
    pos = procuraAulaAgendada(aulas, quantAulas, procDesignacao);

    if (pos!=-1)
    {
      printf("\nCódigo da UC: %4d", aulas[pos].codigo);
      printf("\nDesignação da aula: %s", aulas[pos].designacao);
      printf("\nDocente: %s", aulas[pos].docente);
      printf("\nData da aula: %2d/%2d/%4d", aulas[pos].data.dia, aulas[pos].data.mes, aulas[pos].data.ano);
      printf("\nHora de inicio da aula%d:%d", aulas[pos].horaInicio.hora, aulas[pos].horaInicio.minuto);
      printf("\nHora de fim da aula%d:%d", aulas[pos].horaFinal.hora, aulas[pos].horaFinal.minuto);
      switch (aulas[pos].tipo)
      {
          case 1: printf("\nTipo de aula: T");
            break;
          case 2: printf("\nTipo de aula: TP");
            break;
          case 3: printf("\nTipo de aula: PL");
            break;

      }
      switch (aulas[pos].estadoAula)
      {
          case 1: printf("\nAula agendada");
            break;
          case 2: printf("\nAula a decorrer");
            break;
          case 3: printf("\nAula realizada");
            break;
      }
      printf("\nQuantidade de alunos presentes:%d", aulas[pos].quantAlunos);
      printf("\nQuantidade de acessos a gravacao:%d", aulas[pos].quantAcessos);


      cod = aulas[pos].codigo;
      i = procuraUc(vetorUc, quantUcs, cod);

      printf("\nDesignação da UC:%s", vetorUc[i].designacao);

      printf("\nQuantidade de aulas por agendar:%d", vetorUc[i].totalAulas);

    }
    else
    {
        printf("A aula não existe");
    }
}







aulaOnline *fimAula (aulaOnline aulas[], int quantAulas, int *aulasRe) //--------------------------------------------------------------------------
{

    int pos;
    char procDesignacao[MAXSTRING];


    lerString("\nDesignação da aula: ", procDesignacao, MAXSTRING);
    pos = procuraAulaAgendada(aulas, quantAulas, procDesignacao);

    if (pos!=-1)
    {
        aulas[pos].estadoAula=3;
        (*aulasRe)++;
    }



    return aulas;
}







aulaOnline *inicioAula (aulaOnline aulas[], int quantAulas, int *gravacoes, tipoUc vetorUc[], int quantUcs) //------------------------------------------------------------------------
{
    int pos, cod, i;
    char procDesignacao[MAXSTRING];


    lerString("\nDesignação da aula: ", procDesignacao, MAXSTRING);
    pos = procuraAulaAgendada(aulas, quantAulas, procDesignacao);

    if (pos!=-1)
    {
        aulas[pos].estadoAula=2;
        aulas[pos].gravacao=lerInteiro("\nPretende fazer gravação da aula?\n(1)SIM\n(2)NAO\nOpcao", 1, 2);
        if (aulas[pos].gravacao == 1)
        {
            (*gravacoes)++;

            cod = aulas[pos].codigo;
            i = procuraUc (vetorUc, quantUcs, cod);
            (vetorUc[i].gravacoes)++;
        }
    }
    else
    {
        printf("\nA aula não existe\n");
    }


    return aulas;
}





aulaOnline *lerDadosAula (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int *quantAulas) //--------------------------------------------------
{
    aulaOnline *pAula;
    int numUc, pos, pos2, tipo;
    char designacao[MAXSTRING];

    pAula=aulas;

    do
    {

    numUc=lerInteiro("Indique o número da UC: ", 1, 9999);
    pos=procuraUc(vetorUc, quantUcs, numUc);

    if(pos!=-1)
    {
        aulas=realloc(aulas,(*quantAulas+1)*sizeof(aulaOnline));
        if (aulas==NULL){
            printf("\nERRO - IMPOSSÍVEL AGENDAR AULA");
            aulas=pAula;
        }
        else{
            aulas[*quantAulas].codigo=numUc;

            do
            {

            lerString("Designação da aula: ", aulas[*quantAulas].designacao, MAXSTRING);
            strcpy(designacao, aulas[*quantAulas].designacao);
            pos2 = procuraAulaAgendada(aulas, *quantAulas, designacao);

            if (pos2 != -1)
            {
                printf("\nJá existe uma aula com essa designação! Tente novamente\n");
            }

            } while (pos2 != -1);

            aulas[*quantAulas].data=lerData("Data: ");
            aulas[*quantAulas].tipo=lerInteiro("Indique o tipo de aula (1 - T, 2 - TP, 3 - PL): ", 1, 3);
            tipo=aulas[*quantAulas].tipo;
            lerHora(&aulas[*quantAulas].horaInicio, &aulas[*quantAulas].horaFinal, aulas, *quantAulas, vetorUc, quantUcs, numUc, tipo, aulas[*quantAulas].data);
            lerString("Docente: ", aulas[*quantAulas].docente, MAXSTRING);
            aulas[*quantAulas].estadoAula = 1;
            aulas[*quantAulas].quantAcessos = 0;
            aulas[*quantAulas].quantAlunos = 0;
            (vetorUc[pos].totalAulas)--;
            (*quantAulas)++;
        }

    }
    else
    {
        printf("\n\nERRO - UC NÃO ENCONTRADA!! Volte a tentar\n\n\n");
    }

    } while (pos == -1);

    return aulas;
}





int procuraAulaAgendada (aulaOnline aulas[], int quantAulas, char procDesignacao[]) //-------------------------------------------------------------------
{
    int i, pos=-1;

    for (i=0; i < quantAulas; i++)
    {
        if (strcmp(aulas[i].designacao, procDesignacao)==0)
        {
            pos = i;
            i = quantAulas;
        }
    }

    return pos;
}



aulaOnline *eliminaAulaAgendada (aulaOnline aulas[], int *quantAulas) //-------------------------------------------------------------------
{
    aulaOnline *pAula;
    int i, pos;
    char procDesignacao[MAXSTRING];

    pAula = aulas;

    if (*quantAulas != 0)
    {
        lerString("Designação da aula: ", procDesignacao, MAXSTRING);
        pos = procuraAulaAgendada(aulas, *quantAulas, procDesignacao);
        if (pos == -1 || aulas[pos].estadoAula != 1) //1-agendada 2-a decorrer 3-realizada
        {
            printf("\nImpossivel Eliminar.\nAula não agendada, aula a decorrer ou aula ja realizada\n");
        }
        else
        {
            for (i=pos; i < *quantAulas-1; i++)
            {
                aulas[i] = aulas[i+1];
            }
            aulas = realloc(aulas, (*quantAulas-1)*sizeof(aulaOnline));
            if (aulas == NULL && (*quantAulas-1) != 0)
            {
                printf("\nERRO na alocação de memoria ");
                aulas = pAula;
            }
            (*quantAulas)--;
        }
    }
    return aulas;
}




aulaOnline *alteraAulaAgendada (aulaOnline aulas[], tipoUc vetorUc[], int quantUcs, int *quantAulas) //-------------------------------------------------------------------
{
    int pos, op;
    int cod, tipo;
    char aulaAlterar[MAXSTRING];


    lerString("Aula Online que pretende alterar agendamento(designação): ", aulaAlterar, MAXSTRING);

    pos = procuraAulaAgendada(aulas, *quantAulas, aulaAlterar);

    if (pos == -1 || aulas[pos].estadoAula != 1) //1-agendada 2-a decorrer 3-realizada
    {
        printf("\nImpossivel Alterar.\nAula nao agendada, aula a decorrer ou aula ja realizada\n");
    }
    else
    {

        printf("\n\n**********Informações da aula a alterar**********\n\n");
        printf("Designação: %s", aulas[pos].designacao);
        printf("\nCódigo da UC: %d", aulas[pos].codigo);
        printf("\nTipo de aula(1-T 2-TP 3-PL:%d", aulas[pos].tipo);
        printf("\nData: %02d-%02d-%d", aulas[pos].data.dia, aulas[pos].data.mes, aulas[pos].data.ano);
        printf("\nHora de inicio: %02d:%02d", aulas[pos].horaInicio.hora, aulas[pos].horaInicio.minuto);
        printf("\nHora de fim: %02d:%02d\n", aulas[pos].horaFinal.hora, aulas[pos].horaFinal.minuto);

        cod = aulas[pos].codigo;
        tipo = aulas[pos].tipo;


        do
        {
            op = menuAlterar2();
            switch (op)
            {
            case 1: aulas[pos].data = lerData("\nNova data: ");
                break;
            case 2: lerHora(&aulas[pos].horaInicio, &aulas[pos].horaFinal, aulas, *quantAulas, vetorUc, quantUcs, cod, tipo, aulas[pos].data);
                break;
            case 0://Voltar ao inicio
                break;
            }
        }
        while(op != 0);

    }


    return aulas;
}






int menuAlterar2 (void)//----------------------------------------------------------------------------------------------------------
{
    int opcao2;

        printf("\n\n********************* SUBMENU ALTERAR ********************\n");
        printf("(1)Alterar Data de uma Aula Agendada\n");
        printf("(2)Alterar Hora de uma Aula Agendada\n");
        printf("(0)Voltar ao Menu Principal\n");

        opcao2 = lerInteiro("\nOpção", 0, 2);


    return opcao2;
}




int menuAlterar ()//----------------------------------------------------------------------------------------------------------
{
    int opcao5;


        printf("\n\n********************* MENU ALTERAR ********************\n");
        printf("(1)Alterar o Agendamento de uma Aula Agendada\n");
        printf("(2)Eliminar Aula Agendada\n");
        printf("(0)Voltar ao Menu Principal\n");

        opcao5 = lerInteiro("\nOpção", 0, 2);


    return opcao5;
}



int menu3 () //--------------------------------------------------------------------------------------------------------------------
{

    int opcao3;

    printf("\n\nO que pertende fazer?\n\n");
    printf("(1)Registar inicio da aula\n");
    printf("(2)Registar fim da aula\n");
    printf("(0)Sair");

    opcao3=lerInteiro("\n\nIndique a opção", 0, 2);

    return opcao3;
}





int menu4 () //-----------------------------------------------------------------------------------------------------------------------------------
{
    int opcao4;

    printf("\n\t(1) Le ficheiro das aulas");
    printf("\n\t(2) Le ficheiro das UCs");
    printf("\n\t(3) Armazena aulas no ficheiro");
    printf("\n\t(4) Armazena UCs no ficheiro");
    printf("\n\t(0) Sair");

    opcao4 = lerInteiro("\nOpção", 0, 4);

    return opcao4;
}




aulaOnline *leFicheiroAula (aulaOnline e[], int *num) //----------------------------------------------------------------------------------------------------------
{
    FILE *f;
    aulaOnline *pAula;

    f=fopen("aula.dat", "rb");
    if (f!=NULL) {
        fread (&(*num), sizeof(int), 1, f);
        pAula = e;
        e = realloc(e, (*num) * sizeof(aulaOnline));
        if (e == NULL && *num != 0)
        {
            printf("\nErro ao reservar memoria");
            e = pAula;
        }
        else
        {
        fread (e, sizeof(aulaOnline), *num, f);
        }
        fclose(f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }

    return e;
}



alunos *leFicheiroAluno (alunos e[], int *num) //---------------------------------------------------------------------------------------------
{
    FILE *f;
    alunos *pAluno;

    f=fopen("alunos.dat", "rb");
    if (f!=NULL) {
        fread (&(*num), sizeof(int), 1, f);
        pAluno = e;
        e = realloc(e, (*num) * sizeof(alunos));
        if (e == NULL && *num != 0)
        {
            printf("\nErro ao reservar memoria");
            e = pAluno;
        }
        else
        {
        fread (e, sizeof(alunos), *num, f);
        }
        fclose(f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }

    return e;
}




void leFicheiroUc (tipoUc e[], int *num) //----------------------------------------------------------------------------------------------------------
{
    FILE *f;
    f=fopen("uc.dat", "rb");
    if (f!=NULL) {
        fread (&(*num), sizeof(int), 1, f);
        fread (e, sizeof(tipoUc), (*num), f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }
    fclose(f);
}





void gravaFicheiroAula (aulaOnline e[], int num) //-------------------------------------------------------------------------------------------------------
{
    FILE *f;
    f=fopen("aula.dat", "wb");
    if (f!=NULL)
    {
        fwrite(&num, sizeof(int), 1, f);
        fwrite(e, sizeof(aulaOnline), num, f);

        fclose(f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }

}


void gravaFicheiroAluno (alunos e[], int num) //-------------------------------------------------------------------------------------------------
{
    FILE *f;
    f=fopen("alunos.dat", "wb");
    if (f!=NULL)
    {
        fwrite(&num, sizeof(int), 1, f);
        fwrite(e, sizeof(alunos), num, f);

        fclose(f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }
}



void ficheiroTexto (alunos e[], int num) //-----------------------------------------------------------------------------------------------
{
    FILE *f;
    int i;
    f=fopen("alunos.txt", "w");
    if (f == NULL)
    {
        printf("\nImpossivel abrir ficheiro");
    }
    else
    {
        fprintf(f, "Acessos =%d \n", num);

        for (i=0; i<num; i++)
        {
            fprintf(f, "\nNum:%d \n", e[i].num);
            fprintf(f, "Aula:%s \n", e[i].designacaoAula);
            fprintf(f, "Tipo de acesso (1- online/2-offline):%d \n", e[i].acesso);
        }

        fclose(f);
    }
}




void gravaFicheiroUc (tipoUc e[], int num) //-------------------------------------------------------------------------------------------------------
{
    FILE *f;
    f=fopen("uc.dat", "wb");
    if (f!=NULL) {
        fwrite(&num, sizeof(int), 1, f);
        fwrite(e, sizeof(tipoUc), num, f);
    }
    else
    {
        printf("\nImpossivel abrir ficheiro");
    }
    fclose(f);
}




int menuFicheiros ()
{
    int opcao;

    printf("\n\t(1) Registar acesso");
    printf("\n\t(2) Le ficheiro dos alunos");
    printf("\n\t(3) Armazena alunos em ficheiro binário");
    printf("\n\t(4) Armazena alunos em ficheiro de texto");
    printf("\n\t(0) Sair\n");

    opcao = lerInteiro("\nOpção", 0, 4);

    return opcao;
}





void lerHora (tipoHora *horaInicio, tipoHora *horaFinal, aulaOnline aulas[], int quantAulas, tipoUc vetorUc[], int quantUcs, int cod, int tipo, tipoData data)
{
    int horaI, horaF, duracao;
    int controlo1=0, controlo2=0;
    int pos, regime, i, soma, somaf;
    tipoHora h, f;


    pos = procuraUc(vetorUc, quantUcs, cod);
    regime = vetorUc[pos].regime;


    switch (regime)
    {
    case 1:
        horaI = 8;
        horaF = 18;
        break;
    case 2:
        horaI = 18;
        horaF = 24;
        break;
    }




    switch (tipo)
    {
    case 1:
        duracao = vetorUc[pos].duracao.t;
        break;
    case 2:
        duracao = vetorUc[pos].duracao.tp;
        break;
    case 3:
        duracao = vetorUc[pos].duracao.pl;
        break;
    }



    do
    {


        h.hora = lerInteiro("\nInsira a hora de inicio", 0, 23);
        h.minuto = lerInteiro("\nInsira os minutos de inicio", 0, 59);


        if(h.hora<horaI)
        {
            printf("\n\nHora inválida para o regime da UC! Volte a tentar\n\n");
            controlo1 = 1;
        }
        else
        {
            if (h.hora>=horaF)
            {
                printf("\n\nHora inválida para o regime da UC! Volte a tentar\n\n");
                controlo1 = 1;
            }
            else
            {
                controlo1 = 2;
            }


            for (i=0; i<quantAulas; i++)
            {
                if ((data.dia != aulas[i].data.dia || data.mes != aulas[i].data.mes || data.ano != aulas[i].data.ano) && (aulas[i].codigo==cod))
                {
                    controlo2 = 2;
                }
                else
                {
                    if (aulas[i].codigo==cod)
                    {
                        if (h.hora>=aulas[i].horaInicio.hora && h.hora<=aulas[i].horaFinal.hora)
                        {
                            printf("\n\nJá existe aula marcada para essa hora! Tente novamente\n\n");
                            controlo2 = 1;
                        }
                        else
                        {
                            controlo2 = 2;
                        }

                    }


                }
        }
        }


    } while (controlo1 != 2 && controlo2 != 2);


    soma = h.hora*60 + h.minuto;
    somaf = soma + duracao;
    f.hora = somaf/60;
    f.minuto =((somaf/60.0)-f.hora)*60;


    *horaInicio = h;
    *horaFinal = f;

}



