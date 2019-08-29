#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define SUB_MATRIX_NUM 9

typedef struct{
    int x;
    int y;
    int value;
}params;

int lesudoku[9][9] = {
 {6, 2, 4, 5, 3, 9, 1, 8, 7},
 {5, 1, 9, 7, 2, 8, 6, 3, 4},
 {8, 3, 7, 6, 1, 4, 2, 9, 5},
 {1, 4, 3, 8, 6, 5, 7, 2, 9},
 {9, 5, 8, 2, 4, 7, 3, 6, 1},
 {7, 6, 2, 3, 9, 1, 4, 5, 8},
 {3, 7, 1, 9, 5, 6, 8, 4, 2},
 {4, 9, 6, 1, 8, 2, 5, 7, 3},
 {2, 8, 5, 4, 7, 3, 9, 1, 6},
};

void verificatorL(void* arg);
void verificatorC(void* arg);
void impriminaitor(int lesudoku[9][9]);

//função para capturar os valores de uma submatriz a partir da posicao do valor inicial
int *sub_matrix_catcher(params *init)
{
    int *result = NULL;//resultado inicial
    int parse = sqrt(SUB_MATRIX_NUM);
    //Checagem da posicao, para certificar que esta dentro do range
    if((init -> y <= (SUB_MATRIX_NUM - parse)) 
        && (init -> x <= SUB_MATRIX_NUM - parse)){ 
        int *values = (int *)malloc(sizeof(int) * SUB_MATRIX_NUM);//Alocacao da lista
        int count = 0;
        for(int i = 0;i < parse;i++){
            for(int j = 0;j < parse;j++){
                //Capturando os valores presentes nas posicoes (x + j,y + i)
                values[count] = lesudoku [init-> y + i][init -> x + j];
                count++;
            }
        }
        result = values;
    }
    return result;
}

//Funcao para verificar os valores presentes 
int verify_sub_matrix_values(int list[])
{
    int result = 1;
    if (list == NULL) result = 0;
    else {
        //[a,b,...] -> [a,...,b] -> [...,a,b,...] -> [...,a,...,b] -> ...
        for(int a = 0;a < SUB_MATRIX_NUM;a++){
            if((list[a] > 9) || (list[a] <= 0)){
                result = 0;
                break;
            }
            else {
                for(int b = (a + 1);b < SUB_MATRIX_NUM;b++){
                    if(list[b] == list[a]){
                        result = 0;
                        break;
                    }
                }
            }
        }
    }
    if(result == 1) printf("Valida:");
    else printf("Invalida:");
    return result;
}

//Funcao que reune a captura dos valores da submatriz e a verifica-a
void *matrix_runner(params *pointer){
    int result = 0;
    int parse = sqrt(SUB_MATRIX_NUM);
    int *values = sub_matrix_catcher(pointer);
    result = verify_sub_matrix_values(values);
    printf("(%d %d)\n",(pointer -> y / parse), (pointer -> x / parse));

    free(values);
}


int main(void){

    //Alocando um apontador de posicao do tipo params
    params *pointer = (params *)malloc(sizeof(params));
    //Definindo as coordenadas iniciais
    pointer -> x = 0;
    pointer -> y = 0;
    //Criando uma lista de threads
    pthread_t threads[SUB_MATRIX_NUM];
    //Tid da thread atual
    int thread_response;
    //Posicao que a thread ira ficar na lista
    int count = 0;
    for(int i = 0;i < SUB_MATRIX_NUM;i+=3){
        for(int j = 0;j < SUB_MATRIX_NUM;j+=3){
            //Novas coordenadas
            pointer -> x = j;
            pointer -> y = i;
            //Criacao de uma nova thread com a chamada a uma funcao e passando as coordenadas como argumento
            thread_response = pthread_create(&threads[count],NULL,(void *)matrix_runner,pointer);
            if(thread_response == 0) printf("Thread %d ok -> ",count + 1);
            //Colocando a thread atual para esperar o retorno da ultima
            pthread_join(threads[count++],NULL);
        }
    }


        printf("\n");

        pthread_t thread_L, thread_C;

        pthread_create(&thread_L,NULL,(void *)verificatorL,pointer);
        printf("\n");
        pthread_create(&thread_C,NULL,(void *)verificatorC,pointer);

        pthread_join(thread_L,NULL);
        pthread_join(thread_C,NULL);

    //Terminando a execucao das threads
    pthread_exit(threads);
    //Liberando o ponteiro para as coordenadas
    free(pointer);

    return 0;
}


void verificatorL(void* arg){
        int ehvalida = 1;
        //checa as linhas
        for (int i = 0; i < 9; i++){
                int comparator[9]= {0, 0, 0, 0, 0, 0, 0, 0, 0};
                for (int j = 0; j < 9; j++){
                        if (lesudoku[i][j] < 1 || lesudoku[i][j] > 9){
                                ehvalida = 0;
                        }
                        else{
                                for (int x = 0; x < 9; x++){
                                        if (lesudoku[i][j] == comparator[x]){ 
                                                ehvalida = 0;
                                        }
                                }       
                        }
                        comparator[j] = lesudoku[i][j];    
                }
        }
        if (ehvalida == 0){
                printf("Thread 10: Invalida \n");
        }
        else if (ehvalida == 1){
                printf("Thread 10: Ok \n");
        }
}

void verificatorC(void* arg){
        int ehvalida = 1;
        //checa as colunas
        for (int i = 0; i < 9; i++){
                int comparator[9]= {0, 0, 0, 0, 0, 0, 0, 0, 0};
                for (int j = 0; j < 9; j++){
                        if (lesudoku[j][i] < 1 || lesudoku[j][i] > 9){
                                ehvalida = 0;
                        }
                        else{
                                for (int x = 0; x < 9; x++){
                                        if (lesudoku[j][i] == comparator[x]){  
                                                ehvalida = 0;
                                        }
                                }                             
                        }
                        comparator[i] = lesudoku[j][i];    
                }
        }
        if (ehvalida == 0){
                printf("Thread 11: Invalida \n");
        }
        else if (ehvalida == 1){
                printf("Thread 11: Ok \n");
        }
}
