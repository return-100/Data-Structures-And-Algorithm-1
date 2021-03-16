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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges, time ;
	bool directed ;
	int ** matrix ;
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
	void dfs();
	void dfs_traversal(int u);
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
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
	this->nVertices = n ;
	color = new int[nVertices];
	parent = new int[nVertices];
	dist = new int[nVertices];
    tin = new int[nVertices];
    tout = new int[nVertices];
    matrix = new int*[nVertices];

    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0;
    }
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    ++nEdges;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    if(matrix[u][v] || matrix[v][u])
        --nEdges;

    matrix[u][v] = 0;
    matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    return matrix[u][v] || matrix[v][u];
}

int Graph::getDegree(int u)
{
    int cnt = 0;

    for(int i = 0; i < nVertices; ++i)
    {
        if(matrix[u][i])
            ++cnt;
    }

    return cnt;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i = 0; i < nVertices; ++i)
    {
        if(matrix[u][i])
        {
            if(matrix[i][v] || matrix[v][i])
                return true;
        }
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

        for(int i = 0; i < nVertices; ++i)
        {
            if(matrix[u][i] && color[i] == WHITE)
            {
                color[i] = GREY;
                dist[i] = dist[u] + 1;
                parent[i] = u;
                q.enqueue(i);
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

void Graph::dfs()
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
            parent[i] = i, dist[i] = 0, dfs_traversal(i);
    }

    printf("Vertice No\tParent\tStart Time\tFinish Time\n");

    for(int i = 0; i < nVertices; ++i)
    {
        printf("%d :\t\t%d\t\t%d\t\t%d\n", i, parent[i], tin[i], tout[i]);
    }
}

void Graph::dfs_traversal(int u)
{
    color[u] = GREY;
    tin[u] = ++time;

    for(int i = 0; i < nVertices; ++i)
    {
        if(matrix[u][i] && color[i] == WHITE)
        {
            parent[i] = u;
            dist[i] = dist[u] + 1;
            dfs_traversal(i);
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
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
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
    if(matrix)
    {
        for(int i = 0; i < nVertices; ++i)
            delete matrix[i];
        delete[] matrix;
    }

    color = 0;
    matrix = 0;
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
            g.dfs();
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

/*
10
1 0 6
1 6 5
1 0 3
1 0 4
1 6 9
1 7 8
1 4 8
1 3 8
1 6 7
1 7 2
1 9 1
*/
