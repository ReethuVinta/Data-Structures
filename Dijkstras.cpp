#include<bits/stdc++.h>
using namespace std;

struct Adjnode  //structure to store node in graph
{
  int val;
  int weight;
  Adjnode* next;
};

struct graphedge//structure to store graphedges
{
  int begin;
  int end;
  int wei;
  graphedge* next;
};

struct heapnode //structure for heap node that contains vertice and distance
{
  int ver;
  int dist;
};

struct heap
{
  int current_size;
  int size;
  int *point;
  heapnode **node;
};

class Minheap //minheap class
{
public:
   heapnode* create_heap_node(int u,int v)//creates new heapnode
   {
     heapnode *newnode = new heapnode;
     newnode->ver=u;
     newnode->dist=v;
     return newnode;
   }

   heap* create_heap(int m)//creates a newheap with size m
   {
     heap *heap_create=new heap;
     heap_create->current_size=0;
     heap_create->size=m;
     heap_create->point=new int[m];
     heap_create->node=new heapnode*[m];
     return heap_create;
   }

   void heapify(heap* newheap,int i)//performs minimum heapify at the given node i
   {
     int least,l,r;
     least=i;
     l=(2*i)+1;
     r=(2*i)+2;

     if(l < newheap->current_size && newheap->node[l]->dist < newheap->node[least]->dist )
     {
       least=l;
     }
     if(r < newheap->current_size && newheap->node[r]->dist < newheap->node[least]->dist )
     {
       least=r;
     }
     if(least!=i)
     {
        heapnode *leastnode=newheap->node[least];
        heapnode *swapnode=newheap->node[i];

        newheap->point[leastnode->ver]=i;
        newheap->point[swapnode->ver]=least;

        //swapping
        heapnode* temp=newheap->node[least];
        newheap->node[least]=newheap->node[i];
        newheap->node[i]=temp;
        heapify(newheap,least);
     }
   }

   bool isempty(heap* newheap)//check whether heap is empty or not
   {
     if(newheap->current_size==0)return 1;
     else return 0;
   }

   bool inheap(heap*newheap,int v)//check whether element is present in heap or not
   {
      if(newheap->point[v]<newheap->current_size)return 1;
      else return 0;
   }

   heapnode* extract_min(heap *newheap)//extracts the minimum element from the heap
   {
     if(isempty(newheap))return NULL;

     heapnode* extracted=newheap->node[0];
     heapnode* last=newheap->node[newheap->current_size-1];
     newheap->node[0]=last;
     newheap->point[extracted->ver]=newheap->current_size-1;
     newheap->point[last->ver]=0;
     newheap->current_size--;//decrementing the current size in the heap
     heapify(newheap,0);//heapifying at the root(because we removed element from there)
     return extracted;
   }

   void decrease_key(heap* newheap,int q,int newdist)//decreases the distance at this node
   {
     int p=newheap->point[q];
     newheap->node[p]->dist=newdist;

     while(p && newheap->node[p]->dist < newheap->node[(p-1)/2]->dist)//checking with its parent,if parent is more it swaps with it and this keeps on going till it reaches root
     {
       newheap->point[newheap->node[p]->ver]=(p-1)/2;;
       newheap->point[newheap->node[(p-1)/2]->ver]=q;

       heapnode* temp=newheap->node[p];
       newheap->node[p]=newheap->node[(p-1)/2];
       newheap->node[(p-1)/2]=temp;
       p=(p-1)/2;
     }
   }
};

class Graph : public Minheap//inherits minheap class
{
private:
  vector<vector<int>>connected;
  vector<int>track;
public:
  Adjnode** directed;//to maintain track of directed graph
  Adjnode** undirected;//to maintain track of undirected graph
  int vertices;
  graphedge* HEAD;

  Graph(int p)//intialising the graph
  {
      this->vertices=p;
      directed = new Adjnode*[p];
      undirected = new Adjnode*[p];
      HEAD=NULL;
  }

  void setgraphedge()//takes the graph edges inputs from the user
  {
    string input;
    getline(cin,input);
    graphedge* prev=NULL;
    while(input.length()!=0)
    {
      char S;
      int v1,v2,W;
      stringstream take(input);
      take>>S;
      take>>v1;
      take>>v2;
      take>>W;
      graphedge* node=new(graphedge);
      node->begin=v1;
      node->end=v2;
      node->wei=W;
      node->next=NULL;
      if(HEAD==NULL)HEAD=node;
      else prev->next=node;
      prev=node;
      getline(cin,input);
    }
    cout<<"done taking edges"<<endl;
  }

  void printedges()//prints the edges in the graph
  {
    graphedge* current=HEAD;
    while(current!=NULL)
    {
      cout<<current->begin<<" "<<current->end<<current->wei<<endl;
      current=current->next;
    }
  }

  Adjnode* setvertices(int a,int b,Adjnode* temp)
  {
    Adjnode* newnode=new(Adjnode);
    newnode->val=a;
    newnode->weight=b;
    newnode->next=temp;
    return newnode;
  }

  void undirected_graph()//creates undirected_graph
  {
    for(int i=0;i<vertices;i++)
    {
      undirected[i]=NULL;
    }
    graphedge* current=HEAD;
    while(current!=NULL)
    {
        int start_ver = current->begin;
        int end_ver = current->end;
        int weight =current->wei;
        Adjnode* newNode =setvertices(end_ver, weight,undirected[start_ver]);
        undirected[start_ver] = newNode;

        start_ver = current->end;
        end_ver = current->begin;
        weight =current->wei;
        newNode =setvertices(end_ver, weight, undirected[start_ver]);
        undirected[start_ver] = newNode;
        current=current->next;
      }
  }

