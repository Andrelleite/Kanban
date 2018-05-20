#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"


/**

        LEFT:
                Restrição de uma tarefa por semana
                ler tarefas do ficheiro


        Todas as funções têm um papel fulcral, sendo que existem algumas que se tornam preponderantes na implementação deste código, uma vez que são utilizadas constantemente
        e até mesmo chamadas pelas outras funções, de modo a tornar o código mais eficiente, mais versátil e mais leve. É importante manter um código bem estruturado para que a sua
        manutenção seja fácil

        GitHub -> https://github.com//Andrelleite

        n of functions : 24
        voids : 13
        Task* : 1
        Pessoa* : 1
        Data* :  1
        int: 6

**/

lista_task cria_lista_tarefas(){ /* Função para inicializar a lista de tarefas*/

        lista_task novo = (Node *) malloc(sizeof(Node));
        if(novo != NULL){

                novo->n = 0;
                novo->next = NULL;
                novo->tarefa = NULL;

        }

        return novo;

}

lista_pessoas cria_lista_pessoas(){ /* Função para inicializar uma lista de pessoas */

        lista_pessoas novo = (lista_pessoas)malloc(sizeof(P_Node));
        if(novo != NULL){
                novo->n_task = 1;
                novo->n = 0 ;
                novo->next = NULL;
                novo->p = NULL;
        }

        return novo;

}

void insere_pessoa(lista_pessoas lista){ /* Inserção de uma pessoa numa lista ligada */

        Pessoa *nova = cria_pessoa(lista);
        lista_pessoas no = (lista_pessoas)malloc(sizeof(P_Node));

        no->p = nova;
        no->n = 0;

        if(lista != NULL){

                lista->n++;
                no->next = lista->next;
                lista->next = no;

        }

}

Pessoa *cria_pessoa(lista_pessoas lista){ /* Criar uma pessoa/trabalhador em memória */

        Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));

        novo->nome = (char *)malloc(15 * sizeof(char));
        novo->mail = (char *)malloc(30 * sizeof(char));

        system("cls");
        printf("\n\n\tCriacao de Trabalhador\n\n");
        printf("Nome: ");
        fgets(novo->nome, 15,stdin);
        printf("Idade: ");
        scanf("%d", &novo->idade);
        getchar();
        printf("E-Mail: ");
        fgets(novo->mail, 30, stdin);
        novo->id = lista->n + 1;
        printf("Id: %d\n\n",novo->id);

        if(lista->next == NULL){
                printf("Numero de tarefas maxima: ");
                scanf("%d",&novo->max_task);
                getchar();

                while(novo->max_task <= 0){
                        printf("\nAdicione um limite acima de 0.\n");
                        printf("Numero de tarefas maxima: ");
                        scanf("%d",&novo->max_task);
                        getchar();

                }

        }else{
                novo->max_task = lista->next->p->max_task;
                printf("\nAtribuindo numero maximo de tarefas global (%d).\n",novo->max_task);
        }


        novo->mytasks = cria_lista_tarefas();

        printf("Pressione Enter para continuar... ");
        getchar();

        return novo;
}

void imprime_lista_pessoas(lista_pessoas lista){ /* Fazer display de uma lista de pessoas/trabalhadores em consola */

        Pessoa *pessoa;
        lista_pessoas act = lista->next;

        printf("____Lista de Trabalhadores____\n\n");
        printf("    N de trabalhadores: %d\n\n",lista->n);

        if(lista->next == NULL){
                printf("    (Sem trabalhadores)\n\n");
        }else{

                printf("__________________________________________________\n\n");
                while(act != NULL){
                        pessoa = act->p;
                        printf("Nome: %s | Idade: %d | E-Mail: %s | Max Tasks: %d \n | ID: %d\n__________________________________________________\n\n",pessoa->nome,pessoa->idade,pessoa->mail, pessoa->max_task,pessoa->id);

                        act = act->next;
                }

        }

        printf("Pressione Enter para continuar... ");
        getchar();

}

