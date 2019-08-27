#include <stdio.h>
#include <stdlib.h>

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

void impriminaitor(int matrix[9][9]);
void verificar(int matrix[9][9]);
 
int main()
{
        impriminaitor(lesudoku);
        printf("\n");
		verificar(lesudoku);
}

void impriminaitor(int matrix[9][9]){
        for (int i = 0; i < 9; i ++){
                for (int j = 0; j < 9; j++){
                        printf("%i ", matrix[i][j]);
                }
                printf("\n");
        }
}

void verificar(int matrix[9][9]){
	int validar;
	int comparar[3][3] ={0,0,0,0,0,0,0,0,0};
		for (int i = 0; i < 3; i ++){
                for (int j = 0; j < 3; j++){
                        if (matrix[i][j] < 1 || matrix[i][j] > 9){
                                validar = 0;
                        }
                        else{
                                for (int x = 0; x < 9; x++){
									for(int y = 0; y < 9; y++){
                                        if (matrix[i][j] == comparar[x][y]){ 
                                                validar = 1;
                                        }}
                                }       
                }

}
}
 if (validar == 0){
                printf("A matriz não é válida!");
        }
        else if (validar == 1){
                printf("A matriz é válida!");
        }
}
