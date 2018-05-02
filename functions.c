#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"


/***

        Todas as funções têm um papel fulcral, sendo que existem algumas que se tornam preponderantes na implementação deste código, uma vez que são utilizadas constantemente
        e até mesmo chamadas pelas outras funções, de modo a tornar o código mais eficiente, mais versátil e mais leve. É importante manter um código bem estruturado para que a sua
        manutenção seja fácil

***/

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

        printf("Prioridade: ");
        scanf("%d",&nova->priority);
        getchar();

        printf("Descricao: ");
        nova->descricao = (char *)malloc(30*sizeof(char));
        fgets(nova->descricao,30,stdin );

        printf("Data de Criacao ");
        nova->inicio = set_data();

        nova->prazo = NULL;
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
                        printf("ID: %d\n",tarefa->id);

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
                                printf("Trabalhador encarregue: %s | ID: %d\n",tarefa->worker->nome,tarefa->worker->id);
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

void atribui_tarefa(lista_pessoas lista_p, lista_task lista_t){ /*atribuir uma tarefa a um dado trabalhador */

        lista_pessoas act;
        lista_task task;
        lista_task ant;
        int id;
        int got;
        int choice;

        printf("_____Atribuicao de tarefas_____\n\n");

        printf("Vizualizar trabalhadores? [ 1 - sim / 0 - nao ]\n->");
        scanf("%d",&choice);
        printf("\n");
        if(choice){
               imprime_lista_pessoas(lista_p);
        }

        printf("\nID do trabalhador: ");
        scanf("%d",&id);
        getchar();
        printf("\n");

        got = get_worker(lista_p,&act,id);

        if(got){

                printf("Vizualizar Tarefas? [ 1 - sim / 0 - nao ]\n->");
                scanf("%d",&choice);
                printf("\n");

                if(choice){
                        imprime_lista_tarefas(lista_t);
                }

                printf("\nID da tarefa: ");
                scanf("%d",&id);
                getchar();
                printf("\n");

                got = get_task(lista_t,&ant,&task, id);

                if(got){

                        if(task->tarefa->worker == NULL){
                                insere_tarefa(act->p->mytasks,task->tarefa);
                                task->tarefa->worker = act->p;
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

}

void elimina_no_task(lista_task tarefa, int id){ /* Função para retirar elemento de uma lista de tarefas */

        lista_task act;
        lista_task ant;
        int found;

        found = get_task(tarefa,&ant,&act,id);

        if(found){
                act->tarefa->worker->mytasks->n--;
                act->tarefa->worker = NULL;
                ant->next = act->next;
                printf("\nTarefa desassociada com sucesso.\n\n");
        }else{

                printf("ID errado. Tente Novamente.\n\n");
        }


}

void desassocia_tarefa(lista_pessoas lista_p, lista_task lista_t){ /* Função principal para desassociar uma tarefa de a um dado trabalhador */

        int id;
        int found;
        lista_pessoas act;

        system("cls");

        printf("\n\n\tDesassociar Tarefa\n\n");
        printf("\n\nID do trabalhador: ");
        scanf("%d",&id);
        getchar();

        found = get_worker(lista_p,&act,id);

        if(found){

                if(act->p->mytasks->n > 0){

                        printf("Visualizar tarefas deste trabalhador? [ 1 - sim / 0 - nao ]\n-> ");
                        scanf("%d",&found);
                        getchar();

                        if(found){
                                imprime_lista_tarefas(act->p->mytasks);
                        }

                        printf("\n\nID da tarefa: ");
                        scanf("%d",&id);
                        getchar();
                        elimina_no_task(act->p->mytasks,id);

                }else{

                        printf("Este trabalhador nao tem tarefas associadas.\n");

                }

        }else{
                printf("ID errado. Tente novamente.\n\n");

        }
        printf("Pressione Enter para continuar... ");
        getchar();

}