int get_worker(lista_pessoas lista, lista_pessoas *act, int id){ /* obter um trabalhador pelo seu ID */

        int found  = 0;
        *act = lista->next;

        if(lista->next == NULL){
                printf("    (Sem trabalhadores)\n\n");
        }else if(id >= 0 && id < lista->n + 1){

                while(*act != NULL && found == 0){

                        if( (*act)->p->id == id ){
                                found = 1;
                        }else{
                                (*act) = (*act)->next;
                        }
                }
        }else{
                found = 0;
        }

        return found;

}

int get_task(lista_task lista,lista_task *ant ,lista_task *act, int id){ /* obter uma tarefa pelo seu ID */

        int found  = 0;
        *act = lista->next;
        *ant = lista;

        if(lista->next == NULL){
                printf("(Sem tarefas)\n\n");
        }
        else if(id >= 0 ){

                while(*act != NULL && found == 0){

                        if( (*act)->tarefa->id == id ){
                                found = 1;
                        }else{
                                (*ant) = (*act);
                                (*act) = (*act)->next;
                        }
                }

        }
        else{

                found = 0;

        }

        return found;



}

void worker_info(lista_pessoas lista){ /* Obter informação de um trabalhador */

        lista_pessoas work;
        Pessoa *p;
        int id;
        int choice;
        int got;
        system("cls");

        printf("\n\n\tInformacao de Trabalhador\n\n");

        printf(" ID: ");
        scanf("%d",&id);
        getchar();

        got = get_worker(lista,&work,id);

        if(got){
                p = work->p;
                printf("__________________________________________________\n\n");
                printf("Nome: %s | Idade: %d | E-Mail: %s | ID: %d\n__________________________________________________\n\n",p->nome,p->idade,p->mail, p->id);

                printf("Ver lista de tarefas deste trabalhador? [ 1 - sim / 0 - nao]\n-> ");
                scanf("%d",&choice);
                getchar();
                if(choice){
                        printf("\n      Worker %s\n\t ID: %d \n",p->nome,p->id);
                        imprime_lista_tarefas(p->mytasks);
                }

        }else if(got == 0){
                printf("ID errado. Tente novamente.\n\n");
        }

        printf("Pressione qualquer tecla para continuar... ");
        getchar();
}

Task *cria_tarefa(lista_task lista){ /* Criar uma tarefa em memória */

        Task *nova = (Task *)malloc(sizeof(Task));
        int comp;

        system("cls");

        printf("\n\n\tCriacao de Tarefa\n\n");

        nova->id = lista->n+1;

        printf("Prioridade (1-10) : ");
        scanf("%d",&nova->priority);
        getchar();

        while(nova->priority < 1 || nova->priority > 10){
                printf("\nPrioridade Invalidade. Tente um valor de  1 a 10.\n");
                printf("\nPrioridade (1-10) : ");
                scanf("%d",&nova->priority);
                getchar();
        }

        printf("Descricao: ");
        nova->descricao = (char *)malloc(30*sizeof(char));
        fgets(nova->descricao,30,stdin );

        printf("Data de Criacao ");
        nova->inicio = set_data();

        while(check_date_erros(nova->inicio)){
                printf("Data de criacao ");
                nova->inicio = set_data();
        }


        printf("Prazo final ");
        nova->prazo = set_data();

        while(check_date_erros(nova->prazo)){
                printf("Prazo final ");
                nova->prazo = set_data();

        }


        comp = compare_date(nova->inicio,nova->prazo);

        while(comp == 1 || comp == 0){
                printf("\nPrazo definido nao excede a data de criacao. Insira novamente.\n\n");
                printf("Prazo final ");
                nova->prazo = set_data();
                comp = compare_date(nova->inicio,nova->prazo);

        }

        nova->fim = NULL;
        nova->worker = NULL;
        nova->personId= 0;
        nova->fase = 1;
        printf("ID: %d\n", nova->id);

        printf("Pressione Enter para continuar... ");
        getchar();

        insere_tarefa(lista,nova,0);

        return nova;
}

