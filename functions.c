#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"


/**

        Todas as funções têm um papel fulcral, sendo que existem algumas que se tornam preponderantes na implementação deste código, uma vez que são utilizadas constantemente
        e até mesmo chamadas pelas outras funções, de modo a tornar o código mais eficiente, mais versátil e mais leve. É importante manter um código bem estruturado para que a sua
        manutenção seja fácil

        GitHub -> https://github.com/Andrelleite

        n of functions : 16
        voids : 8
        Task* : 1
        Pessoa* : 1
        Data* :  1
        int: 3

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

        novo->nome = (char *)malloc(10 * sizeof(char));
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
                        printf("Nome: %s | Idade: %d | E-Mail: %s | ID: %d\n__________________________________________________\n\n",pessoa->nome,pessoa->idade,pessoa->mail, pessoa->id);

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
        else if(id >= 0 && id <= lista->n + 1){

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
                        printf("\n      Worker %s\t ID: %d \n",p->nome,p->id);
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

        printf("Prazo final ");
        nova->prazo = set_data();

        nova->fim = NULL;
        nova->worker = NULL;

        printf("ID: %d\n", nova->id);

        printf("Pressione Enter para continuar... ");
        getchar();

        insere_tarefa(lista,nova);

        return nova;
}

void insere_tarefa(lista_task lista, Task *nova){ /* Inserir uma tarefa numa lista ligada */

        lista_task no = (lista_task)malloc(sizeof(Node));
        printf("\nA inserir tarefa...\n");
        no->tarefa = nova;
        no->n = 0;
        lista->n++;

        if(nova != NULL && lista != NULL){

                no->next = lista->next;
                lista->next = no;
                printf("Tarefa inserida.\n");
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

                        printf("Descricao: %s",tarefa->descricao);
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

                       if(tarefa->worker == NULL){
                                printf("Trabalhador encarregue: (ainda sem trabalhador)\n");
                        }else{
                                printf("Trabalhador encarregue: %s | ID trabalhador: %d\n",tarefa->worker->nome,tarefa->worker->id);
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

                if(got){

                        if(task->tarefa->worker == NULL){
                                insere_tarefa(act->p->mytasks,task->tarefa);
                                task->tarefa->worker = act->p;
                                passed = 1;
                        }
                        else if(task->tarefa->worker->id == act->p->id){
                                printf("Esta tarefa ja esta atribuida\n\n");
                        }
                        else if(task->tarefa->worker->id != act->p->id){
                                printf("Esta tarefa ja esta atribuida\n\n");
                        }

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
        act->tarefa = NULL;
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

                printf("\nTarefa desassociada com sucesso.\n\n");
        }else{

                printf("\nID errado. Tente novamente.\n\n");

        }


        printf("Pressione Enter para continuar... ");
        getchar();

}

void pass_section(lista_task from, lista_task to, lista_pessoas lista_p, int flag, int tipo){ /*Passagem de tarefas para sectores de KANBAN */

        int id, found;
        int *idp = (int *)malloc(sizeof(int));
        int passed = 0;
        lista_task ante, pos;
        printf("\n_____Passagem de Sector_____\n\n");

        if(from->next == NULL){
                printf("\nEsta seccao nao tem tarefas disponiveis para passagem\n\n");
        }else{

                if(flag == 1){ /*Somente Adicionar*/

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
                                        }
                                        if(tipo == 2){
                                                pos->tarefa->fim = NULL;
                                        }
                                        insere_tarefa(to,pos->tarefa);
                                        elimina_no_task(from,ante,pos);
                                }
                        }
                        else if(!passed){
                                printf("\nImpossivel mover tarefa para sector uma vez que nao foi associada com sucesso.\n");
                        }
                        else{
                                printf("ID errado. Tente novamente.\n\n");
                        }

                }else if(flag == 0){ /* Somente desvincular*/

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
                        if(found){

                                if(tipo != 0){
                                        printf("\nPor favor indique a data de conclusao da tarefa:\n");
                                        printf("Data de conclusao ");
                                        pos->tarefa->fim = set_data();
                                        desassocia_tarefa(pos->tarefa);
                                }else if(tipo == 0){
                                        pos->tarefa->fim = NULL;
                                }

                                insere_tarefa(to,pos->tarefa);
                                elimina_no_task(from,ante,pos);
                        }else{
                                printf("\nAlgo correu mal. Tente novamente.\n\n");
                        }

                }


        }


        printf("Pressione Enter para continuar... ");
        getchar();

}

