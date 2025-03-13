// Name:Francis Miadi
// ID: 1210100
// section:4

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


#define MinQueueSize 15

// Queue data structure
struct QueueRecord{
int Capacity;
int Front;
int size;
int Rear;
int* Array;
};

typedef struct QueueRecord * Queue;

int isEmpty(Queue );
int isFull( Queue  );
Queue CreateQueue (int );
void MakeEmpty (Queue );
void DisposeQueue(Queue );
int Succ(int  , Queue );
void Enqueue(int  , Queue );
int Front(Queue );
void Dequeue(Queue );
int FrontAndDequeue(Queue );


int getCityCode (char[]);
char* getCityName(int);
int** createAdjMatrix(int ,int);
int** Load(int** AdjM,int mode);
int sizeOfFile(); // a function for calculation the size of the file
void Dijkstra(int** map,int srcV,int destination,int mode);
void printPath(int**,int startPoint,int endPoint,int pre[],int distance[],int mode);
void BreadthFSearch(int** map,int startpoint,int endpoint,int mode);

int main()
{
    char src[15];
    char dest[15];
    int intSrc,intDest;
int** arr1=createAdjMatrix(16,16);// 2D array to store the graph with distances for dijkstra
int** arr2=createAdjMatrix(16,16);// @d array to store the ones graph for the BFS
int i,j;
int key;


/*for ( i = 1; i < 16; i++) {
        for ( j = 1; j < 16; j++) {
            printf("%d ", arr1[i][j]);
        }
        printf("\n");
    }
        printf("\n\n");

    for ( i = 1; i < 16; i++) {
        for ( j = 1; j < 16; j++) {
            printf("%d ", arr2[i][j]);
        }
        printf("\n");
    }*/


int op,k;

printf("NOTE: YOU SHOULD CHOOSE THE OPTIONS IN THE GIVEN OREDER\n");
printf("(it is not a menu ,it is a program with consecutive steps)\n");
 printf("FOR EXAMPLE: YOU CAN'T CHOOSE OPTION NUMBER 2 BEFORE NUMBER 1\n");
    /* printf("choose:\n");
     printf("1- Load cities\n");
     printf("2- Enter the source city\n");
     printf("3- Enter destination \n");
     printf("4- Exit a print to file\n");
scanf("%d",&op);*/

do{
printf("choose:\n");
     printf("1- Load cities\n");
     printf("2- Enter the source city\n");
     printf("3- Enter destination \n");
     printf("4- Exit and print to file\n");
     scanf("%d",&op);

        switch(op){
  case 1:{
                 arr1=Load(arr1,0);
                arr2=Load(arr2,1);
                printf("Load process is done successfully\n");
                break;
  }
  case 2:{
   printf(" Enter the name of the city that you are going from:\n");
scanf("%s",&src);
intSrc=getCityCode(src);
break;
  }
  case 3:{

  printf(" Enter the name of the city that you are going to:\n");
scanf("%s",&dest);
intDest=getCityCode(dest);
printf("\nPATHS:\n");
  Dijkstra(arr1,intSrc,intDest,0);
BreadthFSearch(arr2,intSrc,intDest,0);
Dijkstra(arr1,intSrc,intDest,1);

BreadthFSearch(arr2,intSrc,intDest,1);
break;
  }
case 4:{
  k=-1;

break;
}
default:printf("No Such Option\n");
}
}while(k!=-1);

    return 0;
}
 /*the following function for returning the code of each city
 i gave each city a code, which will make the search process in the graph much easier
 in which i can deal with the cities as integers
 */

