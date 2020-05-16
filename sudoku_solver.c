#include <stdio.h>
#include <stdlib.h>

int is_exist_row(int grid[9][9], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_col(int grid[9][9], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (grid[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int is_exist_box(int grid[9][9], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

int is_safe_num(int grid[9][9], int row, int col, int num) {
	return !is_exist_row(grid, row, num) 
			&& !is_exist_col(grid, col, num) 
			&& !is_exist_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[9][9], int *row, int *col) {
	for (*row = 0; *row < 9; (*row)++) {
		for (*col = 0; *col < 9; (*col)++) {
			if (grid[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int grid[9][9]) {
	
	int row = 0;
	int col = 0;
	
	if (!find_unassigned(grid, &row, &col)){
		return 1;
	}
	
	for (int num = 1; num <= 9; num++ ) {
		
		if (is_safe_num(grid, row, col, num)) {
			grid[row][col] = num;
			
			if (solve(grid)) {
				return 1;
			}
			
			grid[row][col] = 0;
		}
	}
	
	return 0;
}

void displayGrid(int grid[9][9])
{
    int i,j,k;
    printf("\n\n");
    for(k = 0; k < 9; k++)
    {
       printf(" ___ ");
    }
    printf("\n\n");
    for (i = 0 ; i < 9; i++)
    {
        printf("| ");
        for(j = 0; j < 9 ; j++)
        {
            printf("%d ", grid[i][j]);
            if((j+1)%3==0)
            {
                printf(" | ");
            }
            else
            {
                printf("   ");
            }
        }
        if((i+1)%3==0)
        {
            printf("\n");
            for(k = 0; k < 9; k++)
            {
                printf(" ___ ");
            }
            printf("\n\n");
        }
        else
        {
            printf("\n\n");
        }
    }
}

int main()
{
    printf("WELCOME TO SUDOKU SOLVER\n\n");
    int grid[9][9];
    int i, j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            retry:printf("Enter the data at postion %d:%d = ", i+1, j+1);
            scanf("%d", &grid[i][j]);
            system("clear");
            if(grid[i][j]>10){
                printf("ERROR : VALUE ENTERED IS INCORRECT ");
                goto retry;
            }
        }
    }
    printf("\nPUZZLE ENTERED AS : ");
    displayGrid(grid);
    printf("\nSOLUTION : ");
    if(solve(grid))
    {
        displayGrid(grid);
    }
    else
    {
        printf("UNSOLVABLE\n\n");
    }
    return 0;
}

