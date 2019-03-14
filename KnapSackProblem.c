#include<stdio.h>
#include<stdlib.h>

typedef struct   // OBJECT STRUCTURE FOR KNAPSACK BAG
{
    float profit;
    float weight;
    float ppw;

}node;

void heapify(node arr[] , int n , int p)
{
    int gt=p;
    int lc = 2*p+1;
    int rc = 2*p+2;
    if(lc<n && arr[lc].ppw<arr[gt].ppw)
        gt=lc;
    if(rc<n && arr[rc].ppw<arr[gt].ppw)
        gt=rc;
    if(gt!=p)
    {
        node temp = arr[p];
        arr[p] = arr[gt];
        arr[gt] = temp;
        heapify(arr,n,gt);
    }
}
void heap_sort(node arr[] , int n)
{
    int i;
    for(i=(n+1)/2;i>=0;i--)
    {
        heapify(arr,n,i);
    }
    int cs=n;
    while(cs>1)
    {
        node temp = arr[0];
        arr[0] = arr[cs-1];
        arr[cs-1] = temp;
        cs--;
        heapify(arr,cs,0);
    }
}

void KNAPSACK(node arr [] ,int n,float *total_profit , float *capacity)
{
    int i=0;
    while((*capacity)) // WORKING WHILE THERE IS CAPACITY LEFT IN THE BAG
    {
        float temp = *capacity;
        if(temp-arr[i].weight>=0)
        {
            (*capacity)-=arr[i].weight;
            (*total_profit)+=arr[i].profit;
            i++;
            if((*capacity)==0)
            {
                break;
            }
        }
        else
        {
            (*total_profit)+=(*capacity) * arr[i].ppw;
            *capacity =0;
            break;
        }
    }
}

int main()
{
    int n,i;
    float total_profit=0;
    printf("ENTER THE NUMBER OF OBJECTS TO BE FILLED IN THE KNAPSACK\n");
    scanf("%d",&n);
    float capacity;
    printf("ENTER THE CAPACITY OF KNAPSACK\n");
    scanf("%f",&capacity);
    node *arr = (node*)malloc(n*sizeof(node));
    printf("ENTER THE OBJECTS DETAILS : --|PROFIT--WEIGHT|--\n");
    for(i=0;i<n;i++)
    {
        printf("PROFIT : ");
        scanf("%f",&arr[i].profit);
        printf("WEIGHT : ");
        scanf("%f",&arr[i].weight);
        arr[i].ppw = arr[i].profit/arr[i].weight;
    }
    heap_sort(arr,n); // SORTING OBJECTS ACCORDING TO THEIR PROFIT PER WEIGHT
    /*for(i=0;i<n;i++)
    {
        printf("OBJECT : %d PROFIT : %f WEIGHT: %f PPW: %f\n",i+1,arr[i].profit,arr[i].weight,arr[i].ppw);
    }
    */
    KNAPSACK(arr,n,&total_profit,&capacity);

    printf("\n TOTAL PROFIT : %f",total_profit);
    return 0;
}
