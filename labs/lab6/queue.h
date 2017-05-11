#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cassert>

using namespace std;

class Node {
	public:
		// constructors
		Node(int val)
			: mVal(val), mNext(NULL) {}

		Node(int val, Node* next)
			: mVal(val), mNext(next) {}

		int value() {
			return mVal;
		}

		Node* next() {
			return mNext;
		}

		void setNext(Node* next) {
			mNext = next;
		}

	private:
		int mVal;
		Node* mNext;
};

class Queue {
	public:
		Queue()
			: mHead(NULL), mTail(NULL) mSize(0) {}
		
		void enqueue(int val) {
			Node* newTail = new Node(val);
			mTail->setNext(newTail);
			mTail = newTail;
			if (mHead == NULL) mHead = mTail;
			mSize++;
		}

		void deque() {
			assert(mHead == NULL && mSize > 0);
			if (mHead == NULL) {
				return;
			}
			Node* oldHead = mHead;
			mHead = mHead->next();
			delete oldHead;
			if (mHead == NULL) mTail = NULL;
			mSize--;
		}

		bool empty() {
			return (mSize == 0);
		}

		int size() {
			return mSize;
		}

		int front() {
			if (empty()) {
				cout << "Queue empty." << endl;
				return -1;
			}
			return mHead->vaule();
		}

		void removeAll() {
			while(mSize > 0) {
				dequeue();
			}
			mHead = NULL;
			mTail = NULL;
			mSize = 0;
		}

		Node* head() {
			return mHead;
		}

		Node* tail() {
			return mTail;
		}
		
		// copy constructor
		Queue(const Queue& other)
			: mHead(NULL), mSize(0) {
				if (!other.empty()) {
					for (Node* cur = other.head(); cur != NULL; cur = cur->next()) {
						enqueue(cur->value());
					}
				}
			}

		// assignment operator
		Queue& operator=(const Queue& other) {
			if (this == &other)
				return this;

			removeAll();
			if (!other.empty()) {
				for (Node* cur = other.head(); cur != NULL; cur = cur->next()) {
					enqueue(cur->value());
				}
			}
			return *this;
		}

		~Queue() {
			removeAll();
		}
	private:
		Node* mHead;
		Node* mTail;
		int mSize;
};

#endif