void insere_tarefa(lista_task lista, Task *nova, int flag){ /* Inserir uma tarefa numa lista ligada */

        lista_task then = lista->next;
        lista_task ante = lista;

        lista_task no = (lista_task)malloc(sizeof(Node));
        printf("\nA inserir tarefa...\n");

        no->tarefa = nova;
        no->n = 0;
        lista->n++;

        if(nova != NULL && then == NULL){

                no->next = then;
                ante->next = no;
                printf("Tarefa inserida.\n");
        }

        else if(nova != NULL && then != NULL){

                if(flag == 0){ /* Ordenamento por ordem crescente de data de criação*/

                        while(compare_date(nova->inicio,then->tarefa->inicio) == 1 && then->next != NULL){

                                ante = then;
                                then = then->next;
                        }

                      if(compare_date(nova->inicio , then->tarefa->inicio) != 1 ){

                                ante->next = no;
                                no->next = then;

                      }
                      else if (compare_date(nova->inicio, then->tarefa->inicio)){

                                no->next = then->next;
                                then->next = no;

                      }

                }
                else if(flag == 1){ /* Ordenamento crescente por data de conclusao*/

                        while(compare_date(nova->fim,then->tarefa->fim) == 1 && then->next != NULL){

                                ante = then;
                                then = then->next;
                        }

                      if(compare_date(nova->fim , then->tarefa->fim) != 1 ){

                                ante->next = no;
                                no->next = then;

                      }
                      else if (compare_date(nova->fim, then->tarefa->fim)){

                                no->next = then->next;
                                then->next = no;

                      }


                }
                else if(flag == 2){ /* Ordenamento decescente por prioridade */

                        while(nova->priority < then->tarefa->priority && then->next != NULL){

                                ante = then;
                                then = then->next;
                        }

                      if(nova->priority > then->tarefa->priority ){

                                ante->next = no;
                                no->next = then;

                      }
                      else if (nova->priority < then->tarefa->priority){

                                no->next = then->next;
                                then->next = no;

                      }
                      else if (nova->priority == then->tarefa->priority){ /*Ordenamento crescente de data de criacao para prioridades iguais */


                                while( compare_date(nova->inicio , then->tarefa->inicio) == 1 && (nova->priority == then->tarefa->priority) && (then->next != NULL )){
                                        ante = then;
                                        then = then->next;

                                }

                                if(compare_date(nova->inicio,then->tarefa->inicio) == 1){
                                        no->next = then->next;
                                        then->next = no;
                                }
                                else if(compare_date(nova->inicio , then->tarefa->inicio) != 1 ){

                                        ante->next = no;
                                        no->next = then;

                                }
                      }

                }
                else if(flag == 3){ /* Ordenamento por ordem alfabetica */

                        while((strcmp(nova->worker->nome, then->tarefa->worker->nome)) > 0 && then->next != NULL){

                                ante = then;
                                then = then->next;
                        }

                      if( (strcmp(nova->worker->nome, then->tarefa->worker->nome)) < 0 ){

                                ante->next = no;
                                no->next = then;

                      }
                      else{

                                no->next = then->next;
                                then->next = no;

                      }

                }

        }

}

void imprime_lista_tarefas(lista_task lista){ /* Fazer diplay de TODAS as tarefas existentes em consola, já devidamente ordenadas*/

        lista_task act = lista->next;
        Task *tarefa;

        printf("_____Lista de Tarefas_____\n\n");
        printf("    Numero de tarefas: %d\n\n",lista->n);

        if(lista->next == NULL){
                printf("      (Sem tarefas)\n\n");
        }else{

                printf("__________________________________________________\n\n");
                while(act != NULL){
                        tarefa = act->tarefa;
                        printf("Fase em Kankan: %d\n",tarefa->fase);
                        printf("Descricao: %s\n",tarefa->descricao);
                        printf("Prioridade: %d\n",tarefa->priority);
                        printf("ID tarefa: %d\n",tarefa->id);

                        printf(" | Data de inicio: %d/%d/%d\n",tarefa->inicio->dia,tarefa->inicio->mes,tarefa->inicio->ano);

                        if(tarefa->prazo  == NULL){
                                printf(" | Prazo Final: (Sem prazo definido)\n");
                        }else{
                                printf(" | Prazo Final: %d/%d/%d\n",tarefa->prazo->dia,tarefa->prazo->mes,tarefa->prazo->ano);
                        }

                        if(tarefa->fim  == NULL){
                                printf(" | Data de fim: (tarefa em progresso)\n");
                        }else{
                                printf(" | Data de fim: %d/%d/%d\n",tarefa->fim->dia,tarefa->fim->mes,tarefa->fim->ano);
                        }

                        if(tarefa->personId == 0 ){
                                printf("Id de trabalhado: (nao atribuido) \n");
                        }else{
                                printf("Id de trabalhado: %d \n",tarefa->personId);
                        }

                       if(tarefa->worker == NULL){
                                printf("Trabalhador encarregue: (ainda sem trabalhador)\n");
                        }else{
                                printf("Trabalhador encarregue: %s\n",tarefa->worker->nome);
                        }
                        printf("__________________________________________________\n\n");
                        act = act->next;
                }

        }

        printf("Pressione Enter para continuar... ");
        getchar();


}

