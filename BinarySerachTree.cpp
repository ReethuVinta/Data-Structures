#include<bits/stdc++.h>
using namespace std;

struct node //strcuture to maintain each node in BST
{
  int val;
  struct node*left;
  struct node*right;
};
node* ROOT=NULL;//intialising ROOT to zero

node *newnode(int x)
{
  node*temp=new(node);
  temp->val=x;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

node* insert(node*temp,int x)//inserting element into the BST
{
  if(temp==NULL)
  {
    temp=newnode(x);
  }
  if(x<temp->val)
  {
    temp->left=insert(temp->left,x);//if x is less than the current node value go to the left of this node
  }
  else if(x>temp->val)
  {
    temp->right=insert(temp->right,x);//if x is greater than the current node value go to the right of this node
  }
  return temp;
}

void inorder(node *temp)
{
  if (temp == NULL)
    return;
  inorder(temp->left);
  cout << temp->val << " ";
  inorder(temp->right);
}

node* min(node *temp)//find the value of minimum element in this subtree
{
  node *current=temp;
  while(current->left!=NULL)
  {
    current=current->left;
  }
  return current;
}

node* max(node *temp)//find the value of minimum element in this subtree
{
  node* current=temp;
  while(current->right!=NULL)
  {
    current=current->right;
  }
  return current;
}

node* search(node *temp,int x)//finds the value of element x in the BST
{
  if(temp==NULL || temp->val==x)
  {
    return temp;
  }
  else if(x>temp->val)
  {
    return search(temp->right,x);
  }
  else
  {
    return search(temp->left,x);
  }
}

void M(int x)//prints the minimum,maximum element in the subtree of x
{
  node *temp=search(ROOT,x);
  if(temp==NULL)cout<<"No such element is present in BST"<<endl;
  else cout<<"MIN "<<min(temp)->val<<" "<<"MAX "<<max(temp)->val<<endl;
}

node* succ(int x)//finds the successor of element x
{
    node*temp=search(ROOT,x);
    if(temp==NULL)return NULL;
    if(temp->right!=NULL)
    {
      return min(temp->right);
    }
    node *succ=NULL;
    node*current=ROOT;
    while(current!=NULL)
    {
      if(current->val > temp->val)
      {
        succ=current;
        current=current->left;
      }
      else if(current->val < temp->val)
      {
        current=current->right;
      }
      else break;
    }
    return succ;
}

node *pred(int x)//finds predecessor of element x
{
  node* temp=search(ROOT,x);
  if(temp==NULL)return NULL;
  if(temp->left!=NULL)
  {
    return max(temp->left);
  }
  node*pred=NULL;
  node*current=ROOT;
  while(current!=NULL)
  {
    if(current->val < temp->val)
    {
      pred=current;
      current=current->right;
    }
    else if(current->val > temp->val)
    {
      current=current->left;
    }
    else break;
  }
  return pred;
}

node*LCA(node *temp,int a,int b)//finds least common ancestor of element a and b
{
  if(temp==NULL)return temp;
  if(temp->val >a && temp->val >b)
  {
    return LCA(temp->left,a,b);
  }
  if(temp->val <a && temp->val <b)
  {
    return LCA(temp->right,a,b);
  }
  return temp;
}


int main()
{
  string input;
  int x;
  getline(cin,input);
  stringstream take(input);
  while(take>>x)
  {
    ROOT=insert(ROOT,x);//inserting elements into the BST
  }

  string check;
  getline(cin,check);
  while(check.length()!=0)
  {
    char function;
    int m,n;
    stringstream take(check);
    take>>function;
    take>>m;
    take>>n;
    switch(function)
    {
      case 'M': M(m);
                break;
      case 'P' :if(pred(m)==NULL)cout<<"NO PREDECESSOR"<<endl;
                else cout<<pred(m)->val<<endl;
                break;
      case 'S' :if(succ(m)==NULL)cout<<"NO SUCCESSOR"<<endl;
                else cout<<succ(m)->val<<endl;
                break;
      case 'C': if(LCA(ROOT,m,n)==NULL)cout<<"NO LEAST COMMON ANCESTOR"<<endl;
                else cout<<LCA(ROOT,m,n)->val<<endl;
                break;
      default: break;
    }
    getline(cin,check);
  }

}
