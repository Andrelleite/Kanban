#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void menu(lista_pessoas P_Lista, lista_task T_Lista, lista_task Todo, lista_task Doing, lista_task Done){

        int choice;
        Task *temp;
        system("cls");

        printf("\n\t MAIN MENU\n\n\n______ TRABALHADORES ______\n\n[1] Inserir Pessoa\n[2] Vizualizar Lista de Trabalhadores\n[3] Informacao do trabalhador\n\n");
        printf("______    TAREFAS    ______\n\n[4] Criar Nova Tarefa\n[5] Vizualizar Lista de Tarefas\n[6] Atribuir Tarefa\n[7] Desassociar Tarefa\n\n");
        printf("______ KANBAN STATUS ______\n\n[8] Tarefas na secao To Do\n[9] Tarefas na seccao Doing\n[10] Tarefas na seccao Done\n\n0. Exit\n\n");
        printf("\nOpcao: ");
        scanf("%d", &choice);
        getchar();
        printf("\n");

        switch(choice){
                case 1:
                        insere_pessoa(P_Lista);menu(P_Lista, T_Lista,Todo,Doing,Done);break;
                case 2:
                        imprime_lista_pessoas(P_Lista);menu(P_Lista, T_Lista,Todo,Doing,Done);break;
                case 3:
                        worker_info(P_Lista);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 4:
                        temp = cria_tarefa(T_Lista);
                        insere_tarefa(Todo,temp);
                        menu(P_Lista, T_Lista,Todo,Doing,Done);
                        break;
                case 5:
                        imprime_lista_tarefas(T_Lista);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 6:
                        atribui_tarefa(P_Lista,T_Lista);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 7:
                        desassocia_tarefa(P_Lista,T_Lista);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 8:
                        printf("\n      [To Do Section]\n\n");
                        imprime_lista_tarefas(Todo);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 9:
                        printf("\n      [Done Section]\n\n");
                        imprime_lista_tarefas(Done);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 10:
                        printf("\n      [Doing Section]\n\n");
                        imprime_lista_tarefas(Doing);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 0:
                        break;
                default:
                        menu(P_Lista, T_Lista,Todo,Doing,Done);
        }
}


int main(){

        lista_pessoas P_Lista = cria_lista_pessoas();
        lista_task T_Lista = cria_lista_tarefas();

        lista_task Todo_List = cria_lista_tarefas(); /*Todo Section*/
        lista_task Doing_List = cria_lista_tarefas(); /*Doing Section*/
        lista_task Done_List = cria_lista_tarefas(); /*Done Section*/

        menu(P_Lista, T_Lista, Todo_List, Doing_List, Done_List);

       /* FILE *fich = fopen("workers.txt","w");
        fprintf(fich, "I love cheese");*/

        return 0;
}