Data *set_data(){ /* Criar uma data */

        Data *nova = (Data *)malloc(sizeof(Data));

        printf("(dd/mm/aaaa) : ");
        scanf("%d/%d/%d",&nova->dia,&nova->mes,&nova->ano);
        getchar();

        return nova;

}

int atribui_tarefa(lista_pessoas lista_p, lista_task lista_t, int *idp){ /*atribuir uma tarefa a um dado trabalhador */

        lista_pessoas act;
        lista_task task;
        lista_task ant;
        int id;
        int got;
        int choice;
        int passed = 0;

        printf("_____Atribuicao de tarefas_____\n\n");

        printf("Vizualizar trabalhadores disponiveis? [ 1 - sim / 0 - nao ]\n->");
        scanf("%d",&choice);
        printf("\n");

        if(choice){
                imprime_lista_pessoas(lista_p);
                printf("\n");
        }

        printf("\nID do trabalhador: ");
        scanf("%d",&id);
        getchar();
        printf("\n");

        got = get_worker(lista_p,&act,id);

        if(got){

                printf("Vizualizar Tarefas disponiveis? [ 1 - sim / 0 - nao ]\n->");
                scanf("%d",&choice);
                printf("\n");

                if(choice){
                        imprime_lista_tarefas(lista_t);
                        printf("\n");
                }

                printf("\nID da tarefa: ");
                scanf("%d",&id);
                getchar();
                printf("\n");

                *idp = id;
                got = get_task(lista_t,&ant,&task, id);

                if(got && act->p->mytasks->n < act->p->max_task){

                        if(task->tarefa->worker == NULL){
                                insere_tarefa(act->p->mytasks,task->tarefa,0);
                                task->tarefa->worker = act->p;
                                task->tarefa->personId=act->p->id;
                                passed = 1;
                        }
                        else if(task->tarefa->worker->id == act->p->id){
                                printf("Esta tarefa ja esta atribuida\n\n");
                        }
                        else if(task->tarefa->worker->id != act->p->id){
                                printf("Esta tarefa ja esta atribuida\n\n");
                        }

                }else if( act->p->mytasks->n > act->p->max_task){
                        printf("\nNumero de tarefas maximo atingido. Tarefa nao associada.\n\n");
                }else{
                        printf("ID errado. Tente novamente.\n\n");
                }

        }else{
                printf("ID errado. Tente novamente.\n\n");
        }

        printf("Pressione Enter para continuar... ");
        getchar();

        return passed;

}

void elimina_no_task(lista_task tarefa, lista_task ant, lista_task act){ /* Função para retirar elemento de uma lista de tarefas */


        tarefa->n--;
        ant->next = act->next;
        printf("\nTarefa eliminada com sucesso.\n\n");



}

void desassocia_tarefa(Task *task){ /* Função principal para desassociar uma tarefa de a um dado trabalhador */

        int found;
        lista_task ante, pos;
        system("cls");

        printf("\n______Desassociar Tarefa______\n\n");

        found = get_task(task->worker->mytasks,&ante,&pos,task->id);

        if(found){
                elimina_no_task(task->worker->mytasks,ante,pos);
                task->worker = NULL;
                task->personId = 0;
                printf("\nTarefa desassociada com sucesso.\n\n");
        }else{

                printf("\nID errado. Tente novamente.\n\n");

        }


        printf("Pressione Enter para continuar... ");
        getchar();

}

