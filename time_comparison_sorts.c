#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;

ll arr[1000000];

void swap(ll *p, ll *q)
{
    ll x = *p;
    *p = *q;
    *q = x;
}

/// MERGE SORT
void merge(ll *arr, ll p, ll q, ll r)
{
    ll n1 = q - p + 1;
    ll n2 = r - q;

    ll left[n1 + 1];
    ll right[n2 + 1];

    for (ll i = 0; i < n1; i++)
        left[i] = arr[p + i];

    for (ll j = 0; j < n2; j++)
        right[j] = arr[q + j + 1];

    left[n1] = 999999999999999999;
    right[n2] = 999999999999999999;

    ll i = 0, j = 0;

    for (ll k = p; k <= r; k++)
    {
        if (left[i] < right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
    }
}

void mergeSort(ll *arr, ll p, ll r)
{
    if (p < r)
    {
        ll q = (p + r) / 2;

        //recursively divide

        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);

        //recursively merge and sort
        merge(arr, p, q, r);
    }
}

/// QUICK SORT
ll partition(ll *arr, ll low, ll high)
{
    ll pivot = arr[high];
    ll i = (low - 1);

    for (ll j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(ll *arr, ll low, ll high)
{
    if (low < high)
    {
        ll pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/// HEAP SORT
void heapify(ll *arr, ll n, ll i)
{
    ll largest = i;
    ll l = 2 * i + 1;
    ll r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ll *arr, ll n)
{
    for (ll i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (ll i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// void printArray(ll *arr, ll n)
// {
//     for (ll i = 0; i < n; ++i)
//         printf("%lld\t", arr[i]);
//     printf("\n");
// }

int main()
{

    srand(time(0));

    ll n = 10;

    FILE *fp;

    fp = fopen("q1_plot_c.txt", "w");

    if(fp == NULL){
        printf("ERROR Opening File.\n");
    }

    double merge_sort_time, quick_sort_time, heap_sort_time, mst, qst, hst;

    while (n <= 1000000)
    {
        mst = qst = hst = 0.0;

        // ll arr[n];

        clock_t time;

        for (int k = 1; k <= 10; k++)
        {
            for (ll i = 0; i < n; i++)
            {
                arr[i] = rand();
            }

            ///MERGE SORT BEGINS
            time = clock();
            ///START
            mergeSort(arr, 0, n - 1);
            ///END
            time = clock() - time;
            ///MERGE SORT ENDS
            mst += ((double)time) / CLOCKS_PER_SEC;
        }
        merge_sort_time = mst / 10;

        for (int k = 1; k <= 10; k++)
        {
            for (ll i = 0; i < n; i++)
            {
                arr[i] = rand();
            }

            ///QUICK SORT BEGINS
            time = clock();
            ///START
            quickSort(arr, 0, n - 1);
            ///END
            time = clock() - time;
            ///QUICK SORT ENDS
            qst += ((double)time) / CLOCKS_PER_SEC;
        }
        quick_sort_time = qst / 10;

        for (int k = 1; k <= 10; k++)
        {
            for (ll i = 0; i < n; i++)
            {
                arr[i] = rand();
            }

            ///HEAP SORT BEGINS
            time = clock();
            ///START
            heapSort(arr, n);
            ///END
            time = clock() - time;
            ///HEAP SORT ENDS
            hst += ((double)time) / CLOCKS_PER_SEC;
        }
        heap_sort_time = hst / 10;
        
        fprintf(fp, "%lld, %lf, %lf, %lf\n", n, merge_sort_time, quick_sort_time, heap_sort_time);
        
        n *= 10;
    }

    fclose(fp);

    return 0;
}
