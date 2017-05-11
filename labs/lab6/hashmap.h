
int tableSize = 256;

class HashNode {
private:
	int key;
	int value;
public:
	HashNode(int key, int val) {
		this->key = key;
		this->value = val;
	}

	int getKey() {
		return key;
	}

	int getValue() {
		return value;
	}
};

class HashMap {
private:
	HashNode** table;
public:
	HashMap() {
		table = new HashNode*[tableSize];
		for (int i = 0; i < tableSize; i++) {
			table[i] = NULL;
		}
	}

	int get(int key) {
		int hash = key % tableSize;
		while(table[hash] && table[hash]->getKey() != key) hash = (hash+1) % tableSize;
		if (table[hash]) return table[hash]->getValue();;
		return -1;
	}

	int put(int key, int val) {
		int hash = key % tableSize;
		while(table[hash] && table[hash]->getKey() != key) hash = (hash+1) % tableSize;
		if (table[hash]) delete table[hash];
		table[hash] = new HashNode(key, val);
	}

	~HashMap() {
		for (int i = 0; i < tableSize; i++) {
			if (table[i]) delete table[i];
		}
		delete [] table;
	}
};