void pass_section(lista_task from, lista_task to, lista_pessoas lista_p, int flag, int tipo, int fase){ /*Passagem de tarefas para sectores de KANBAN */

        int id, found, comp, comp2;
        int trys = 0;
        int *idp = (int *)malloc(sizeof(int));

        int passed = 0;

        lista_task ante, pos;

        printf("\n_____Passagem de Sector_____\n\n");

        if(from->next == NULL){
                printf("\nEsta seccao nao tem tarefas disponiveis para passagem\n\n");
        }else{

                if(flag == 1){ /*Somente Adicionar e/ou Retirar trabalhador*/

                       passed = atribui_tarefa(lista_p, from, idp);

                        if(passed){

                                printf("\nProcessando tarefa com ID: %d\n\n",*idp);

                                id = *idp;
                                found = get_task(from,&ante,&pos,id);

                                if(found){

                                        printf("\nAlterar Prazo final ? [ 1 - sim / 0 - nao]\n-> ");
                                        scanf("%d",&passed);

                                        if(passed){

                                                printf("\nNovo prazo final ");

                                                pos->tarefa->prazo = set_data();

                                                while( check_date_erros(pos->tarefa->prazo)){
                                                        printf("Prazo final ");
                                                        pos->tarefa->prazo = set_data();
                                                }

                                                comp = compare_date(pos->tarefa->inicio,pos->tarefa->prazo);  /*Teste de verificação de data*/

                                                while((comp == 0 || comp == 1) && (trys != 3)){
                                                        printf("\nPrazo inserido nao valido. Tente novamente.\n\n");
                                                        printf("Novo Prazo final ");
                                                        pos->tarefa->prazo = set_data();
                                                        comp = compare_date(pos->tarefa->inicio,pos->tarefa->prazo);
                                                        trys++;
                                                }
                                                if(trys == 3){
                                                        printf("\nExcedeu o numero maximo de tentativas para corrigir o erro.\n");
                                                        printf("\nTodas as alteracoes serao revertidas.\n");
                                                }


                                        }

                                        if(tipo == 2){
                                                pos->tarefa->fim = NULL;
                                        }
                                        if(trys != 3){
                                                pos->tarefa->fase = fase;
                                                insere_tarefa(to,pos->tarefa,3);
                                                elimina_no_task(from,ante,pos);
                                        }

                                }
                        }
                        else if(!passed){
                                printf("\nImpossivel mover tarefa para sector uma vez que nao foi associada com sucesso.\n");
                        }
                        else{
                                printf("ID errado. Tente novamente.\n\n");
                        }

                }
                else if(flag == 0){ /* Somente desvincular*/

                        printf("\nVer lista de tarefas disponiveis? [ 1 - sim / 0 - nao]\n-> ");
                        scanf("%d",&passed);
                        getchar();

                        if(passed){
                                imprime_lista_tarefas(from);
                                printf("\n");
                        }

                        printf("ID da tarefa: ");
                        scanf("%d",&id);
                        getchar();
                        found = get_task(from,&ante,&pos,id);

                        printf("%d",found);

                        if(found){

                                if(tipo != 0){   /* Colocar data de conclusao */

                                        printf("\nPor favor indique a data de conclusao da tarefa:\n");
                                        printf("Data de conclusao ");
                                        pos->tarefa->fim = set_data();

                                        while(check_date_erros(pos->tarefa->fim) && trys != 3){
                                                printf("Data de conclusao ");
                                                pos->tarefa->fim = set_data();
                                                trys++;
                                        }

                                        if(trys != 3){

                                                trys = 0;

                                                comp = compare_date(pos->tarefa->prazo,pos->tarefa->fim);
                                                comp2 = compare_date(pos->tarefa->inicio,pos->tarefa->fim);

                                                while(comp2 == 1 || comp == -1){
                                                        printf("\nData de conclusao inserida nao valida. Tente novamente.\n\n");
                                                        printf("Data de conclusao ");
                                                        pos->tarefa->fim = set_data();
                                                        comp = compare_date(pos->tarefa->prazo,pos->tarefa->fim);
                                                        comp2 = compare_date(pos->tarefa->inicio,pos->tarefa->fim);
                                                        trys++;
                                                }
                                                if(trys == 3){
                                                        printf("\nExcedeu o numero maximo de tentativas para corrigir o erro.\n");
                                                        printf("\nTodas as alteracoes serao revertidas.\n");
                                                }else{
                                                        desassocia_tarefa(pos->tarefa);   /* Desvincula trabalhador da tarefa atual */
                                                        pos->tarefa->fase = fase;
                                                        insere_tarefa(to,pos->tarefa,1);
                                                }

                                        }else{

                                                printf("\nExcedeu o numero maximo de tentativas para corrigir o erro.\n");
                                                printf("\nTodas as alteracoes serao revertidas.\n");

                                        }

                                }

                                else if(tipo == 0){
                                        pos->tarefa->fim = NULL;
                                        pos->tarefa->fase = fase;
                                        desassocia_tarefa(pos->tarefa);   /* Desvincula trabalhador da tarefa atual */
                                        insere_tarefa(to,pos->tarefa,2);
                                }
                                if(trys != 3){
                                        elimina_no_task(from,ante,pos);
                                }

                        }else{
                                printf("\nAlgo correu mal. Tente novamente.\n\n");
                        }

                }
        }


        printf("Pressione Enter para continuar... ");
        getchar();

}