int getCityCode (char name[]){
    if(strcmp(name,"Akka")==0)                  return 1;
    else if(strcmp(name,"Bethlehem")==0)        return 2;
    else if(strcmp(name,"Haifa")==0)            return 3;
    else if(strcmp(name,"Hebron")==0)           return 4;
    else if(strcmp(name,"Jaffa")==0)            return 5;
    else if(strcmp(name,"Jenin")==0)            return 6;
    else if(strcmp(name,"Jericho")==0)          return 7;
    else if(strcmp(name,"Jerusalem")==0)        return 8;
    else if(strcmp(name,"Nablus")==0)           return 9;
    else if(strcmp(name,"Nazareth")==0)         return 10;
    else if(strcmp(name,"Qalqilya")==0)         return 11;
    else  if(strcmp(name,"Ramallah")==0)        return 12;
    else  if(strcmp(name,"Salfit")==0)          return 13;
    else  if(strcmp(name,"Tubas")==0)           return 14;
    else if(strcmp(name,"Tulkarem")==0)         return 15;
    else printf("No Such city in our records\n");
}
/*
The following is for getting the name of the city by passing it's city code to it
so i can print the name of the cities after the path constructing process ends
*/
char* getCityName(int code){
    if(code==1)                  return "Akka";
    else if(code==2)             return "Bethlehem";
    else if(code==3)             return "Haifa";
    else if(code==4)             return "Hebron";
    else if(code==5)             return "Jaffa";
    else if(code==6)             return "Jenin";
    else if(code==7)             return "Jericho";
    else if(code==8)             return "Jerusalem";
    else if(code==9)             return "Nablus";
    else if(code==10)            return "Nazareth";
    else if(code==11)            return "Qalqilya";
    else  if(code==12)           return "Ramallah";
    else  if(code==13)           return "Salfit";
    else  if(code==14)           return "Tubas";
    else if(code==15)            return "Tulkarem";
        else printf("No Such city in our records\n");

}
/*
A function for creating a 2D Array t represent the graph
i used the pointers way because for me it is easier to deal with it while
passing to functions and returning from them
*/
int** createAdjMatrix(int m ,int n){
    int* values = calloc(m*n, sizeof(int));
    int** rows = malloc(m*sizeof(int*));
    for (int i=0; i<m; ++i)
    {
        rows[i] = values + i*n;
    }
    return rows;
}
/*
Load function, to load the graph
this function is controlled by a mode switch
in which if the mode is 0 ,it will load the graph with the distances from the file
but if it is  1 it will load the graph with 1's in the positions of distances
*/
int** Load(int** AdjM,int mode){

FILE *in;
in = fopen("cities.txt","r");
char destination[40];
char source[40];
char values[10];
char temp[10];
char temp2[10];
int i=0,src,dest,value;
// scanning the city names and the distance between them,line by line
while(i<sizeOfFile()){
    fscanf(in,"%s",source);
        src=getCityCode(source);
fscanf(in,"%s",destination);
    dest= getCityCode(destination);
fscanf(in,"%s",values);
 strncpy(temp,values,3);
// here i check if the distance is one or two or three digits
 if(isdigit(temp[0])&&isdigit(temp[1])&&isdigit(temp[2])){
        value =atoi(temp);

 }
 else if(isdigit(temp[0])&&isdigit(temp[1])&&!isdigit(temp[2])){

    strncpy(temp2,temp,2);
        value =atoi(temp2);

 }
 else if((isdigit(temp[0]))&&(!isdigit(temp[1]))&&(!isdigit(temp[2]))){
int num = temp[0];
value = num-48;
 }
// the mode control part
    if(mode==0){
    AdjM[src][dest]=value;
    }
    else if (mode==1){
            AdjM[src][dest]=1;
    }
    i++;
}
fclose(in);
return AdjM;
}
int sizeOfFile(){ // a function for calculation the size of the file
    char x;         // in other words the number of numbers in the file
    int count=0;
FILE *IN;
IN=fopen("cities.txt","r");                 //  checking the file validity steps
if(IN == NULL){
    printf("ERROR-can't open the file");
    exit(1);
}
while((x=fgetc(IN))!=EOF){//counting until reaching the end of file
    if(x=='\n')
        count++;
}
fclose(IN);

return count;

}
/*
This code implements Dijkstra's algorithm to find the shortest paths from a source vertex
to the destination vertex
it explores the edge with the less weight in  each step without giving notice to what this edge could lead to
and because of that we call it a greedy algorithm
*/
void Dijkstra(int** map,int srcV,int destination,int mode){

int cost[15];// to store the distance
int visited[15];// to check a vertex as visited
int pre[15];// to store the vertex that we came from
int stopFlag=0,minDist=0,nextVertex;
for(int i=1;i<=15;i++)// initializing the previous three arrays
	{
	    if(map[srcV][i]==0)
            cost[i]=1000;// setting the initial cost to 1000, because it should be a value that we won't reach more than it
        else
		cost[i]=map[srcV][i];

		pre[i]=srcV;
		visited[i]=0;// set all vertices as unvisited

	}

cost[srcV]=0;

	visited[srcV]=1;// set the source vertex as visited
stopFlag=1;
while(stopFlag<15)
	{
		minDist=1000;
    for(int j=1;j<16;j++){
        if((cost[j]<minDist)&&!visited[j])// if the new cost is less than the current , update the cost
			{
//printf("test1");
				minDist=cost[j];
            nextVertex=j;

			}
    }
			visited[nextVertex]=1;
    for(int k=0;k<16;k++)
        if(!visited[k])
            // for an unvisited vertex,we check if the distance that we reached to it by it is less than the current cost led to it
            if(((minDist+map[nextVertex][k])<cost[k])&&map[nextVertex][k]&&(minDist!=1000))
            {
                //printf("test2");

                cost[k]=minDist+map[nextVertex][k];// setting the new cost to the new cost
            pre[k]=nextVertex;// put this vertex in the pre, so it will be a parent for the next vertex ,that we will reach for it
					}           // by this vertex
		stopFlag++;
	}
 printPath(map,srcV,destination,pre,cost,mode);
}
/*
a function to print the shortest path between to given verticies (the path is found by dijkstra algorithm)
*/
void printPath(int**map,int startPoint,int endPoint,int pre[],int distance[],int mode){
int j,k=0;
int path[15];// an array to store the path's cities codes as indicies

for(j=0;j<16;j++)
path[j]=0;
if(mode ==0){
    printf("\n By Dijkstra Algorithm:-\n");

printf("\nDistance from %s to %s = %d Km\n",getCityName(startPoint),getCityName(endPoint),distance[endPoint]);
			j=endPoint; // we go in reverse order in the pre array
			do          // from the destination to the source
			{
				j=pre[j];
				path[k]=j;// fill the path array by using the pre content
                k++;
			}while(j!=startPoint);


                printf(" %s ",getCityName(endPoint));
				printf(" <(%d Km)",map[path[0]][endPoint]);

                k=0;
			j=endPoint;
// again from the destination to the source
            do
			{
				j=pre[j];

				printf("- %s",getCityName(path[k]));// we print the cities that constructs the shortest path
								if(path[k]!=startPoint)

				printf(" <(%d Km)",map[path[k+1]][path[k]]);// we get the distance between the consecutive two cities from the adjacency matrix
k++;

			}while(j!=startPoint);
}
// the same steps but for printing in the file
else if(mode==1){
        FILE *out;
out = fopen("shortest_distance.txt","a");

    fprintf(out," By Dijkstra Algorithm:-\n");

fprintf(out,"\nDistance from %s to %s = %d Km\n",getCityName(startPoint),getCityName(endPoint),distance[endPoint]);
			j=endPoint;
			do
			{
				j=pre[j];
				path[k]=j;
                k++;
			}while(j!=startPoint);


							fprintf(out," %s ",getCityName(endPoint));
				fprintf(out," <(%d Km)",map[path[0]][endPoint]);

                k=0;
			j=endPoint;

            do
			{
				j=pre[j];

				fprintf(out,"- %s",getCityName(path[k]));
				if(path[k]!=startPoint)
				fprintf(out," <(%d Km)",map[path[k+1]][path[k]]);

k++;

			}while(j!=startPoint);



}

	}
