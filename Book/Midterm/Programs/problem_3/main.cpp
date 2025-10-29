/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Modified By: John Huynh
 * Purpose:  Driver program to test out the statistics problem.
 */

//Libraries
#include <iostream>//I/O
using namespace std;

//User Libraries
#include "Array.h"
#include "Stats.h"

//No Global Constants

//Function Prototypes I supply
Array *fillAry(int,int);        //Fill an array and put into a structure
void prntAry(const Array *,int);//Print the array 
int *copy(const int *,int);     //Copy the array
void mrkSort(int *,int);        //Sort an array
void prtStat(const Stats *);    //Print the structure
void rcvrMem(Array *);          //Recover memory from the Array Structure
void rcvrMem(Stats *);          //Recover memory from Statistics Structure

//Functions you are to supply
Stats *stat(const Array *);     //Find & store mean, median, & modes in structure

//Execution begins here
int main(int argc, char*argv[]) {
    //Declare variables
    int arySize;//Array Size
    int modNum; //Number to control the modes (digits 0 to 9 allowed)
    Array *array;
    
    //Input the size and mod number
    cout<<"This program develops an array to be analyzed"<<endl;
    cout<<"Array size from mod number to 100"<<endl;
    cout<<"Mod number from 2 to 10"<<endl;
    cout<<"Input the Array Size and the mod number to be used."<<endl;
    cin>>arySize>>modNum;
    cout<<endl<<endl;
    
    //Fill the array
    array=fillAry(arySize,modNum);
    
    //Print the initial array
    cout<<"Original Array before sorting"<<endl;
    prntAry(array,10);
    
    //Sort the array
    mrkSort(array->data,array->size);
    cout<<"Sorted Array to be utilize for the stat function"<<endl;
    prntAry(array,10);
    
    //Calculate some of the statistics
    Stats *stats=stat(array);
    
    //Print the statistics
    prtStat(stats);
    
    //Recover allocated memory
    rcvrMem(array);
    rcvrMem(stats);
    
    //Exit stage right
    return 0;
}

int *copy(const int *a,int n){
    //Declare and allocate an array
    //that is a c
    int *b=new int[n];
    //Fill
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    //Return the copy
    return b;
}

void prtStat(const Stats *ary){
    cout<<endl;
    cout<<"The average of the array = "<<ary->avg<<endl;
    cout<<"The median of the array  = "<<ary->median<<endl;
    cout<<"The number of modes      = "<<
            ary->mode->size<<endl;
    cout<<"The max Frequency        = "<<
            ary->modFreq<<endl;
    if(ary->mode->size==0){
        cout<<"The mode set             = {null}"<<endl;
        return;
    }
    cout<<"The mode set             = {";
    for(int i=0;i<ary->mode->size-1;i++){
        cout<<ary->mode->data[i]<<",";
    }
    cout<<ary->mode->data[ary->mode->size-1]<<"}"<<endl;
}

void mrkSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(array[j]<array[i]){
                int temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
}

void rcvrMem(Stats *stats){
    rcvrMem(stats->mode);
    delete stats;
}

void rcvrMem(Array *array){
    delete []array->data;
    delete array;
}

void prntAry(const Array *array,int perLine){
    //Output the array
    for(int i=0;i<array->size;i++){
        cout<<array->data[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

Array *fillAry(int n, int modNum){
    //Allocate memory
    Array *array=new Array;
    array->size=n;
    array->data=new int[array->size];
    
    //Fill the array with mod numbers
    for(int i=0;i<n;i++){
        array->data[i]=i%modNum;
    }
    
    //Exit function
    return array;
}

Stats *stat(const Array *array){
    
    // Grab Array Size and Data

    const int size = array->size;
    const int *data = array->data;

    // Create a structure to house the calculated results

    Stats *results = new Stats;

    results->mode = new Array;
    results->mode->size = 0;
    results->mode->data = nullptr;

    // Calculate the mean by summing the data and dividing by size

    float total = 0.0;

    for (int i = 0; i < size; ++i) {

        total += data[i];

    }

    results->avg = total / size;

    // Find the middle number in sorted result array

    if (size % 2 == 0) {

        results->median = (data[size / 2 - 1] + data[size / 2]) / 2;

    } else {

        results->median = data[size / 2];

    }

    // Set initial mode values

    int maxFrequency = 1;
    int currentCount = 1;

    // Set max frequency by comparing current to previous value

    for (int i = 1; i <= size; ++i) {

        if (data[i] == data[i - 1]) {

            ++currentCount;

        } else {

            if (currentCount > maxFrequency) {

                maxFrequency = currentCount;

            }

            currentCount = 1;

        }
    }

    results->modFreq = maxFrequency;

    // If no unqiue values, then no mode is in set

    if (maxFrequency == 1) {

        results->mode->size = 0;
        results->mode->data = nullptr;

        return results;

    }

    // Identify the number of sets match the mode value

    int modeCount = 0;
    currentCount = 1;

    for (int i = 1; i <= size; ++i) {
    
        if (data[i] == data[i - 1]) {
    
            ++currentCount;
    
        } else {
    
            if (currentCount == maxFrequency) {

                ++modeCount;

            }

            currentCount = 1;
        
        }

    }

    // Allocate and collect the mode values
    
    results->mode->size = modeCount;
    results->mode->data = new int[modeCount];

    // Collect the mode sets together

    int modeIndex = 0;
    currentCount = 1;

    for (int i = 1; i <= size; ++i) {

        if (data[i] == data[i - 1]) {

            ++currentCount;

        } else {

            if (currentCount == maxFrequency) {

                // Store the value of the data (number) being collected 
                results->mode->data[modeIndex++] = data[i - 1];

            }

            currentCount = 1;

        }

    }

    return results;
}
