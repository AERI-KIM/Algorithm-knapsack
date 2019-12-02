#include<stdio.h>

int max(int a, int b)
{
    return (a > b)? a : b;
}

int knapsack_basic(int max_weight, int weight[], int value[], int num)
{
    int i, w;
    int B[num+1][max_weight+1];

    //knapsack table 작성
    for(i=0; i<=num; i++){
        for(w=0; w<=max_weight; w++){
            if(i==0 || w==0)
                B[i][w]=0;
            else if(weight[i-1] <= w)
                B[i][w] = max(value[i-1] + B[i-1][w-weight[i-1]], B[i-1][w]);
            else
                B[i][w] = B[i-1][w];
        }
    }

    //knapsack backtracking
    int a=num, b=max_weight;
    while(1){
        if(B[a][b]==0) break; // backtracking 완료
        if(B[a][b] == B[a-1][b])
            a=a-1; // 평행이동한 경우 == 가방에 물건을 넣지 않음
        else{ // 대각선 이동한 경우 == 가방에 물건을 넣음
            printf("%d ", a);
            a=a-1;
            b=b-weight[a];
        }
    }

    return B[num][max_weight];
}

int main()
{
    FILE *f;
    int value[1024], weight[1024];
    int max_weight, index=1, tmp=0;
    char inputfile[40];

    printf("Input file name? ");
    scanf("%s", inputfile);
    f = fopen(inputfile, "rb");

    if(f==NULL){
        printf("Cannot open the input file.\n");
        return 1;
    }
    else{
        while(1){
            fscanf(f, "%d", &tmp);
            if(tmp == -1){
                max_weight = weight[(index-1)/2];
                break;
            }

            if(index%2 != 0) weight[index/2] = tmp;
            else value[(index-1)/2] = tmp;
            index++;
        }
    }

    printf("%d", knapsack_basic(max_weight, weight, value, (index-1)/2));
    return 0;
}



/*
#include <stdio.h>
#include <stdlib.h>


/////////////////////////////////////////////////////////////
// common functions for handling arrays
/////////////////////////////////////////////////////////////

long *readkeys_textfile( const char infile[], int *pN )
  // returns an array of long integers, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  long *A, tmp;
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return NULL;
    }
    else {
      A = (long*)malloc(sizeof(long)*(*pN));
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%ld", &tmp) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return A;
	}
	else A[i] = tmp;
      }
    }
    fclose(fp);
    return A;
  }
}

void savekeys_textfile( const char outfile[], long A[], int N )
  // save the given array of long integers, with its sie N
  // to file whose name given by outfile[]
{
  int i;
  FILE *fp;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file for write %s\n",outfile);
  }
  else {
    // save number of elements
    fprintf(fp, "%d\n",N);
    for (i=0; i<N; i++) fprintf(fp, "%ld ", A[i]);
    fprintf(fp,"\n");
    fclose(fp);
  }
}
*/
/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
/*
int main()
{
  int numElements;
  long *A;	// to store data to be sorted
  // for file name, max length 1023 including path
  char infile[1024], outfile[1024];
  int method;	// which sorting method


  // file name given by keyboard
  printf("Input file name? ");
  scanf("%s",infile);
  printf("Output file name? ");
  scanf("%s",outfile);


  // read text file of integers:
   //* number_of_intergers integer1 integer2 ...
  A = readkeys_textfile(infile, &numElements);

  if ( A != NULL && numElements > 0 ) {

    // save results
    savekeys_textfile(outfile, A, numElements);


    // once allocated, should be freed after use
    free(A);
  }

  return 0;
}
*/
