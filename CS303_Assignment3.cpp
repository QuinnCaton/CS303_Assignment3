#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <time.h>
#include "omp.h"
using namespace std;

void sortBubble(int* arr, int size);
void sortSelection(int* arr, int size);
void sortShell(int* arr, int n);
void quickSort(int arr[], int low, int high, int& swaps);
void mergeSort(int arr[], int l, int r, int& swaps);

void sortBubbleList(list<int>& arr) {
    //initializes iterator points for loop comparisons
    list<int>::iterator start = arr.begin();
    list<int>::iterator end = arr.end();
    for (auto i = start; i != end; i++) {
        for (auto j = start; j != end; ++j) {
            if (*i < *j) { //comparison for data held at iterator location
                iter_swap(i, j); //swap operation for two items in iterator locations
            }
        }
    }
}

int main()
{
    list<int> myList = { 7, 5, 1, 3, 9, 4, 29, 16 };

    sortBubbleList(myList);

    for (auto i = myList.begin(); i != myList.end(); i++) {
        cout << *i << endl;
    }
    cout << endl;
    cout << endl;

    srand(time(0)); //seed for rand() function
    int arr1[1000];
    int arr2[1000];
    int arr3[1000];

#pragma omp parallel for
    for (int j = 0; j < 1000; j++) {
        arr1[j] = rand();
        arr2[j] = rand();
        arr3[j] = rand();
    }

int arrBubble1[1000]; //All of these are for copying the random numbers from
int arrBubble2[1000]; //the base three arrays for use in their corresponding
int arrBubble3[1000]; //sort methods.

int arrSelec1[1000];
int arrSelec2[1000];
int arrSelec3[1000];

int arrShell1[1000];
int arrShell2[1000];
int arrShell3[1000];
    
int arrQuick1[1000];
int arrQuick2[1000];
int arrQuick3[1000];

int arrMerge1[1000];
int arrMerge2[1000];
int arrMerge3[1000];

//This omp section copies the data into the new arrays
#pragma omp parallel for
    for (int i = 0; i < 1000; i++) {
        arrBubble1[i] = arr1[i];
        arrBubble2[i] = arr2[i];
        arrBubble3[i] = arr3[i];

        arrSelec1[i] = arr1[i];
        arrSelec2[i] = arr2[i];
        arrSelec3[i] = arr3[i];

        arrShell1[i] = arr1[i];
        arrShell2[i] = arr2[i];
        arrShell3[i] = arr3[i];

        arrQuick1[i] = arr1[i];
        arrQuick2[i] = arr2[i];
        arrQuick3[i] = arr3[i];

        arrMerge1[i] = arr1[i];
        arrMerge2[i] = arr2[i];
        arrMerge3[i] = arr3[i];
    }

sortBubble(arrBubble1, 1000);
sortBubble(arrBubble2, 1000);
sortBubble(arrBubble3, 1000);

sortSelection(arrSelec1, 1000);
sortSelection(arrSelec2, 1000);
sortSelection(arrSelec3, 1000);

sortShell(arrShell1, 1000);
sortShell(arrShell2, 1000);
sortShell(arrShell3, 1000);

int q1 = 0;
int q2 = 0;
int q3 = 0;
quickSort(arrQuick1, 0, 999, q1);
cout << "Quick swaps: " << q1 << endl;
quickSort(arrQuick2, 0, 999, q2);
cout << "Quick swaps: " << q2 << endl;
quickSort(arrQuick3, 0, 999, q3);
cout << "Quick swaps: " << q3 << endl;

int m1 = 0;
int m2 = 0;
int m3 = 0;
mergeSort(arrMerge1, 0, 999, m1);
cout << "Merge swaps: " << m1 << endl;
mergeSort(arrMerge2, 0, 999, m2);
cout << "Merge swaps: " << m2 << endl;
mergeSort(arrMerge3, 0, 999, m3);
cout << "Merge swaps: " << m3 << endl;

    
return 0;
}

void sortBubble(int* arr, int size) {
    int swaps = 0;
    for (int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < (size - i - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++; //counter
            }
        }
    }
    cout << "Bubble swaps: " << swaps << endl;
}

void sortSelection(int* arr, int size) {
    int swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        int min = arr[i];
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            swaps++; //counter
        }
    }
    cout << "Selection swaps: " << swaps << endl;
}

void sortShell(int* arr, int n) {
    int swaps = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                swaps++; //counter
            }
            arr[j] = temp;
        }
    }
    cout << "Shell swaps: " << swaps << endl;
}

void swap(int& x, int& y) {
    int temp = y;
    y = x;
    x = temp;
}
int partition(int arr[], int low, int high, int& swaps) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
            swaps++; //counter
        }
    }
    swap(arr[i + 1], arr[high]);
    swaps++; //counter
    return (i + 1);
}
void quickSort(int arr[], int low, int high, int& swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, swaps);
        quickSort(arr, low, pi - 1, swaps);
        quickSort(arr, pi + 1, high, swaps);
    }
}

void merge(int arr[], int l, int m, int r, int& swaps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    /* create temp arrays */
    int* L = new int[n1];
    int* R = new int[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
            swaps++; //counter
        }
        else
        {
            arr[k] = R[j];
            j++;
            swaps++; //counter
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        swaps++; //counter
    }
    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        swaps++; //counter
    }
    delete[] L;
    delete[] R;
}
void mergeSort(int arr[], int l, int r, int& swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, swaps);
        mergeSort(arr, m + 1, r, swaps);
        merge(arr, l, m, r, swaps);
    }
}

