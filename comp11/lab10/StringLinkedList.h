/*
 * An interface to a linked list of strings.
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2018
 *
 * Updated: Spring 2021
 */

#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H
#include <string>

using namespace std;

class StringLinkedList
{
public:
        StringLinkedList();
        ~StringLinkedList();

        bool isEmpty();
        void addToFront(string s);
        string firstElement();
        int  length();
        void removeFirst();
        void remove(string s);
        void print();
        void printArtistically();
        void addToBack(string s);
        void addAtPosition(string s, int position);
        void removeFromPosition(int position);
        
private:
        struct Node {
                string element;
                Node *next;
        };

        int *front;


        /*
         * I defined the following helper functions.
         * You can define them, too, or you can ignore them.
         * If you add additional helper functions, you should
         * add those declarations here.
         */
        Node *newNode(string s, Node *next);
        Node *newNode(string s);
        Node *addAtPosition(string s, int position, Node *current);
        int  length(Node *current);
        void printArtistically(Node *current);
        Node *removeRec(string s, Node *firstNode);
        Node *removeFromPosition(int position, Node *firstNode);

        /*
         * Making copy constructor and assignment operator private
         * because we're not implementing them.
         * You do not have to know about these, but you should
         * not pass or return your linked lists by value.
         */
        StringLinkedList(const StringLinkedList &other);
        StringLinkedList &operator=(const StringLinkedList &rhs);
};

#endif
