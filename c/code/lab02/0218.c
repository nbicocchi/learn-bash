#include <stdio.h>

/*
 * Merges two subarrays of arr[].
 * First subarray is arr[l..m], second subarray is arr[m+1..r]
 */
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r] */
    i = 0; /* Initial index of first subarray */
    j = 0; /* Initial index of second subarray */
    k = l; /* Initial index of merged subarray */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*
 * l is for left index and r is right index of the
 * sub-array of arr to be sorted
 */
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        /* Same as (l+r)/2, but avoids overflow for large l and h */
        int m = l + (r - l) / 2;

        /* Sort first and second halves */
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/* Function to print an array */
void show_array(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("[%d] %d\n", i, arr[i]);
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    show_array(arr, n);
    merge_sort(arr, 0, n - 1);
    show_array(arr, n);
}
