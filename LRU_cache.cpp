#include<bits/stdc++.h>
using namespace std;

int capacity = 2;
map<int,struct node*> h;

struct node
{
    int key;
    int value;
    struct node *next;
    struct node *prev;
};

struct node *start = NULL;
struct node *last = NULL;

void put(int kkey,int vvalue);

void printreverse()
{
    struct node *temp;
    temp = last;
    while(temp!=NULL)
    {
        cout<<temp->key<<"-->";
        temp = temp->prev;
    }
}

void print()
{
    struct node *temp;
    temp = start;
    while(temp!=NULL)
    {
        cout<<temp->key<<"-->";
        temp = temp->next;
    }
}

struct node* createnode(int kkey,int vvalue)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->key = kkey;
    newnode->value = vvalue;
    newnode->prev = NULL;
    newnode->next=NULL;
};

void get(int kkey)
{
    if(!(h.find(kkey)!=h.end()) )
    {
        cout<<"-1"<<endl;
    }
    else
    {
        struct node *temp = h[kkey];
        if(temp==start)
        {
            cout<<temp->key<<endl;
        }
        else{

                int value = temp->value;
                cout<<temp->key<<endl;
                if(temp==last)
                {
                    temp->prev->next =NULL;
                    last = temp->prev;
                    temp->prev = NULL;
                    temp->next = start;
                    start->prev = temp;
                    start = temp;
                }
                else{
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    temp->prev = NULL;
                    temp->next = start;
                    start->prev = temp;
                    start = temp;
                }
        }
    }
}

void put(int kkey,int vvalue)
{
    if(h.empty())
    {
        struct node *newnode = createnode(kkey,vvalue);
        h[kkey] = newnode;
        start = newnode;
        last = newnode;
    }

    else if(!(h.find(kkey) != h.end()) && h.size() < capacity)
    {
        //insert the node into the front;
        struct node *newnode = createnode(kkey,vvalue);
        newnode->next = start;
        start->prev = newnode;
        start = newnode;
        h[kkey] = newnode;
    }

    else if( h.find(kkey) !=h.end() )
    {
        struct node *temp = h[kkey];
        if(temp==last)
        {
            temp->prev->next =NULL;
            last = temp->prev;
            temp->prev = NULL;
            temp->next = start;
            start->prev = temp;
            start = temp;
        }
        else{
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp->prev = NULL;
            temp->next = start;
            start->prev = temp;
            start = temp;
        }
    }

    else if(!(h.find(kkey) != h.end()) && h.size() >= capacity){
        // replacement should happen here
        // front of the linked list contains the most recently used item
        // last or rear contains the least recently used item.
        //steps:
        // get the rear element key
        // remove the element from the hashmap.
        // decrement the rear
        // insert the newnode into the front of the linked list

        int removekey = last->key;
        h.erase(removekey);
        last = last->prev;
        last->next =NULL;

        struct node *newnode = createnode(kkey,vvalue);
        newnode->next= start;
        start->prev = newnode;
        start = newnode;
        h[kkey] = newnode;
    }
}

int main()
{
    put(1, 1);
    put(2, 2);
    get(1);       // returns 1
    put(3, 3);    // evicts key 2
    get(2);       // returns -1 (not found)
    put(4, 4);    // evicts key 1
    get(1);       // returns -1 (not found)
    get(3);       // returns 3
    get(4);
}
