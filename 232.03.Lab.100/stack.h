/***********************************************************************
 * Module:
 *    Stack
 * Summary:
 *    Our custom implementation of std::stack
 *
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
//#include "vector.h"
#include <vector>

namespace custom
{

/**************************************************
 * STACK
 * First-in-Last-out data structure
 *************************************************/
template<class T>
class stack
{
public:
  
   // 
   // Construct
   // 

    stack() { this->container.resize(0); }
    stack(const stack <T>& rhs) { *this = rhs; }
    stack(stack <T>&& rhs) { this->container = move(rhs.container); }
    stack(const std::vector<T>& rhs) { this->container = rhs.container; }
    stack(std::vector<T>&& rhs) { this->container = rhs.container; }
   ~stack() {  }

   //
   // Assign
   //
   
   stack <T> & operator = (const stack <T> & rhs)
   {
       this->container = rhs.container;
      return *this;
   }
   stack <T>& operator = (stack <T> && rhs)
   {
       this->container = move(rhs.container);
      return *this;
   }
   void swap(stack <T>& rhs)
   {
       this->container.swap(rhs.container);
   }

   // 
   // Access
   //

         T& top()       { return (this->container.back()); }
   const T& top() const { return *(this->container.back()); }

   // 
   // Insert
   // 

   void push(const T& t) { container.push_back(t); } // Copy push
   void push(T&& t) { container.push_back(std::move(t)); } // Move push

   //
   // Remove
   //

   void pop() 
   { 
       this->container.pop_back();
   }

   //
   // Status
   //
   size_t  size () const { return this->container.size();  }
   bool empty   () const { return this->size() == 0 ? true : false; }
   
#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   
  std::vector<T> container;  // underlying container
};



} // custom namespace


