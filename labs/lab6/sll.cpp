#include "sll.h"

using namespace std;

void SLinkedList::sort()
{
	mHead = mergeSort(mHead);
	SLLNode* temp = mHead;
	while(temp->next() != NULL){
		temp = temp -> next();
	}
	mTail = temp;
	return;
}

SLLNode* SLinkedList::mergeSort(SLLNode* aHead)
{
  // Your code goes here
	if ((aHead == NULL) or (aHead->next() == NULL)) {
		return aHead;
	}
	SLLNode* a = aHead;
	SLLNode* b = split(aHead) -> next();
	split(aHead)->setNext(NULL);
	return merge(mergeSort(a), mergeSort(b));	

}


SLLNode* SLinkedList::split(SLLNode* aHead)
{
	SLLNode* fast;
	SLLNode* slow;
	
	if (aHead == NULL or aHead->next() == NULL) {
		return NULL;
	} else {
		slow = aHead;
		fast = aHead->next();
		while (fast != NULL) {
			fast = fast->next();
			if (fast != NULL) {
				fast = fast->next();
				slow = slow->next();
			}
		}
		return slow;
	}
}


SLLNode* SLinkedList::merge(SLLNode* a, SLLNode* b)
{
	SLLNode* result = NULL;
	if (a == NULL) {
		return b;
	}
	if (b == NULL) {
		return a;
	}
	
	if (a->value() <= b-> value()){
		result = a;
		a = a->next();
		result->setNext(merge(a, b));
	} else {
		result = b;
		b = b->next();
		result->setNext(merge(a,b));
	}	
	return result;
}



/// Overloaded operator<< for outputing a list
ostream& operator<<(ostream& s, const SLinkedList& aList)
{
  aList.output(s);
  return s;
}
