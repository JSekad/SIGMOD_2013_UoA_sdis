#include "../../include/distance.h"
#include <stdlib.h>
#include <math.h>
#include "string.h"

#define MFUNC(a,b,c) fmin(fmin(a,b),c)



int editDistance(char* a,char* b)
{
    int length_a=strlen(a);
    int length_b=strlen(b);
    int arr[length_a + 1][length_b + 1];//array to store results
    for(int i=0 ; i <=length_a ; i++)
    {
        for(int j=0 ; j<=length_b ; j++)
        {
            if(i == 0)
            {
                arr[i][j] = j;
            }
            else if(j == 0)
            {
                arr[i][j] = i;
            }
            else if(a[i-1] == b[j-1])
            {
                arr[i][j]=arr[i-1][j-1];
            }
            else
            {
                arr[i][j]=1 + MFUNC(arr[i][j-1],arr[i-1][j],arr[i-1][j-1]);
            }
        }
    }
    return arr[length_a][length_b];
}