int compare_date(Data *d1, Data *d2){ /*Comparar datas*/

        long int ex_d1 = (d1->ano * 10000) + (d1->mes * 100) + d1->dia;
        long int ex_d2 = (d2->ano * 10000) + (d2->mes * 100) + d2->dia;

        int comp = 0;

        if(ex_d1 > ex_d2){
                comp = 1;
        }else if(ex_d1 < ex_d2){
                comp = -1;
        }

        return comp;

}

void switch_worker(lista_task doing , lista_pessoas geral){ /*Alterar trabalhador responsavel por tarefa*/


        int choice, id, found;
        lista_task ante, then;
        lista_pessoas atual;

        system("cls");

        if(doing->next != NULL && geral->next != NULL){

                printf("\nVer todas as tarefas atribuidas? [ 1- sim / 0 - nao ]\n->");
                scanf("%d",&choice);
                getchar();

                if(choice){
                        imprime_lista_tarefas(doing);
                }

                printf("ID da tarefa: ");
                scanf("%d",&id);
                getchar();

                found = get_task(doing,&ante,&then,id);


                if(found){

                        printf("\nVer lista de trabalhadores? [ 1 - sim / 0 - nao ]\n->");
                        scanf("%d",&choice);
                        getchar();
                        if(choice){
                                imprime_lista_pessoas(geral);
                        }

                        printf("ID do trabalhador: ");
                        scanf("%d",&id);
                        getchar();

                        found = get_worker(geral,&atual,id);

                        if(found){

                                if(atual->p->mytasks->n < atual->p->max_task){
                                        desassocia_tarefa(then->tarefa);
                                        elimina_no_task(doing,ante,then);
                                        then->tarefa->worker = atual->p;
                                        then->tarefa->personId = atual->p->id;
                                        insere_tarefa(atual->p->mytasks,then->tarefa,0);
                                        insere_tarefa(doing,then->tarefa,3);

                                }else{
                                        printf("\nEste trabalhador já atingiu o limite maximo de tarefas.\n");
                                }
                        }else{
                                printf("\nAlgo esta errado. Tente novamente.\n\n");
                        }
                }else{
                        printf("\nTarefa nao encontrada.\n");
                }
        }else{
                printf("\nSem tarefas atribuidas.\n");
        }

        printf("Pressione Enter para continuar... ");
        getchar();

}

int check_date_erros(Data *data){ /*Detecao de erros em datas*/

        int error = 0;

         if( (data->dia <= 0 || data->dia > 31) || (data->mes <= 0 || data->mes > 12) || (data->dia > 29 && data->mes == 2 && data->ano % 4 == 0) || (data->dia > 28 && data->mes == 2 && data->ano % 4 != 0)){
                printf("\nData introduzida nao valida. Insira novamente.\n\n");
                error = 1;
        }

        return error;

}

