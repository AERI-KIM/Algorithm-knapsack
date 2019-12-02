#include<stdio.h>

double max(double a, double b)
{
    return (a > b)? a : b;
}

double knapsack_basic(int max_index, int max_weight, double weight[], double value[], int num)
{
    int i, w;
    double B[num+1][max_weight+1];

    //knapsack table 작성
    for(i=0; i<=num; i++){
        for(w=0; w<=max_weight; w++){
            if(i==0 || w==0)
                B[i][w]=0;
            else if(weight[i-1] <= w)
                B[i][w] = max(value[i-1] + B[i-1][(int)(w-weight[i-1])], B[i-1][w]);
            else
                B[i][w] = B[i-1][w];
        }
    }

    //knapsack backtracking
    if(max_index != -1){
        int a=num, b=max_weight;
        while(1){
            if(B[a][b]==0) break; // backtracking 완료
            if(B[a][b] == B[a-1][b])
                a=a-1; // 평행이동한 경우 == 가방에 물건을 넣지 않음
            else{ // 대각선 이동한 경우 == 가방에 물건을 넣음
                if(max_index == a) printf("%dx0.5 ", a);
                 else printf("%d ", a);
                a=a-1;
                b=b-weight[a];
            }
        }
    }

    return B[num][max_weight];
}

void split_item(int i, double weight[], double value[])
{
    weight[i-1] = weight[i-1]/2;
    value[i-1] = value[i-1]/2;
}

void recover_item(int i, double weight[], double value[])
{
    weight[i-1] = weight[i-1]*2;
    value[i-1] = value[i-1]*2;
}

int find_max(double value_list[], int num)
{
    double max = value_list[0];
    int max_index = 0;

    for(int i=1; i<=num; i++){
        if(value_list[i] >= max){
            max = value_list[i];
            max_index = i;
        }
    }

    return max_index;
}

double knapsack_one_item_split(int max_weight, double weight[], double value[], int num)
{
    int i, max_index;
    double value_list[num];
    value_list[0] = knapsack_basic(-1, max_weight, weight, value, num); //split하지 않은 경우의 max value

    for(i=1; i<=num; i++){
        split_item(i, weight, value); //i번쨰의 값과 무게를 절반으로 잘라서 리턴
        value_list[i] = knapsack_basic(-1, max_weight, weight, value, num); //-1일 떄는 backtracking을 하지 않음.
        //printf("%.2lf\n", value_list[i]);
        recover_item(i, weight, value); // 쪼갠 것을 다시 복구
    }

    max_index = find_max(value_list, num); // max인 결과값을 가지는 인덱스를 반환

    split_item(max_index, weight, value);
    return knapsack_basic(max_index, max_weight, weight, value, num); //-1이 아닐 떄는 backtracking을 한다.
}


int main()
{
    FILE *f;
    double value[1024], weight[1024];
    int max_weight, index=1;
    double tmp=0;
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
            fscanf(f, "%lf", &tmp);
            if(tmp == -1){
                max_weight = weight[(index-1)/2];
                break;
            }

            if(index%2 != 0) weight[index/2] = tmp;
            else value[(index-1)/2] = tmp;
            index++;
        }
    }

    printf("%.2lf", knapsack_one_item_split(max_weight, weight, value, (index-1)/2));
    return 0;
}
