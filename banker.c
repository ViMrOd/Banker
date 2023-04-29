#include <stdio.h>

int main()
{
	int alloc[100][100], max[100][100], avail[100]; // Allocate all the arrays
	int rows1, cols1, rows2, cols2, i, j, k;
	
	// Open file
    FILE *fp;
	fp = fopen("state.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
	
	// Read allocation matrix
    fscanf(fp, "%d %d", &rows1, &cols1);
	for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++)
            fscanf(fp, "%d", &alloc[i][j]);
    }
	
	// Read maximum matrix
    fscanf(fp, "%d %d", &rows1, &cols1);
	for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++)
            fscanf(fp, "%d", &max[i][j]);
    }
    
    // Read availiable matrix
    fscanf(fp, "%d", &cols2);
	for (int i = 0; i < cols2; i++)
            fscanf(fp, "%d", &avail[i]);
    
    fclose(fp);
    
    // Initialize finish array all false
    int finish[rows1], ans[rows1], ind = 0;
    for (k = 0; k < rows1; k++)
        finish[k] = 0;
    
    // Calculate need matrix
    int need[rows1][cols1];
    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols1; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    
    int n = 0;
    for (k = 0; k < rows1; k++) {
        for (i = 0; i < rows1; i++) {
            if (finish[i] == 0) {
 				int flag = 0;
                for (j = 0; j < cols1; j++) {
                    if ((need[i][j]) > avail[j]) { //Process needs more than availiable
                    	flag = 1;
                    	break;
                    }
                }
                // If resources are availiable added to answer array to be run
 				if (flag == 0) { 
                    ans[ind++] = i;
                    for (n = 0; n < cols1; n++)
                    	avail[n] += alloc[i][n]; // Reinitializes availiable array
                    finish[i] = 1; // Process finished
                }
            }
        }
    }
	
	// Checks finish see if any false
	int flag = 1;   
	for(int i = 0;i < rows1;i++) {
		if(finish[i] == 0) {
			flag = 0;
         	printf("The following system is not safe");
        	break;
      	}
	}
	
	// Prints safe sequence if exists
	if(flag == 1) {
		printf("Following is the SAFE Sequence\n");
      	for (i = 0; i < rows1 - 1; i++)
        	printf("P%d -> ", ans[i]);
      	printf("P%d ", ans[rows1 - 1]);
    }
    
	printf("\n");
     
    return 0;   
}
