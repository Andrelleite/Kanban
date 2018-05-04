#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void menu(lista_pessoas P_Lista, lista_task T_Lista, lista_task Todo, lista_task Doing, lista_task Done){

        int choice, choice_2;
        Task *temp;
        system("cls");

        printf("\n       | MAIN MENU |\n\n\n______ TRABALHADORES ______\n\n[1] Inserir Pessoa\n[2] Vizualizar Lista de Trabalhadores\n[3] Informacao do trabalhador\n\n");
        printf("______    TAREFAS    ______\n\n[4] Criar Nova Tarefa\n[5] Vizualizar Lista de Tarefas\n\n");
        printf("______ KANBAN STATUS ______\n\n[6] Visualizar todo o quadro\n[7] Tarefas na secao To Do\n[8] Tarefas na seccao Doing\n[9] Tarefas na seccao Done\n\n");
        printf("______KANBAN LISTS OPS______\n\n[10] Mover tarefa em To Do\n[11] Mover tarefa em Doing\n[12] Mover tarefa em Done\n\n[0] Exit\n\n");
        printf("\nOpcao [ ] : ");
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
                        system("cls");
                        printf("\n      [TO DO SECTION]\n\n");
                        imprime_lista_tarefas(Todo);
                        printf("\n      [DOING SECTION]\n\n");
                        imprime_lista_tarefas(Doing);
                        printf("\n      [DONE SECTION]\n\n");
                        imprime_lista_tarefas(Done);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 7:
                        system("cls");
                        printf("\n      [TO DO SECTION]\n\n");
                        imprime_lista_tarefas(Todo);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 8:
                        system("cls");
                        printf("\n      [DOING SECTION]\n\n");
                        imprime_lista_tarefas(Doing);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 9:
                        system("cls");
                        printf("\n      [DONE SECTION]\n\n");
                        imprime_lista_tarefas(Done);
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 10:

                        system("cls");
                        printf("\n     [TO DO] ");
                        printf("\n\nDestino:\n\n[1] Sector Doing\n\n");
                        printf("\nOpcao [ ] : ");
                        scanf("%d", &choice_2);
                        getchar();
                        printf("\n");
                        switch(choice_2){
                                case 1:
                                        printf("\n     [TO DO] -> [DOING]");
                                        printf("\n  *Atribuicao obrigatoria.*\n");
                                        pass_section(Todo,Doing,P_Lista,1);
                                        break;
                                default:
                                        break;
                        }
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;

                case 11:
                        system("cls");
                        printf("\n     [DOING] ");
                        printf("\n\nDestino:\n\n[1] Sector To do\n[2] Sector Done\n\n");
                        printf("\nOpcao [ ] : ");
                        scanf("%d", &choice_2);
                        getchar();
                        printf("\n");
                        switch(choice_2){
                                case 1:
                                        printf("\n     [DOING] -> [TO DO]");
                                        printf("\n  *Desvincula Trabalhador atual.*\n");
                                        break;
                                case 2:
                                        printf("\n     [DOING] -> [DONE]");
                                        printf("\n  *Desvincula Trabalhador atual.*\n");
                                        break;
                                default:
                                        break;
                        }
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 12:
                        system("cls");
                        printf("\n     [DONE] ");
                        printf("\n\nDestino:\n\n[1] Sector To do\n[2] Sector Doing\n\n");
                        printf("\nOpcao [ ] : ");
                        scanf("%d", &choice_2);
                        getchar();
                        printf("\n");
                        switch(choice_2){
                                case 1:
                                        printf("\n     [DONE] -> [TO DO]");
                                        printf("\n  *Atribuicao obrigatoria.*\n");
                                        break;
                                case 2:
                                        printf("\n     [DONE] -> [DOING]");
                                        printf("\n  *Atribuicao obrigatoria.*\n");
                                        break;
                                default:
                                        break;
                        }
                        menu(P_Lista,T_Lista,Todo,Doing,Done);
                        break;
                case 0:
                        printf("**Toda a informacao foi guardada em ficheiros **\n");
                        break;
                default:
                        menu(P_Lista, T_Lista,Todo,Doing,Done);
        }
}

void pont(int *p){

        *p = 5;

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