// BFS or Breadth First Search Algorithm works as follows
/*
Starting from a given source vertex, BFS visits all its neighbors before moving on to their neighbors.
It uses a queue data structure to keep track of the vertices to be visited.
The algorithm begins by enqueueing the source vertex and marking it as visited.
Then, it enters a loop that continues until the queue is empty.
In each iteration, a vertex is dequeued, visited, and its unvisited neighbors are enqueued.
The process repeats until all vertices have been visited.
*/
void BreadthFSearch(int** map,int startpoint,int endpoint,int mode){

int Edges[15];
int step=1;
int visited[15];
int pre[15];
int vertex,i,j;
  for ( i = 1; i <16; i++) {
    visited[i] = 0;
    Edges[i]=1000;
    pre[i]=0;

  }
  Queue Q = CreateQueue(15);

  visited[startpoint]=1;
  Enqueue(startpoint,Q);// we add the starting point to the queue
Edges[startpoint]=0;
  while(!isEmpty(Q)){
    vertex = FrontAndDequeue(Q);
if(vertex == endpoint) // if we reach the destination , we break out of the loop
    break;
// after we dequeue an element from the queue, we start to check it's neighbors , if is not visited
// we enqueue it , and set the original not vertex as visited
    for(i=1;i<16;i++){
        if(map[vertex][i]&&!visited[i]){
            visited[i]=1;
            Edges[i]=Edges[vertex]+1;// we increase the number of edges for this vertex
                        pre[i]=vertex;
            Enqueue(i,Q);
        }
    }

  }
int temp=endpoint;
// we start printing from the end point and go back until we reach the starting point
if(mode ==0){
                printf("\nPath by Breadth First Search Algorithm:- \n\n");

while(temp!=startpoint){
if(temp == endpoint)
    printf("   %s",getCityName(temp));
    else     printf("  <- %s",getCityName(temp));

    temp=pre[temp];
    if(temp == startpoint)
        printf(" <- %s",getCityName(startpoint));

}
printf("\nNumber of Edges = %d\n\n ",Edges[endpoint]);// to print the number of edges that we have needed to reach the destination
}
// the same printing part but this one is for the file printing
else if(mode==1){
    FILE *out;
out = fopen("shortest_distance.txt","a");
        fprintf(out,"\n\nPath by Breadth First Search Algorithm:- \n\n");

 while(temp!=startpoint){
if(temp == endpoint)
    fprintf(out,"   %s",getCityName(temp));
    else     fprintf(out,"  <- %s",getCityName(temp));

    temp=pre[temp];
    if(temp == startpoint)
        fprintf(out," <- %s",getCityName(startpoint));

}
fprintf(out,"\nNumber of Edges = %d\n\n ",Edges[endpoint]);

}

}

