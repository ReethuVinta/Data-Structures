#include<bits/stdc++.h>
using namespace std;

struct Adjnode//stucture that stores vertice and weight
{
  int val;
  int weight;
  Adjnode* next;
};

struct graphedge//strcuture that stores edges vertices and edge weight
{
  int begin;
  int end;
  int wei;
  graphedge* next;
};

class Graph//GRAPH class
{
public:
  Adjnode** adj;//to maintain the track of undirected graph
  graphedge* HEAD;
  int vertices;
  Graph(int q)
  {
      this->vertices=q;
      adj = new Adjnode*[q];
      HEAD=NULL;
  }

  void setgraphedge()//takig graphedges input from user
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
      if(HEAD==NULL)HEAD=node;//creating linked list of edges
      else prev->next=node;
      prev=node;
      getline(cin,input);
    }
    cout<<"done taking edges"<<endl;
  }

  void printedges()//printgin edges present in the graph
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

  void construct_graph()//constructing undirected graph from the edges given by the user
  {
    for(int i=0;i<vertices;i++)
    {
      adj[i]=NULL;
    }
    graphedge* current=HEAD;
    while(current!=NULL)
    {
        int start_ver = current->begin;
        int end_ver = current->end;
        int weight =current->wei;
        Adjnode* newNode =setvertices(end_ver, weight, adj[start_ver]);
        adj[start_ver] = newNode;

        start_ver = current->end;
        end_ver = current->begin;
        weight =current->wei;
        newNode =setvertices(end_ver, weight, adj[start_ver]);
        adj[start_ver] = newNode;
        current=current->next;
      }
  }

  void display()//dsplaying the adjacency list of graph
  {
    for(int i=0;i<vertices;i++)
    {
        Adjnode* ptr;
        ptr=adj[i];
        while(ptr!=NULL)
        {
          cout<<i<<","<<ptr->val<<" "<<ptr->weight<<" ";
          ptr=ptr->next;
          cout<<endl;
        }
    }
 }

 void neighbours(int x)//function that finds neighbours of vertex x
 {
   Adjnode* ptr=adj[x];
   if(ptr==NULL)
   {
     cout<<"no neighbours"<<endl;
   }
   else
   {
     while(ptr!=NULL)
     {
       cout<<ptr->val<<" ";
       ptr=ptr->next;
     }
     cout<<endl;
   }
 }

 void totalvertices()//prints all the vertice present in the graph
 {
   for(int i=0;i<vertices;i++)
   {
     if(adj[i]!=NULL)cout<<i<<" ";
   }
   cout<<endl;
 }

 void edgeweight(int v1,int v2)//funciotn that finds the edge weight between v1 and v2
 {
   if(v1>=vertices || v2>=vertices)cout<<"given vertices are out of bound"<<endl;

   int weigth_obtained=0;
   auto ptr=adj[v1];
   while(ptr!=NULL)
   {
     if(ptr->val==v2)
     {
       weigth_obtained=ptr->weight;
       break;
     }
     ptr=ptr->next;
   }
   if(weigth_obtained==0)cout<<"no edge between them"<<endl;
   else cout<<weigth_obtained<<endl;
 }

 void vertexcheck(int v)//funciotn that checks whether vertex v is present in graph or not
 {
   if(adj[v]==NULL)cout<<"Given Vertex not present"<<endl;
   else cout<<"Given Vertex is present"<<endl;
 }

 bool containedge(int v1,int v2)//function that checks whether there is an edge between v1 and v2
{
    if(v1>=vertices || v2>=vertices)
      return 0;
    auto ptr=adj[v1];
    while(ptr!=NULL)
    {
      if(ptr->val==v2)return 1;
      ptr=ptr->next;
    }
    auto itr=adj[v2];
    while(itr!=NULL)
    {
      if(itr->val==v1)return 1;
      itr=itr->next;
    }
    return 0;
}
};

int main()
{
  int N;
  string M;
  getline(cin,M);
  stringstream take(M);
  take>>N;

  Graph G(N);
  G.setgraphedge();
  G.construct_graph();

  string input;
  getline(cin,input);
  while(input.length()!=0)
  {
    char S;
    int v1,v2;
    stringstream take(input);
    take>>S;
    take>>v1;
    take>>v2;
    switch(S)
    {
     case'a':  if(v1>=G.vertices)cout<<"vertice outof bound"<<endl;
               else G.neighbours(v1);
               break;
     case 'b': G.totalvertices();
               break;
     case 'c' :if(v1>=G.vertices || v1>=G.vertices )cout<<"vertices outof bound"<<endl;
               else G.edgeweight(v1,v2);
               break;
     case 'd' : if(v1>=G.vertices)cout<<"vertice outof bound"<<endl;
                else G.vertexcheck(v1);
                break;
     case 'e': if(v1>=G.vertices || v1>=G.vertices )cout<<"vertices outof bound"<<endl;
               else
               {
                 if(G.containedge(v1,v2)==0)cout<<"No edge"<<endl;
                 else cout<<"edge is present"<<endl;
               }
    }
    getline(cin,input);
  }

  return 0;
}
