#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include<utility>

using namespace std;

class HashTable {
private:
    int tableSize;  // Actual size of the table
    int currentSize;  // Number of elements in the table
    vector<pair<int, int>> table;
    vector<bool> isDeleted;
    int maxProbes;  // Variable for controlling the number of probes

    // Hash function: key mod table size
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Function to resize the hash table when the load factor exceeds 70%
    void resize() {
        int newSize = nextPrime(tableSize * 2);
        vector<pair<int, int>> oldTable = table;
        vector<bool> oldIsDeleted = isDeleted;

        table.clear();
        isDeleted.clear();

        table.resize(newSize, {-1, -1});  // Initialize all slots to (-1, -1) (empty)
        isDeleted.resize(newSize, false);

        tableSize = newSize;
        currentSize = 0;

        // Rehash old values
        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].first != -1 && !oldIsDeleted[i]) {
                this->insert(oldTable[i].first);  // Reinsert into the new table
            }
        }
    }

public:
    HashTable(int initialSize) {
        tableSize = nextPrime(initialSize);
        table.resize(tableSize, {-1, -1});  // Initialize all slots to (-1, -1) (empty)
        isDeleted.resize(tableSize, false);
        currentSize = 0;
        maxProbes = tableSize;  // Set maximum probes to table size
    }

    // Function to insert a key using quadratic probing
    void insert(int key) {
        int index = hashFunction(key);
        int i = 0;  // Quadratic probing counter

        while (i < maxProbes) {
            int newIndex = (index + i * i) % tableSize;

            // Check for duplicate keys
            if (table[newIndex].first == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }

            // Insert into empty or previously deleted slot
            if (table[newIndex].first == -1 || isDeleted[newIndex]) {
                table[newIndex] = make_pair(key, key);  // Value is the same as the key
                isDeleted[newIndex] = false;
                currentSize++;

                // Resize if load factor exceeds 70%
                if (currentSize * 100 / tableSize > 70) {
                    resize();
                }
                return;
            }

            i++;
        }

        cout << "Max probing limit reached!" << endl;
    }

    // Function to remove a key using quadratic probing
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < maxProbes) {
            int newIndex = (index + i * i) % tableSize;

            if (table[newIndex].first == key && !isDeleted[newIndex]) {
                table[newIndex] = {-1, -1};  // Mark slot as empty
                isDeleted[newIndex] = true;  // Mark slot as deleted
                currentSize--;
                cout << "Key " << key << " removed." << endl;
                return;
            }

            if (table[newIndex].first == -1) {
                cout << "Element not found" << endl;
                return;
            }

            i++;
        }

        cout << "Element not found" << endl;
    }

    // Function to search for a key using quadratic probing
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < maxProbes) {
            int newIndex = (index + i * i) % tableSize;

            if (table[newIndex].first == key && !isDeleted[newIndex]) {
                return newIndex;
            }

            if (table[newIndex].first == -1) {
                return -1;  // Key not found
            }

            i++;
        }

        return -1;  // Key not found
    }

    // Function to print the table in the required format
    void printTable() {
        for (int i = 0; i < tableSize; ++i) {
            if (table[i].first != -1 && !isDeleted[i]) {
                cout << table[i].second << " ";  // Print value (same as key)
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};