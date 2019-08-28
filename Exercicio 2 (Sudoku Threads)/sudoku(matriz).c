#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SUB_MATRIX_NUM 9

typedef struct{
    int x;
    int y;
    int value;
}params;

typedef struct{
    int values[SUB_MATRIX_NUM];
    params start;
    params end;
}sub_matrix;

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

//função para capturar os valores de uma submatriz a partir da posicao do valor inicial
int *sub_matrix_catcher(params *init)
{
    int *result = NULL;//resultado inicial
    int parse = sqrt(SUB_MATRIX_NUM);
    //Checagem da posicao, para certificar que esta dentro do range
    if((init -> y <= (SUB_MATRIX_NUM - parse)) 
        && (init -> x <= SUB_MATRIX_NUM - parse)){ 
        // int values[SUB_MATRIX_NUM]; Causando problemas
        int *values = (int *)malloc(sizeof(int) * SUB_MATRIX_NUM);//Alocacao da lista
        int count = 0;
        for(int i = 0;i < parse;i++){
            for(int j = 0;j < parse;j++){
                values[count] = lesudoku [init-> y + i][init -> x + j];
                count++;
            }
        }
        result = values;
    }
    return result;
}

// //função para capturar os valores de uma submatriz a partir da posicao do valor inicial
// int *sub_matrix_catcher(params *init){
//     int *result = NULL;//resultado inicial
//     //Checagem da posicao, para certificar que esta dentro do range
//     if((init -> y <= (SUB_MATRIX_NUM - 3)) && (init -> x <= SUB_MATRIX_NUM - 3 )){ 
//         params *end = (params *)malloc(sizeof(params));//alocacao de um novo parametro
//         end -> x = (init -> x) + 2;
//         end -> y = (init -> x) + 2;
//         int x = 0,y = 0;
//         int values[9];
//         int count = 0;
//         for(int i = 0;i < 3;i++){
//             for(int j = 0;j < 3;j++){
//                 values[count] = lesudoku [init-> y + i][init -> x + j];
//                 count++;
//             }
//         }
//         result = values;
//         free(end);
//     }
//     return result;
// }

int verify_sub_matrix_values(int list[])
{
    int result = 1;
    if (list == NULL) result = 0;
    else {
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
    return result;
}




int main(void){
    params *test = (params *)malloc(sizeof(params));
    test -> x = 3;
    test -> y = 3;  
    int *list = sub_matrix_catcher(test);
    for(int i = 0; i<9;i++){
        if(list != NULL){
            printf("%d ", list[i]);
        }
    }
    int valid = verify_sub_matrix_values(list); 
    if(valid == 1){
        printf("\n Matriz valida");
    }
    free(test);
    free(list);
    return 0;
}