  void directed_graph()//creates directed graph
  {
    for(int i=0;i<vertices;i++)
    {
      directed[i]=NULL;
    }
    graphedge* current=HEAD;
    while(current!=NULL)
    {
        int start_ver = current->begin;
        int end_ver = current->end;
        int weight =current->wei;
        Adjnode* newNode =setvertices(end_ver, weight,directed[start_ver]);
        directed[start_ver] = newNode;
        current=current->next;
    }
  }

  void display()//displays directed graph
  {
    for(int i=0;i<vertices;i++)
    {
        Adjnode* ptr;
        ptr=directed[i];

        while(ptr!=NULL)
        {
          cout<<i<<","<<ptr->val<<" "<<ptr->weight<<" ";
          ptr=ptr->next;
          cout<<endl;
        }
    }
  }

 void displayundirected()//displays undirected graph
 {
   for(int i=0;i<vertices;i++)
   {
       Adjnode* ptr;
       ptr=undirected[i];

       while(ptr!=NULL)
       {
         cout<<i<<" "<<ptr->val<<" "<<ptr->weight<<" ";
         ptr=ptr->next;
         cout<<endl;
       }
   }
}

  vector<int> BFS(int s,bool visited[])//runs BFS on vertex 's'
  {
    int u;
    list<int>queue;
    vector<int>track;//to maintain the elements in this connected component
    queue.push_back(s);
    track.push_back(s);
    visited[s]=1;

    while(!queue.empty())
    {
      u=queue.front();
      queue.pop_front();
      auto ptr=undirected[u];
      while(ptr!=NULL)
      {
        if(!visited[ptr->val])//if it is unvisited the add into the queue
        {
          visited[ptr->val]=1;
          if(find(track.begin(),track.end(),ptr->val)==track.end())track.push_back(ptr->val);//if this element is not present in track then add it into the track
          queue.push_back(ptr->val);
        }
        ptr=ptr->next;
      }
     }
    return track;
  }

  void totalcount()//gets the total number of connected compnents in the graph
  {
    bool visited[vertices];
    int count=0;
    for(int i=0;i<vertices;i++)
    {
      visited[i]=0;
    }
    for(int i=0;i<vertices;i++)
    {
      if(undirected[i]!=NULL)
      {
      if(!visited[i])
      {
        vector<int>track;
        //cout<<"BFS sent into this "<<i<<endl;
        track=BFS(i,visited);
        connected.push_back(track);//adding each connected componenst we get into vector
        count=count+1;
      }
    }
  }
    cout<<"connected components are "<<count<<endl;
  }

  void printconnected()//prints the elements in each connected components
  {
    for(int i=0;i<connected.size();i++)
    {
      sort(connected[i].begin(),connected[i].end());
      for(int j=0;j<connected[i].size();j++)
        {
            cout<<connected[i][j]<<" ";
        }
        cout<<endl;
    }
  }

  void dij(int source)//runs dijkstras on the source
  {
    int distance[vertices];
    heap *MINHEAP=create_heap(vertices);//creates minheap of size vertices

    for(int i=0;i<vertices;++i)//initialises the distance,point for each element in minheap
    {
      distance[i]=INT_MAX;
      MINHEAP->node[i]=create_heap_node(i,distance[i]);
      MINHEAP->point[i]=i;
    }
    MINHEAP->current_size=vertices;
    MINHEAP->node[source]=create_heap_node(source,distance[source]);
    MINHEAP->point[source]=source;
    distance[source]=0;//setting distance of souce to zero
    decrease_key(MINHEAP,source,distance[source]);//intially we have set distance of source to INT_MAX so new using decrease key to make the distance 0

    while(!isempty(MINHEAP))//runs untill heap is not empty
    {
      heapnode* extracted=extract_min(MINHEAP);//extracting the min elemnt from the heap

      int u=extracted->ver;
      auto ptr=directed[u];
      while(ptr!=NULL)
      {
        int v=ptr->val;
        if(inheap(MINHEAP,v) && distance[u]!=INT_MAX && ptr->weight+distance[u]<distance[v])//if d[v]>d[u]+w(u,v) then update the distance of v
        {
          distance[v]=distance[u]+ptr->weight;
          decrease_key(MINHEAP,v,distance[v]);
        }
        ptr=ptr->next;
      }
    }

    for(int i=0;i<vertices;i++)
    {
      if(distance[i]!=INT_MAX)//printing the distances of elements which are in same conneted components
      {
        cout<<source<<" "<<i<<" "<<distance[i]<<endl;
      }
    }
  }

};

int main()
{
  int N;//taking count of vertices in the graph
  string M;
  getline(cin,M);
  stringstream take(M);
  take>>N;

  Graph G(N);
  G.setgraphedge();//taking edges input from user

  string input;
  getline(cin,input);
  while(input.length()!=0)
  {
    string S;
    int source;
    stringstream take(input);
    take>>S;
    take>>source;
    switch(S[0])
    {
      case 'F':
               G.undirected_graph();
               G.totalcount();
               G.printconnected();
               break;
      case 'S':G.directed_graph();
               G.dij(source);
               break;
    }
    getline(cin,input);
  }


  return 0;
}
