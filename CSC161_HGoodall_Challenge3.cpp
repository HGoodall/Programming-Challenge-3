/* CSC161_HGoodall_Challenge3.cpp : This Program finds how many comparisons are made when sorting an array using a selection sortand quick sort algorithm, then calculatesand displays the average comparisons made in 100 loops.Then the average comparisons in 1000 loops are found in a binary search and sequential search.
* Author: Hannah Goodall
* Date: 3/14/2022
* Computer Science II
*/

#include <iostream>
#include <chrono>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

void shuffleArray(int arr[], int size);
int selectionSort(int arr[], int length);
int quickSort(int arr[], int size, int &count);
int partition(int arr[], int first, int last, int &counter);
void swap(int arr[], int first, int second);
int recQuickSort(int arr[], int first, int last, int &counter);
void print(int arr[], int size);
int seqSearch(int arr[], int size, int target);
int binarySearch(int arr[], int size, int target);

void main()
{
    const int SIZE = 100;
    const int SEARCHSIZE = 1000;
    int arr1[SIZE];
    int arr2[SIZE];
    int arr3[SEARCHSIZE];
    int arr4[SEARCHSIZE];

    //create initial array for sort algorithms. nums 1-100
    for (int i = 0; i < SIZE; i++) {
        arr1[i] = i + 1;
    }
    cout << endl;

    //count and calculate average num of comparisons in selection and quick sort
    int total1 = 0, total2 = 0, average1, average2;

    for (int i = 0; i < SIZE; i++) {
        int counter = 0;
        shuffleArray(arr1, SIZE);
        //make a copy of arr1 to arr2
        for (int i = 0; i < SIZE; i++) {
            arr2[i] = arr1[i];
        }
        total1 += selectionSort(arr1, SIZE);
        total2 += quickSort(arr2, SIZE, counter);
       
    }
    //display averages for selection sort and quick sort
    average1 = total1 / SIZE;
    cout << "Average comparisons in Selection Sort: " << average1 << endl;
    average2 = total2 / SIZE;
    cout << "Average comparisons in Quick Sort: " << average2 << endl;


    //create initial array for search algorithms. nums 1-1000
    for (int i = 0; i < SEARCHSIZE; i++) {
        arr3[i] = i + 1;
    }

    //count and calculate average num of comparisons in sequential and binary search
    int total3 = 0.0, total4 = 0.0, average3, average4;
    for (int i = 0; i < SEARCHSIZE; i++) {
        shuffleArray(arr3, SEARCHSIZE);
        //make a copy of arr3 to arr4
        for (int i = 0; i < SEARCHSIZE; i++) {
            arr4[i] = arr3[i];
        }
        total3 += seqSearch(arr3, SIZE, i);
        total4 += binarySearch(arr4, SIZE, i);

    }
    //display averages
    average3 = total3 / SIZE;
    cout << "Average comparisons in Sequential Search: " << average1 << endl;
    average4 = total4 / SIZE;
    cout << "Average comparisons in Binary Search: " << average2;

  
}

void shuffleArray(int arr[], int size) {

    srand(duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
    for (int i = 0; i < size; i++) {
        int index = rand() % size;
        swap(arr, i, index);
    }

}

//modify selection sort to return number of comparisons performed.
int selectionSort(int arr[], int length) {
    int count = 0;
    for (int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
                count++;
            }
        }
        swap(arr, i, min_index);
    }
    return count;

}
int quickSort(int arr[], int size, int &count) {
    recQuickSort(arr, 0, size - 1, count);
    return count;
}

int recQuickSort(int arr[], int first, int last,int &counter) {
    int pivotLocation;

    if (first < last) {
        pivotLocation = partition(arr, first, last, counter);
        recQuickSort(arr, first, pivotLocation - 1, counter);
        recQuickSort(arr, pivotLocation + 1, last, counter);  
    }
    return counter;
}

int partition(int arr[], int first, int last,int &counter) {
    
    int pivot, smallIndex;

    swap(arr, first, (first + last) / 2);
    pivot = arr[first];
    smallIndex = first;
    
    for (int index = first + 1; index <= last; index++) 
        if (arr[index] < pivot) {
            counter++;
            smallIndex++;
            swap(arr, smallIndex, index); 
        }
    swap(arr, first, smallIndex);
   
    
    return smallIndex;
    
}


void swap(int arr[], int first, int second) {
    int temp;

    temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}
//sequential search
int seqSearch(int arr[], int size, int target) {
    int index = 0, count = 0;

    for(int i = 0; i < size; i++) {
        count++;
        if (arr[index] == target)
            break;
    }
    return count;
}

int binarySearch(int arr[], int size, int target) {
    int start = 0;
    int end = size - 1;
    int mid;
    int count = 0;

    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid] == target) {
            return count++;
        }
        else if (arr[mid] > target) {
            count++;
            end = mid - 1;
        }
        else {
            count++;
            start = mid + 1;
        }
    }
    return count;
}
void print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}