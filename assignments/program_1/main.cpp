
///////////////////////////////////////////////////////////////////////////////
//                   YOU MUST COMPLETE AND COMMENT YOUR CODE!
// Title:            Program 1
// Files:            main.cpp
// Semester:         3013 Algorithms Spring 2018
//
// Author:           Jakob Lopez
// Email:            thejakoblopez@gmail.com
// Description:
//       This is a basic linked-list that allows numbers to be inserted either in the front or in order

/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node
{
  int data;
  node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers. 
* Methods:
*     void  frontSert(int x)
*     void  orderSert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*/
class intLinkedList
{
  private:
  node* Head;
  
  public:
  intLinkedList()
  {
    Head = NULL;
  }
  void frontSert(int x)
  {
    //empty list case
    if(!Head)
    {
      Head = new node;
      Head->data = x;
      Head->next = NULL;
    }
    else
    {//not empty list
      node* T = new node;
      T->data = x;
      T->next = Head;
      Head = T;
    }
  }
  
  void orderSert(int x)
  {
    //New node
    node *temp = new node;
    temp->data = x;
    temp->next = NULL;
    
    //If Head is null or if Head's data is greater than temp
    if (!Head || Head->data >= temp->data)
    {
        temp->next = Head;
        Head = temp;
    }
    else
    {
        //New node that points to Head
        node *current = Head;
        
        //Traverse list
        while (current->next!=NULL && current->next->data < temp->data)
        {
            current = current->next;
        }
        
        temp->next = current->next;
        current->next = temp;
    }
  }
  
  node* Find(int key)
  {
    node* temp = Head;
    while(temp){
      if(temp->data == key)
      {
        return temp;
      }
      temp = temp->next;
    }
    return NULL;
  }
  
  node* Remove(int key)
  {
    node* result = Find(key);
    if(result)
    {
      node* temp = Head;
      while(temp->next != result)
      {
        temp = temp->next;
      }
      temp->next = result->next;
      delete result;
    }
  }
  
  void print()
  {
    node* p = Head;
    while(p)
    {
      cout << p->data << "->";
      p = p->next;
    }
    cout<<endl;
  }
};

int main() 
{
  // seed random number generator
  srand(8734587);
  
  
  // declare instance of intLinkedList turning
  // a class definition into an "object"
  intLinkedList mylist;
  intLinkedList mylist1;
  //Load 10 random ints into our list
  for(int i=0;i<10;i++)
  {
    mylist.frontSert(rand()%100);
  }
  
  cout<<"frontSert:"<<endl;
  //print the list
  mylist.print();
  cout<<endl;
  
  int x = 99;
  
  //find some value
  if(mylist.Find(x))
  {
    cout << x << " was not found"<<endl;
  }
  else
  {
    cout << x << " was not found"<<endl;
  }
  cout<<endl;
  
  int y = 58;
  //remove some value 
  mylist.Remove(y);
  
  cout<<y<<" was removed from the list. New list:"<<endl;
  
  //print the list again
  mylist.print();
  cout<<endl;
  

  cout<<"============================================"<<endl;
  cout<<"New list"<<endl;
  cout<<endl;
  
  
  for(int i=0;i<10;i++)
  {
    mylist1.orderSert(rand()%100);
  }
  cout<<"orderSert:"<<endl;
  mylist1.print();

  
}