void upload_workers(Pessoa *nova, lista_pessoas lista, lista_pessoas rep){ /* carregamento de trabalhadores em ficheiro */

        lista_pessoas no = (lista_pessoas)malloc(sizeof(P_Node));
        lista_pessoas act = lista->next;
        lista_pessoas then = lista;
        no->p = nova;
        no->n = 0;
        if(lista->next == NULL){

                lista->n++;
                no->next = lista->next;
                lista->next = no;

        }
         else{

                while(act->next != NULL && no->p->id > act->p->id){
                        then = act;
                        act = act->next;
                }
                if(no->p->id < act->p->id){
                        lista->n++;
                        then->next = no;
                        no->next = act;

                }else if(no->p->id == act->p->id){

                        no->next = rep->next;
                        rep->next =no;

                }else{
                        lista->n++;
                        no->next = act->next;
                        act->next = no;
                }
        }

}

void correct_id(lista_pessoas lista, lista_pessoas rep){

        lista_pessoas ante;
        lista_pessoas post;
        lista_pessoas act = rep->next;
        int done = 1;

        while(act !=NULL){
                ante = lista->next;
                post = ante->next;
                while(done != 0 && post->next != NULL){
                        if(act->p->id == post->p->id){
                                act->p->id++;
                                ante = post;
                                post = post->next;
                        }else if(act->p->id > post->p->id){
                                ante = post;
                                post = post->next;
                        }else{
                                rep->next = act->next;
                                ante->next = act;
                                act->next = post;
                                done = 0;
                        }
                }
                if(post->next == NULL && done != 0){
                       if(act->p->id == post->p->id){
                                rep->next = act->next;
                                act->p->id++;
                                act->next = post->next;
                                post->next = act;
                        }else if(act->p->id > post->p->id){
                                rep->next = act->next;
                                act->next = post->next;
                                post->next = act;
                        }else{
                                rep->next = act->next;
                                ante->next = act;
                                act->next = post;
                        }
                }
                act = rep->next;

        }

}

void upload_info(lista_pessoas P_Lista){ /* carregamento de informacao em ficheiro */

        int i , j;
        int max_t;
        FILE *file = fopen("workers.txt","r");
        char *p, *q;
        char line[100];
        char temp[100];
        Pessoa *nova;
        lista_pessoas repetidos = cria_lista_pessoas();

        printf("\n\n____  LOADING INFORMATION ____\n\n");

        if(file == NULL){
                printf("ERROR.");
                exit(1);
        }

        max_t = P_Lista->n_task;

        while( fgets(line,100,file) != NULL ){

                p = line;
                j = 0;
                nova = (Pessoa *)malloc(sizeof(Pessoa));

                while(*p != '\n' && *p != '\0'){
                        q = temp;
                        i = 0;
                        while( *p != ',' && *p != '\n' && *p != '\0'){
                                *q = *p;
                                q++;
                                p++;
                                i++;
                        }
                        if( j == 0 ){
                                nova->nome = (char *)malloc(i*sizeof(char));
                                sprintf(nova->nome,"%s",temp);
                        }else if(j == 1){
                                nova->idade = atoi(temp);
                        }else if(j == 2){
                                nova->mail = (char *)malloc(i*sizeof(char));
                                sprintf(nova->mail,"%s",temp);
                        }else if(j == 3){
                                nova->id = atoi(temp);
                        }
                        j++;
                        memset(temp, 0, sizeof(temp));
                        p++;
                }
                nova->mytasks = cria_lista_tarefas();
                nova->max_task = max_t;
                upload_workers(nova,P_Lista,repetidos);

        }
        correct_id(P_Lista,repetidos);
        imprime_lista_pessoas(P_Lista);
        fclose(file);


}

void put_on_text(lista_pessoas lista){ /* escreve informacao dos trabalhadores em ficheiro em ficheiro*/

        FILE *file = fopen("workers.txt","w");
        char *pos;
        lista_pessoas act = lista->next;
        Pessoa *worker;

        while(act != NULL){

                worker = act->p;


                if ((pos=strchr(worker->nome, '\n')) != NULL)
                        *pos = '\0';
                if ((pos=strchr(worker->mail, '\n')) != NULL)
                        *pos = '\0';

                fprintf(file,"%s,%d,%s,%d,\n",worker->nome,worker->idade,worker->mail,worker->id);
                act = act->next;
        }



        fclose(file);
}

