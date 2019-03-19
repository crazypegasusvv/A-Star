#include<bits/stdc++.h>
using namespace std;

#define INF INT_MAX

struct node
{
	int x;                 // x co-ordinate of point or node 
	int y;                 //  y co-ordinate 
	int z;                // z co-ordinate
	int g;                //distance from source  to this point
	int h;                //heuristic or distance estimate from this point to destination
	bool cl;             //true if evaluated  or in closed list 
	bool op;            //true if in open list or being evaluated
	int index;           //index of point in graph
	node()
	{
		x=INF;
		y=INF;
		z=INF;
		g=INF;
		h=INF;
		cl=false;
    op=false;
		index=INF;
	}
};

bool manhattan=false;         //true if distance measure for heuristic is manhattan
bool euclidean=false;         //true if distance measure for heuristic is euclidean

struct mycomparator           //comparator 
{
	bool operator()(node const& l,node const& r)      //comparison function for priority queue 
	{
		if(l.g+l.h>r.g+r.h) return true;
		else if(l.g+l.h==r.g+r.h) return l.g>r.g;
		return false;
	}
};

/*
    macro for defining priority queue with priority based on sum of 'g' and 'h'
*/
#define  my_pq(l_name) priority_queue<node, vector<node>,mycomparator> l_name   

void fill_nodes(struct node plane[],int num)
{
	fstream fin;
	int xco,yco;
	fin.open("coord_input.txt");        //input file for co-ordinates of vertices
	for(int i=0;i<num;i++)
	{
		fin>>xco>>yco;
		plane[i].x=xco;
		plane[i].y=yco;
		plane[i].index=i;
	}
	fin.close();
}

void init_graph(vector< list<int> > &G,int num)
{
	fstream fin;
	fin.open("graph_input.txt");              //input file for representation of graph (adjacency list or adjacency matrix)
	int adjLen,vert;
	for(int i=0;i<num;i++) 
	{
		fin>>adjLen;
		list<int> list_;
		for(int j=0;j<adjLen;j++){
			fin>>vert;
			list_.push_back(vert);
		}
		G.push_back(list_);
		//for(int j=0;j<num;j++) fin>>G[i][j];
	}
	fin.close();
}

void print_graph(int **G,int num)
{
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++) cout<<G[i][j]<<" ";
		cout<<endl;
	}
}

void print_graph(vector< list<int> > G)
{
    for(int i=0;i<G.size();i++)
    {
        cout<<i;
        list<int>::iterator iter;
        for(iter=G[i].begin();iter!=G[i].end();iter++)
        {
            cout<<" " <<*iter;
        }
        cout<<endl;
    }
}

void print_nodes(struct node plane[],int num)
{
	cout<<endl;
	for(int i=0;i<num;i++)
	{
		cout<<plane[i].x<<" "<<plane[i].y<<endl;
	}
	cout<<endl;
}

int euclidean_distance(node a,node b)
{
	return (int)sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int manhattan_distance(node a,node b)
{
	return abs(a.x-b.x)+abs(a.y-b.y);
}
int distance(node a,node b)           //calls distance measure as chosen 
{
	if(euclidean==true) return euclidean_distance(a,b);
	if(manhattan==true) return manhattan_distance(a,b);
}

void calculate_h(node plane[],int num,int dest)     //calculates heuristic from the current point to destination
{
	for(int i=0;i<num;i++)
	{
		plane[i].h=distance(plane[i],plane[dest]);
	}
}
