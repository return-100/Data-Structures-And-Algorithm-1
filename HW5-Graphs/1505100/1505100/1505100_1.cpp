#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;

ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}

void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}

int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges, time ;
	bool directed ;
	ArrayList  * adjList ;
	int *color ;
	int *parent ;
	int *dist ;
	int *tin ;
	int *tout ;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfs(int source);
	void dfs_traversal();
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	color = 0 ;
	time = 0 ;
	tin = 0 ;
	tout = 0 ;
	parent = 0 ;
	time = 0 ;
	dist = 0 ;
	directed = dir ;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n;
	if(adjList!=0) delete[] adjList;
	if(color!=0) delete[] color;
	if(parent!=0) delete[] parent;
	if(tin!=0) delete[] tin;
	if(tout!=0) delete[] tout;
	if(dist!=0) delete[] dist;

	adjList = new ArrayList[nVertices];
	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
    tin = new int[nVertices];
    tout = new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;

    if(adjList[u].searchItem(v) != NULL_VALUE)
        --nEdges;

    adjList[u].removeItem(v);
    adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    return false;
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i = 0; i < adjList[u].getLength(); ++i)
    {
        if(i != v && adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE)
            return true;
    }

    return false;
}

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    parent[source] = source ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u = q.dequeue();

        for(int i = 0; i < adjList[u].getLength(); ++i)
        {
            int v = adjList[u].getItem(i);

            if(color[v] == WHITE)
            {
                color[v] = GREY;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.enqueue(v);
            }
        }

        color[u] = BLACK;
    }

    printf("Vertice No\tParent\tDistance From %d\n", source);

    for(int i = 0; i < nVertices; ++i)
    {
        printf("%d :\t\t%d\t\t%d\n", i, parent[i], dist[i]);
    }
}

void Graph::dfs_traversal()
{
    for(int i = 0; i < nVertices; ++i)
    {
        color[i] = WHITE;
        dist[i] = INFINITY;
        parent[i] = -1;
        tin[i] = tout[i] = 0;
    }

    for(int i = 0; i < nVertices; ++i)
    {
        if(color[i] == WHITE)
            parent[i] = i, dist[i] = 0, dfs(i);
    }

    printf("Vertice No\tParent\tStart Time\tFinish Time\n");

    for(int i = 0; i < nVertices; ++i)
    {
        printf("%d :\t\t%d\t\t%d\t\t%d\n", i, parent[i], tin[i], tout[i]);
    }
}

void Graph::dfs(int u)
{
    color[u] = GREY;
    tin[u] = ++time;

    for(int i = 0; i < adjList[u].getLength(); ++i)
    {
        int v = adjList[u].getItem(i);

        if(color[v] == WHITE)
        {
            parent[v] = u;
            dist[v] = dist[u] + 1;
            dfs(v);
        }
    }

    color[u] = BLACK;
    tout[u] = ++time;
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(color) delete[] color;
	if(parent) delete[] parent;
	if(dist) delete[] dist;
    if(tin) delete[] tin;
    if(tout) delete[] tout;
    if(adjList) delete[] adjList;

    color = 0;
    adjList = 0;
    dist = 0;
    tin = 0;
    tout = 0;
    parent = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("\n1. Add edge.             2. Remove Edge.  3. isEdge         4. Get Degree.\n");
        printf("5. Has Common Adjacent.  6. BFS.          7. Get Distance.  8. DFS.\n");
        printf("9. Print Graph           10. Exit.\n\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v))
                printf("There is a edge between %d and %d\n", u, v);
            else
                printf("There is no edge between %d and %d\n", u, v);
        }
        else if(ch==4)
        {
            int u;
            scanf("%d", &u);
            printf("The degree of vertex %d is %d\n", u, g.getDegree(u));
        }
        else if(ch==5)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v))
                printf("There is a common adjacent edge between %d and %d\n", u, v);
            else
                printf("There is no common adjacent edge between %d and %d\n", u, v);
        }
        else if(ch==6)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("The distance between %d and %d is %d\n", u, v, g.getDist(u, v));
        }
        else if(ch==8)
        {
            g.dfs_traversal();
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }
}
