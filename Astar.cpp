#include "star_helper.h" //header file for helper functions like input and initialising data structures

/*this function prints the path from destination to source */
void construct_path(vector<int> cameFrom,int curIndex)
{
	cout<<endl;
	cout<<"path is:\n";
	while(curIndex!=INF)
	{
		cout<<curIndex<<" ";	
		curIndex=cameFrom[curIndex];    //getting predecessor of node in shortest path
	}
	cout<<endl;
}

/* the search function*/
void AStar(int src,int dest,vector< list<int> > G,struct node plane[],int num)
{

  /* 
      open_list is priority queue of nodes based on sum of distance measure 'g' and
      heuristic estimate 'h' 
      my_pq() is a macro for defining the priority queue
      
  */
	my_pq(open_list);   
  
  
	plane[src].op=true;         //marking source node as in open list
  
  
	plane[src].g=0;             //distance from source to itself is zero
  
  
	open_list.push(plane[src]); //adding source destination to the open list
  
	vector<int> cameFrom;       //vector for storing best predecessor in the path
	cameFrom.resize(num,INF);   //initializing vector with size=no. of nodes
  
  /*
  
    continue until there is no node in priority queue
    implies exhaustion of search 
    
  */
  
  while(!open_list.empty())
	{
  
    /*
    
      the node which is closest or has lowest 'f'
      where 'f=g+h' in the priority queue
      
    */
		struct node current=open_list.top(); 
    
    
    /*
      destination node is reached in the  priority queue
      implies search is success
    */
		if(current.index==dest)                 
		{
			construct_path(cameFrom,current.index);  //routine for printing path from destination to source
			return;
		}
    
    
		int cur_index=current.index;
    
		plane[cur_index].op=false;        //removing node from open list
		open_list.pop();                    
    
		plane[cur_index].cl=true;         //adding the node to closed list


		list<int>::iterator iter;         //iterator for accessing vertices in adjacency list
		for(iter=G[cur_index].begin();iter!=G[cur_index].end();iter++) {
			int i=*iter;
			if(plane[i].cl==true) continue;                               //if node is already in closed list (or evaluated)
				int temp_g=current.g+distance(plane[cur_index],plane[i]);  //sum of estimate and distance
        
				if(plane[i].op==false)                                    //if node is not in open list already
				{
        	cameFrom[i]=cur_index;                                  //updating predecessor of node in what would be a shortest path
					plane[i].g=temp_g;                                      //distance measure
					plane[i].h=distance(plane[i],plane[dest]);              //heuristic
					open_list.push(plane[i]);                               //adding node to open list
				}
				else if(temp_g>=plane[i].g) continue;                      //adjacent vertex is not optimal to include in shortest path
		}
		/*for(int i=0;i<num;i++)
		{
			if(G[cur_index][i]==1)
			{
				if(plane[i].cl==true) continue;
				int temp_g=current.g+distance(plane[cur_index],plane[i]);
				if(plane[i].op==false) 
				{
					cameFrom[i]=cur_index;
					plane[i].g=temp_g;
					plane[i].h=distance(plane[i],plane[dest]);
					open_list.push(plane[i]);
				}
				else if(temp_g>=plane[i].g) continue;
			}
		}*/
	}  
	cout<<"\nNo Path\n";     
}

int main()
{
	list<node> closed_list;
	int st,en,num;
	cout<<"enter no. of objects: ";
	cin>>num;
	node plane[num];
	fill_nodes(plane,num);

	vector< list<int> > G;
	/*int **G;
	G=new int*[num];
	for(int i=0;i<num;i++) G[i]=new int[num];*/
	init_graph(G,num);
	
	cout<<"choose the distance measure:\n1.Euclidean\n2.Manhattan\n";
	int inp_d;
	cin>>inp_d;
	if(inp_d==1) euclidean=true;
	else if(inp_d==2) manhattan=true;
	cout<<"enter source index: ";
	cin>>st;
	cout<<"enter destination index: ";
	cin>>en;
	AStar(st,en,G,plane,num);
	return 0;
}