int isFull( Queue q ){return q->size==q->Capacity;}
int isEmpty(Queue q){return q->size==0;}
Queue CreateQueue (int MaxElements){
Queue q;
if(MaxElements < MinQueueSize)
    printf("the size is too small!");
    else{
q= (struct QueueRecord*)malloc(sizeof (struct QueueRecord));
if(q==NULL)
    printf("out of space!");

q->Array = (int*)malloc(sizeof(int)*MaxElements);
if(q->Array == NULL)
        printf("out of space!");
q->Capacity = MaxElements;
MakeEmpty(q);
    }
return q;
}
void MakeEmpty (Queue q){
q->Front =1;
q->Rear = 0;
q->size =0;

}
void DisposeQueue(Queue q){
if(q!=NULL)
{
free(q->Array);
free(q);
}
}
int Succ(int value , Queue q){
if(++value == q->Capacity)
    value = 0;
return value;
}
void Enqueue(int x , Queue q){
if(isFull(q))
    printf ("out of space!");
else {
    q->size++;
    q->Rear = Succ(q->Rear ,q);
    q->Array[q->Rear]=x;
}
}

int Front(Queue q){
if(!isEmpty(q))return q->Array[q->Front];
else {
        printf("the queue is empty");return 0;
}
}

void Dequeue(Queue q){
if(!isEmpty(q)){
    q->size--;
    q->Front = Succ(q->Front,q);
}
    else {
        printf("the queue is empty");
    }

}
int FrontAndDequeue(Queue q){
int x=0;
if(!isEmpty(q)){
    q->size--;
    x= q->Array[q->Front];
    q->Front = Succ(q->Front,q);}
    else {
        printf("the queue is empty");
    }
return x;
}




