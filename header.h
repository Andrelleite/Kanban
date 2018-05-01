#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

/**Lists**/

typedef struct node* lista_task;

typedef struct person_node* lista_pessoas;

/**Stucts**/

typedef struct data{ /*estrutura para datas */

        int dia;
        int mes;
        int ano;

}Data;

typedef struct pessoa{ /*estrutura para trabalhadores*/

        int id;
        char *nome;
        int idade;
        char *mail;
        lista_task mytasks;


}Pessoa;

typedef struct task{ /*estrutura para tarefas*/

        int id;
        int priority;
        Data *inicio;
        Data *fim;
        Data *prazo;
        char *descricao;
        Pessoa *worker;

}Task;

typedef struct node{ /* Lista ligada para tarefas*/

        int n;
        Task *tarefa;
        lista_task next;

}Node;

typedef struct person_node{ /*Lista ligada para pessoas */

        int n;
        Pessoa *p;
        lista_pessoas next;

}P_Node;

/**Function Declarations**/

lista_task cria_lista_tarefas();

lista_pessoas cria_lista_pessoas();

Pessoa *cria_pessoa(lista_pessoas lista);

void cria_tarefa(lista_task lista);

void insere_pessoa(lista_pessoas lista);

void insere_tarefa(lista_task lista, Task *tarefa);

void imprime_lista_pessoas(lista_pessoas lista);

void imprime_lista_tarefas(lista_task lista);

int get_worker(lista_pessoas lista, lista_pessoas *act, int id);

void worker_info(lista_pessoas lista);

Data *set_data();

void atribui_tarefa(lista_pessoas lista_p, lista_task lista_t);

void elimina_no_task(lista_task tarefa, int id);

void desassocia_tarefa(lista_pessoas lista_p, lista_task lista_t);

#endif
