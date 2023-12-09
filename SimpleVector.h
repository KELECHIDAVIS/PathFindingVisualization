//User Libraries
// SimpleVector class template
#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
using namespace std;

template <class T>
class SimpleVector
{
private:
   T *aptr;          // To point to the allocated array
   int arraySize;    // Number of elements in the array
   void memError();  // Handles memory allocation errors
   void subError();  // Handles subscripts out of range

public:
   // Default constructor
   SimpleVector()
      { aptr = 0; arraySize = 0;}
      
   // Constructor declaration
   SimpleVector(int);
   
   // Copy constructor declaration
   SimpleVector(const SimpleVector &);
   
   // Destructor declaration
   ~SimpleVector();
   
   // Accessor to return the array size
   int size() const
      { return arraySize; }

   // Accessor to return a specific element
   T getElementAt(int position);

   // Overloaded [] operator declaration
   T &operator[](const int &);
   
   //Adding 4 functions Push front/back, Pop front/back
   void pshFrnt(T);
   void pshBack(T);
   T popFrnt();
   T popBack();
};

//*******************************************
//Student to code these functions
//*******************************************

template <class T>
void SimpleVector<T>::pshFrnt(T val)
{
    //Student Code Here
    
    // create a new arr with val at its front
    T* newArray= new T[this->arraySize+1]; 
    newArray[0] = val; 
    
    // now fill new newArray with original's data 
    for(int i =0 ; i< this->arraySize; i++)
    {
        newArray[i+1] = this->aptr[i]; 
    }
    
    // now deallocate memory used for aptr
    delete [] this->aptr; 
    
    // now give aptr the new arrays value; 
    
    this->aptr = newArray; 
    
    //increment array's size now 
    this->arraySize++; 
}


template <class T>
void SimpleVector<T>::pshBack(T val)
{
   //Student Code Here
   
    // create a new arr with val at its end
    T* newArray= new T[this->arraySize+1]; 
    newArray[this->arraySize] = val; 
    
    // now fill new newArray with original's data 
    for(int i =0 ; i< this->arraySize; i++)
    {
        newArray[i] = this->aptr[i]; 
    }
    
    // now deallocate memory used for aptr
    delete [] this->aptr; 
    
    // now give aptr the new arrays value; 
    
    this->aptr = newArray; 
    
    //increment array's size now 
    this->arraySize++; 
}

template <class T>
T SimpleVector<T>::popFrnt()
{
   //Student Code Here
   // very similar to what we did earlier 
   
   
   // create a new arr with one less size 
    T* newArray= new T[this->arraySize-1]; 
     
    
    // now fill new newArray with original's data; skip the first one 
    for(int i =1 ; i< this->arraySize; i++)
    {
        newArray[i-1] = this->aptr[i]; 
    }
    
    // store item that was lost for returning 
    T poppedItem = aptr[0]; 
    
    // now deallocate memory used for aptr
    delete [] this->aptr; 
    
    // now give aptr the new arrays value; 
    
    this->aptr = newArray; 
    
    //increment array's size now 
    this->arraySize--;
   
   return poppedItem;
}

template <class T>
T SimpleVector<T>::popBack()
{
  //Student Code Here
   // very similar to what we did earlier 
   
   
   // create a new arr with one less size 
    T* newArray= new T[this->arraySize-1]; 
     
    
    // now fill new newArray with original's data; skip the last one 
    for(int i =0 ; i< this->arraySize-1; i++)
    {
        newArray[i] = this->aptr[i]; 
    }
    
    // store item that was lost for returning 
    T poppedItem = aptr[this->arraySize-1]; 
    
    // now deallocate memory used for aptr
    delete [] this->aptr; 
    
    // now give aptr the new arrays value; 
    
    this->aptr = newArray; 
    
    //increment array's size now 
    this->arraySize--;
   
   return poppedItem;
}

//***********************************************************
// Constructor for SimpleVector class. Sets the size of the *
// array and allocates memory for it.                       *
//***********************************************************

template <class T>
SimpleVector<T>::SimpleVector(int s)
{
   arraySize = s;
   // Allocate memory for the array.
   try
   {
      aptr = new T [s];
   }
   catch (bad_alloc)
   {
      memError();
   }

   // Initialize the array.
   for (int count = 0; count < arraySize; count++)
      *(aptr + count) = 0;
}

//*******************************************
// Copy Constructor for SimpleVector class. *
//*******************************************

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
   // Copy the array size.
   arraySize = obj.arraySize;
   
   // Allocate memory for the array.
   aptr = new T [arraySize];
   if (aptr == 0)
      memError();
      
   // Copy the elements of obj's array.
   for(int count = 0; count < arraySize; count++)
      *(aptr + count) = *(obj.aptr + count);
}

//**************************************
// Destructor for SimpleVector class.  *
//**************************************

template <class T>
SimpleVector<T>::~SimpleVector()
{
   if (arraySize > 0)
      delete [] aptr;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVector<T>::memError()
{
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVector<T>::subError()
{
   cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}

//*******************************************************
// getElementAt function. The argument is a subscript.  *
// This function returns the value stored at the sub-   *
// cript in the array.                                  *
//*******************************************************

template <class T>
T SimpleVector<T>::getElementAt(int sub)
{
   if (sub < 0 || sub >= arraySize)
      subError();
   return aptr[sub];
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************

template <class T>
T &SimpleVector<T>::operator[](const int &sub)
{
   if (sub < 0 || sub >= arraySize)
      subError();
   return aptr[sub];
}
#endif
