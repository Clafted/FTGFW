#include <string>
#include <array>

using namespace std;
class ArrayPractice 
{
    public:
    
    static void selectionSort(int* ar, size_t size)
    {
        int lowestIndex;
        int placeHolder;
        for (int i = 0; i < size; i++)
        {
            lowestIndex = i;
            // Find lowest value from i to ar.size()
            for (int j = i; j < size; j++)
            {
                if (ar[j] < ar[lowestIndex])
                {
                    lowestIndex = j;
                }
            }
            // Switch lowest value with ar[i]
            placeHolder = ar[lowestIndex];
            ar[lowestIndex] = ar[i];
            ar[i] = placeHolder;
        }
    }

    static void mergeSort(int * ar, size_t size, int lowerBound, int upperBound)
    {
        int middle = (lowerBound + upperBound) / 2;                     // Gets the index of the middle on the latter half
        
        int * firstHalf, * secondHalf;
        // Sort both halves of the array
        mergeSort(ar, (size / 2 ) - (size % 2), lowerBound, middle);
        mergeSort(ar, (size / 2), middle, upperBound);

        int iOne = lowerBound, iTwo = middle;
        int sortedArray[size];
        for (int i = 0; i < size; i++)
        {
            if () {

            } else if (ar[iOne] < ar[iTwo]) {
                sortedArray[i] = ar[iOne];
            } else {
                sortedArray[i] = ar[iTwo];
            }
        }
    }
};