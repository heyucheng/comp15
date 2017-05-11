
#include <iostream>
#include <cmath>
#include "TaskList.h"

using namespace std;

////////////////////////////////////////////////////////
// TaskListNode

TaskListNode::TaskListNode(float aTimeStamp,
			   std::string& aTaskTitle)
  : mTimeStamp(aTimeStamp), mTaskTitle(aTaskTitle), mNext(nullptr)
{
}

TaskListNode::TaskListNode(float aTimeStamp,
			   std::string& aTaskTitle,
			   TaskListNode* aNext)
  : mTimeStamp(aTimeStamp), mTaskTitle(aTaskTitle), mNext(aNext)
{
}

// Insert after this node
void TaskListNode::insertAfter(float aTimeStamp, string& aTaskTitle)
{
  mNext = new TaskListNode(aTimeStamp, aTaskTitle, mNext);
}

// Delete the node after this node
void TaskListNode::removeAfter()
{
  TaskListNode* temp = next();
  mNext = mNext->next();
  delete temp;
}

////////////////////////////////////////////////////////
// TaskList

TaskList::TaskList()
  : mHead(nullptr), mOrder(TaskList::ASCENDING)
{
}

TaskList::TaskList(TaskList::Order aOrder)
  : mHead(nullptr), mOrder(aOrder)
{
}

bool TaskList::isEmpty() const 
{
  return (mHead == nullptr);
}

// Adding to the front of the list
void TaskList::addTask(float aTimeStamp, 
		       string aTaskTitle)
{
  if (mHead != nullptr) {
    if (aTimeStamp == mHead->timeStamp()) {
      cerr << "Attempt to enter a conflicting task." << endl;
      cerr << "Not doing anything." << endl;
      return;
    }
    if (mOrder == TaskList::ASCENDING) {
      // Entering tasks in the ascending order
      if (aTimeStamp < mHead->timeStamp()) {
	cerr << "The enforced ordering is Ascending. Invalid entry."
	     << endl;
	cerr << "Not doing anything" << endl;
	return;
      }
    } else {
      // Entering tasks in the descending order
      if (aTimeStamp > mHead->timeStamp()) {
	cerr << "The enforced ordering is Ascending. Invalid entry."
	     << endl;
	cerr << "Not doing anything." << endl;
	return;
      }
    }
  }
  mHead = new TaskListNode(aTimeStamp, aTaskTitle, mHead);
}

// Remove the front element
void TaskList::removeFront()
{
  TaskListNode* temp = mHead;
  mHead = mHead->next();
  delete temp;
}




// Delete a task matching a particular time-stamp
void TaskList::deleteTask(float aTimeStamp)
{
   // Your implementation goes here
  if(isEmpty()) {
    cout << "The day-planner is empty" << endl;
    return;
  }


  TaskListNode * searchPtr = mHead;
  TaskListNode * temp = nullptr;

  do{
    temp = searchPtr;
    searchPtr = searchPtr->next();
  } while(searchPtr != nullptr and searchPtr->timeStamp() != aTimeStamp);

  if(searchPtr == nullptr) {
    cout << "There is no task at " << aTimeStamp << "." << endl;
  } 
  if (searchPtr->timeStamp() == aTimeStamp) {
    temp->setNext(searchPtr->next());
    delete searchPtr;

  }

} 

// Insert a new task at an appropriate position
void TaskList::insertTask(float aTimeStamp, std::string aTaskTitle)
{
  
   // Your implementation goes here 
  if(isEmpty()) {
  mHead = new TaskListNode(aTimeStamp, aTaskTitle, nullptr);
  } 

  TaskListNode * searchPtr = mHead;

  if (mOrder == TaskList::ASCENDING) {
  
    do{
      searchPtr = searchPtr->next();
    } while(searchPtr->next() != nullptr and searchPtr->timeStamp() <= aTimeStamp );

    if (searchPtr->next() == nullptr){
      searchPtr->insertAfter(aTimeStamp, aTaskTitle);
    }
    if (searchPtr->timeStamp() == aTimeStamp){
      cout << "You already have task at " << aTimeStamp << "." << endl;
    }else {
      searchPtr->insertAfter(aTimeStamp, aTaskTitle);
    }
  } else {
  
    do{
      searchPtr = searchPtr->next();
    } while(searchPtr->next() != nullptr and searchPtr->timeStamp() >= aTimeStamp);
    if (searchPtr->next() == nullptr){
      searchPtr->insertAfter(aTimeStamp, aTaskTitle);
    }
    if (searchPtr->timeStamp() == aTimeStamp){
      cout << "You already have task at " << aTimeStamp << "." << endl;
    }else {
      searchPtr->insertAfter(aTimeStamp, aTaskTitle);
    }    
  }
  
}

// Output the task list
void TaskList::output(std::ostream& s) const
{
  cout << "TODAY'S TASK LIST" << endl;
  if (mOrder == TaskList::ASCENDING) {
    // When the list is added in the ascending order
    // the list is stored in descending order
    cout << "(Descending Order)" << endl;
  } else {
    // vice versa
    cout << "(Ascending Order)" << endl;
  }
  if (isEmpty()) {
    cout << "No agenda!" << endl;
  }
  for (TaskListNode* currNode = mHead;
       currNode != nullptr; currNode = currNode->next()) {
    float taskTime = currNode->timeStamp();
    int hour = static_cast<int>(floor(taskTime));
    bool afternoon = false;
    int min = static_cast<int>(floor((taskTime-hour)*60));
    if (hour > 12) {
      afternoon = true;
      hour -= 12;
    }
    cout << hour << ":";
    if (min < 10) {
      cout << "0"; // padding a 0 for formatting
    }
    cout << min;
    cout << (afternoon? " PM" : " AM");
    cout << " - ";
    cout << currNode->taskTitle() << endl;
  }
}

// Delete all
void TaskList::removeAll()
{
     // Your implementation goes here
  while (mHead != nullptr) {
    removeFront();
  }
}

// Destructor
TaskList::~TaskList()
{
  removeAll();
}

// Reverse the list
void TaskList::reverse()
{
  TaskListNode * oldHead = nullptr;
  TaskListNode * newHead = nullptr;

  if (mOrder == TaskList::ASCENDING) {
    TaskList::Order aOrder = TaskList::DESCENDING;
    setOrder(aOrder);
  } else {
    TaskList::Order aOrder = TaskList::ASCENDING;
    setOrder(aOrder);
  } 
  
  newHead = mHead;
  mHead = newHead->next();
  newHead->setNext(nullptr);
  oldHead = mHead;
  while(oldHead != nullptr) {
    oldHead = oldHead->next();
    mHead->setNext(newHead);
    newHead = mHead;
    mHead = oldHead;
  } 
  mHead = newHead;
  delete oldHead;
}



std::ostream& operator<<(std::ostream& s, const TaskList& aTaskList)
{
  aTaskList.output(s);
  return s;
}