void put_on_text_task(lista_task lista){ /* escreve em ficheiro as tarefas */

        FILE *file = fopen("task.txt","w");
        char *pos;
        lista_task act = lista->next;
        Task *tarefa;

        int id, idperson;
        int diai,mesi,anoi;
        int diaf,mesf,anof;
        int diap,mesp,anop;
        int fase;
        int prio;

        while(act != NULL){

                tarefa = act->tarefa;

                prio = tarefa->priority;
                id = tarefa->id;
                fase = tarefa->fase;
                idperson = tarefa->personId;
                diai = tarefa->inicio->dia;
                mesi = tarefa->inicio->mes;
                anoi = tarefa->inicio->ano;

                diap = tarefa->prazo->dia;
                mesp = tarefa->prazo->mes;
                anop = tarefa->prazo->ano;

                if(tarefa->fim){
                        diaf = tarefa->fim->dia;
                        mesf = tarefa->fim->mes;
                        anof = tarefa->fim->ano;
                }else{
                        diaf = mesf = anof = 0;
                }


                if ((pos=strchr(tarefa->descricao, '\n')) != NULL){
                        *pos = '\0';
                }

                fprintf(file,"%d,%d,%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d,%d\n",id,prio,tarefa->descricao,idperson,diai,mesi,anoi,diaf,mesf,anof,diap,mesp,anop,fase);

                act = act->next;
        }



        fclose(file);

}

Data *translate_date(char *data){

        int dia,mes,ano;
        int i,j = 0;
        int s = 0;
        int comp = strlen(data);
        char *p = data;
        char temp[4];
        Data *d = (Data*)malloc(sizeof(Data));

        for(i = 0; i < comp ; i++){

                if(*p == '/' || p == '\0'){

                        if(s == 0){
                                dia = atoi(temp);
                        }else if(s == 1){
                                mes = atoi(temp);
                        }
                        memset(temp,0,sizeof(temp));
                        j = 0;
                        s++;
                }
                else{
                        temp[j] = *p;
                        j++;
                }
                p++;

        }
        ano = atoi(temp);
        d->dia = dia; d->mes = mes; d->ano = ano;
        return d;
}


void upload_info_task(lista_task T_Lista){ /* carregamento de informacao em ficheiro */

        int i , j = 0;
        int p = 0;
        FILE *file = fopen("task.txt","r");
        char line[100];
        char temp[100];
        char desc[40];
        int comp;
        char *pString;
        Task *task;
        lista_task lista = cria_lista_tarefas();
        lista_task no;

        printf("\n\n____  LOADING INFORMATION ____\n\n");

        if(file == NULL){
                printf("ERROR LOADING FILE.");
                exit(1);
        }

        while( fgets(line,200,file) != NULL ){
                comp = strlen(line);
                p = 0;
                task = (Task*)malloc(sizeof(Task));

                for(i = 0; i < comp-1; i++){
                        j = 0;
                        while(line[i] != ',' && line[i] != '\n' && line[i] != '\0'){
                                temp[j] = line[i];
                                j++;
                                i++;
                        }
                        pString = (char *)malloc(j*sizeof(char));
                        pString = temp;
                        p++;

                        if(p == 1){
                                task->id = atoi(pString);
                        }else if(p == 2){
                                task->priority = atoi(pString);
                        }else if(p == 3){
                                task->descricao  = (char *)malloc(j*sizeof(char));
                                sprintf(task->descricao,"%s",temp);
                        }else if(p == 4){
                                task->personId = atoi(pString);
                        }else  if(p == 5){
                                task->inicio = translate_date(pString);
                        }else  if(p == 6){
                                task->prazo = translate_date(pString);
                        }else  if(p == 7){
                                task->fim = translate_date(pString);
                        }else{
                                task->fase = atoi(pString);
                        }
                        memset(temp,0,sizeof(temp));
                        task->worker = NULL;
                }

                insere_tarefa(T_Lista,task,2);
        }
        imprime_lista_tarefas(T_Lista);
        fclose(file);
}
