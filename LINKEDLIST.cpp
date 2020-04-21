#include<bits/stdc++.h>
using namespace std;

struct node  //structure defined for node
{
  char letter;
  struct node *next;
};

struct freq  //node to maintain the frequency of each alphabet
{
  char letter;//alphabet
  unsigned long long int N;//to maintain the count of that alphabet
  struct freq *ptr;
};

node *HEAD=NULL;//intialising head of the MAIN linked list to NULL
node *TAIL=NULL;
freq *HEADFREQ=NULL;//intialising head of freq linkedlist to NULL

node* newnode(char A)  //fucntion that creates new node with the given character
{
  node *temp=(node*)malloc(sizeof(node));
  temp->letter=A;
  temp->next=NULL;
  return temp;
}

freq* search(char x)//function that searches for charatcer x in freq linked list
{
  freq *current=HEADFREQ;
  if(HEADFREQ==NULL)return NULL;
  else
  {
    while(current!=NULL)
    {
      if(current->letter==x)break;
      current=current->ptr;
    }
  }
  return current;
}

void insert(char x)//function that insert charatcer x into freq linked list
{
  freq* P=new freq;
  P->letter=x;
  P->N=1;
  P->ptr=NULL;

  freq* current=HEADFREQ;
  if(HEADFREQ==NULL)HEADFREQ=P;
  else
  {
  while(current->ptr!=NULL)
  {
    current=current->ptr;
  }
  current->ptr=P;
  }
}
void swap(freq*a,freq*b)//function to swap contenets of two freq nodes
{
  char m;
  int n;
  m=a->letter;
  n=a->N;
  a->letter=b->letter;
  a->N=b->N;
  b->letter=m;
  b->N=n;
}

void sort()//function to sort the FREQ linked list
{
  freq* current= HEADFREQ;
  freq* itr=NULL;
  while(current!=NULL)
  {
    itr=current->ptr;
    while(itr!=NULL)
    {
      if(current->N > itr->N)swap(current,itr);
      itr=itr->ptr;
    }
    current=current->ptr;
  }
}

void store(string S,unsigned long long int n)  //function to make linked list from string
{

  node *prev;
  if(TAIL==NULL)prev=NULL;
  else prev=TAIL;
  node *p=NULL;

  for(unsigned long long int i=0;i<n;i++)
  {
    p=newnode(S[i]);
    if(HEAD==NULL)
    {
      HEAD=p;
    }
    else
    {
      prev->next=p;
    }
    prev=p;
    //tracking freq array
    freq* temp=search(S[i]);
    if(temp==NULL)//if character is not there then we insert that character into FREQ Linkedlist
    {
        insert(S[i]);
    }
    else//if character is there then we increase the count by 1;
    {
      temp->N++;
    }
  }
  TAIL=prev;
  cout<<HEAD->letter<<" "<<TAIL->letter;//printing HEAD and TAIL of linked list
}


void ascend() //function that sorts frequency of that alphabet
{
  if(HEAD==NULL)cout<<"ERROR"<<endl;
  else
  {
    sort();//sorting the FREQ linked list
    freq* current=HEADFREQ;
    cout<<"printing in ascending order"<<endl;
    while(current!=NULL)//printing sorted FREQ list
    {
      cout<<current->letter<<" ";
      current=current->ptr;
    }
  }
}

void print()//fucntion that prints alphabet and it's frequency
{
  if(HEAD==NULL)cout<<"ERROR"<<endl;//if HEAD is NULL it prints ERROR
  else
  {
    freq *current=HEADFREQ;
    while(current!=NULL)//Function to print freq of each alphabet
    {
      cout<<current->letter<<"-"<<current->N<<" ";
      current=current->ptr;
    }
    cout<<endl;
  }
}


void del(node *current,node*prev)//fucntion to delete a node
{
  if(current->next==NULL)
  {
    prev->next=NULL;
    TAIL=prev;
  }
  else
  {
    prev->next=current->next;
  }
  free(current);
}

void remove(unsigned long long int k)
{
   if(HEAD==NULL || k==0)cout<<"ERROR"<<endl;
   else
   {
   node* current=HEAD;
   node* prev=NULL;
   unsigned long long int count;
   while(current!=NULL)
   {
      if(current==HEAD)//if it is head increment the count and continue
      {
        count=0;
        count++;
        prev=current;
        current=current->next;
      }
      else if(current->letter!=prev->letter)//if both are not equal set the count to '0' and continue
      {
        count=0;
        count++;
        prev=current;
        current=current->next;
      }
      else  //if both are equal
      {
        count++;
        if(count>k)
        {
          freq* temp=search(current->letter);
          temp->N--;//decressing the frequency of this aplhabet in FREQ linked list
          del(current,prev);
          count--;
          current=prev->next;
        }
        else
        {
          prev=current;
          current=current->next;
        }
      }
   }
   node *temp=HEAD;
   while(temp!=NULL)//printing the linked list after deleting the charcaters that obtain more than k tmes consecutively
   {
     cout<<temp->letter<<" ";
     temp=temp->next;
   }
   }
}

int main()
{
  string P,S;
  unsigned long long int n,k;
  getline(cin,P); //scanning the string
  stringstream take(P);
  take>>S;

  n=S.length();

  string input;
  getline(cin,input);
  while(input.length()!=0)
  {
    string function;
    int k;
    stringstream take(input);
    take>>function;
    take>>k;
    switch(function[0])
    {
      case 'S':store(S,n);//executes store function
               break;
      case 'P':print();//executes print function
               break;
      case 'A':ascend();//executes ascend function
               break;
      case 'R':remove(k);//executes remove function
               break;
      default :break;
    }
    getline(cin,input);
  }
  return 0;
}
