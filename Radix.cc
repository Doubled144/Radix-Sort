/************************************************************//*
  Filename   : Radix.cc
  Author     : Dominic J. DuRant
  Course     : CSCI 362-01
  Assignment : 6
  Description: This program is meant to test the time of Radix sort against
              the standard sort. The complexity of Radix is O(d*N) while 
              std sort is O(nlgn). 
*/

/************************************************************/
// System includes

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include <random>
#include <bits/stdc++.h>

/************************************************************/
// Local includes
#include "Timer.hpp"

/************************************************************/
// Using declarations

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::minstd_rand;
using std::uniform_int_distribution;
using std::queue;
using std::setprecision;
using std::fixed;
using std::sort;

/************************************************************/
// Function prototypes/global vars/typedefs

//Sorting for Radix Algorithm
void
radixSort (vector<int>& v, int d);

//Compares the initial vector to the standard
//  sort and prints if Radix was sorted correctly. 
void
compare (vector<int>& v, vector<int>& Acopy);

//Add random numbers (according to the seed) to the initial vector
void 
addNum (vector<int>& v, int d);

//Return the time in (ms) for Radix Sort
double
timeRadix (vector<int>& v, int d);

//Return the time in (ms) for Radix Sort
double
timeStandard (vector<int>& Acopy);

/************************************************************/

int
main (int argc, char* argv[])
{ 
  size_t N; //number of integers to sort.
  int d; //maximum number of digits in a number.
  

  cout << "N ==> ";
  cin  >> N;
  cout << "d ==> ";
  cin  >> d;
  cout << endl;
  
  vector<int> v(N);  
  addNum (v, d);

  cout << "Radix time:     " << fixed << setprecision(2) << timeRadix (v, d) << " ms" << endl;

  vector<int> Acopy (v); 
  cout << "std::sort time: " << timeStandard (Acopy) << " ms" << endl;
  cout << endl;

  compare (v, Acopy);

  return EXIT_SUCCESS;
}

/************************************************************/

void
radixSort (vector<int>& v, int d)
{
  queue <int> arrQueue [10];

  int max = 10;
  int min = 1;
  
  //push values into queue for sorting
  for (int a = 0; a < d; ++a)
  {
    for (size_t i = 0; i < v.size (); ++i)
    { 
      int point = v[i];        
      arrQueue[(point % max) / min].push (point);       
    }
  
    size_t i = 0;
    //add values back to vector
    for (int j = 0; j < 10; ++j)
    {
       while (!arrQueue[j].empty ())
       {
          v[i] = arrQueue[j].front ();
          arrQueue[j].pop ();
          ++i;
       }
    }
    max *= 10;
    min *= 10;
  }
}
   
/************************************************************/

void
compare (vector<int>& v, vector<int>& Acopy)
{
  if (v == Acopy)
  {
    cout << "Sort ok?    yes\n";
  }
  else
  {
    cout << "Sort ok?    no\n";
  }   
}

/************************************************************/
void 
addNum (vector<int>& v, int d)
{
  minstd_rand gen (0);
  uniform_int_distribution<int> distribution(0, pow (10, d) - 1);
  
  for (size_t i = 0; i < v.size (); ++i)
  {
    v[i] = distribution(gen);
  }
}

/************************************************************/
double
timeRadix (vector<int>& v, int d)
{
  Timer <> stopWatch; 

  radixSort (v, d);
  
  stopWatch.stop ();

  return stopWatch.getElapsedMs ();
}

/************************************************************/
double
timeStandard (vector<int>& Acopy)
{
  Timer <> stopWatch;
  sort (Acopy.begin (), Acopy.end ());
  stopWatch.stop ();

  return stopWatch.getElapsedMs ();
}
/*
N      d=2      d=4       d=8        std(d=8)    
====   ======   ======    ======     ========   
100e6  1717.76  3504.62   7093.02    1874.47
200e6  3445.99  7230.46   13223.78   4032.19
400e6  7499.70  13417.63  26386.92   7491.50
*/

/* 
Discussion
==========
The time for radix sort is consistent with the complexity O(d*N). 
However, it is still slower than the standard library sorting.
Radix sort should win every case but fails to do so with
the randomly genrated numbers from the seed.  
I beleive it is slower either because implementation or the std sort is optimized
to be faster in every case.  
*/