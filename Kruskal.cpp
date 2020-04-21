#include<bits/stdc++.h>
using namespace std;

struct graphedge //linked list to maintain thegraph edges
{
  int begin;
  int end;
  int wei;
  graphedge* next;
};

class Graph//graph class
{
public:
  bool *vertices_count;//to maintain the track of vertcies present in graph
  int vertices;  //vertices in graph
  int weight;  //weight of spanning tree
  int *parent;  //array that maintains parent of each element
  int *rank;//array that maintains rank of each set
  int edges,treeedges;//to maintain counts of edges in graph,spanning tree
  graphedge* HEAD;//maintains the track of edges
  graphedge* TREEHEAD;//maintains the track of edges in minimum spaanning tree

  Graph(int q)//intialising the graph
  {
    this->vertices=q;
    parent = new int[q];
    rank = new int[q];
    vertices_count=new bool[q];
    for(int i=0;i<q;i++)vertices_count[i]=0;
    HEAD=NULL;
    TREEHEAD=NULL;
    edges=0;
    treeedges=0;
    weight=0;  //intialising weight
  }

  void edge_input()  //function to take edges input from user
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
      graphedge* node=new(graphedge);//creating graph node
      node->begin=v1;
      node->end=v2;
      node->wei=W;
      node->next=NULL;
      vertices_count[v1]=1;
      vertices_count[v2]=1;
      if(HEAD==NULL)HEAD=node;
      else prev->next=node;
      prev=node;
      edges++;//incrementing the count of edges by 1 as edge is added
      getline(cin,input);
    }
    cout<<"done taking edges"<<endl;
  }

  void make_set()  //fucntion that makes disjoint sets
  {
    for(int i=0;i<vertices;i++)
    {
      parent[i]=i;//setting the parent of each to itself
      rank[i]=0;//making rank to be 0
    }
  }

  int find_set(int x) //find set with rank compression
  {
    if(x!=parent[x])//if x!=parent[x] then go find parent of parent[x]
    {
      parent[x]=find_set(parent[x]);
    }
    return parent[x];
  }

  void union_set(int x,int y) //union set with rank heuristic
  {
    int F1=find_set(x);
    int R1=rank[F1];
    int F2=find_set(y);
    int R2=rank[F2];

    if(R1>R2) //if R1>R2 then set parent of y as x
    {
      parent[y]=x;
    }
    else if(R1<R2)//if R1>R2 then set parent of x as y
    {
      parent[x]=y;
    }
    else //if rank of both are equal then u can either set rank of y as x or vice-verca. Here I have set parent of y as x
    {
      parent[y]=x;
      rank[x]++;
    }
  }

  void print()  //function to print the edges of undirected graph gien by user
  {
    graphedge* current=HEAD;
    while(current!=NULL)
    {
      cout<<current->begin<<" "<<current->end<<" "<<current->wei<<endl;
      current=current->next;
    }
  }

  void print_tree()  //function to print the elements in minimum spanning tree
  {
    if(check_tree()==0)cout<<"No spanning tree"<<endl;//performs check_tree if it fails the there is no spannign tree
    else
    {
      graphedge* current=TREEHEAD;
      while(current!=NULL)
      {
        cout<<"("<<current->begin<<","<<current->end<<")"<<endl;
        current=current->next;
      }
    }
  }

  void swap(graphedge* a,graphedge*b)//swapping the elements in two graphedges
  {
    int i,j,k;
    i=a->begin;
    j=a->end;
    k=a->wei;
    a->begin=b->begin;
    a->end=b->end;
    a->wei=b->wei;
    b->begin=i;
    b->end=j;
    b->wei=k;
  }

  void sort()//performs sorting
  {
    graphedge* current,*itr;
    current=HEAD;
    itr=NULL;

    if(HEAD==NULL)return;
    else
    {
      while(current!=NULL)
      {
        itr=current->next;
        while(itr!=NULL)
        {
          if(current->wei > itr->wei)swap(current,itr);//if current element is greater than itr element we swap
          itr=itr->next;
        }
        current=current->next;
      }
    }
  }
  void kruskal()  //runs kruskal on graph
  {
      int temp1,temp2;
      sort();//sorting the edges based on weights
      make_set();//this intialises parent,rank
      graphedge* current=HEAD;
      graphedge* prev=NULL;
      while(current!=NULL)
      {   //performing find_set on vertices of the current edge
          temp1=find_set(current->begin);
          temp2=find_set(current->end);
          if(temp1!=temp2)//if they are not equal then it is safe edge
          {
              treeedges++;//increses the edges coutn of tree by one
              weight=weight+current->wei;
              graphedge* node=new(graphedge);
              node->begin=current->begin;
              node->end=current->end;
              node->wei=current->wei;
              node->next=NULL;
              //adding the safe edges into tree
              if(TREEHEAD==NULL)TREEHEAD=node;
              else prev->next=node;
              prev=node;
              //performing union on these two vertices
              union_set(temp1,temp2);
          }
          current=current->next;
      }
      //cout<<"well that was weight for u "<<weight<<endl;
  }

  bool check_tree()//check whether the tree we got is spanning tree or not
  {
      int total_vertices=0;
      for(int i=0;i<vertices;i++)if(vertices_count[i]==1)total_vertices++;
      if(treeedges==total_vertices-1)return 1;//uses the property of spanning tree::TOTAL VERTICES IN GRAPH-1==EDGES IN SPANNING TREE
      else return 0;
  }

};

int main()
{
  int N;//taking count of vertices
  string M;
  getline(cin,M);
  stringstream take(M);
  take>>N;

  Graph G(N);//intialising graph parameters
  G.edge_input();//taking edges input
  G.kruskal();//running kruskal algorithm
  G.print_tree();//printing the SPANNING TREE
  return 0;
}
