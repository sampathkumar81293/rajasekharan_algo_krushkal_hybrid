#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define C1 1.5
#define C2 1.1
#define maxsize 100000000

// rajasekharan algorithm

/*declaration of structure for each point*/
typedef struct _point{
  double c,d,cost;
int id;
  struct _point *next;
}point;
typedef point *parray; /* array of points */
typedef point ***harray;/*hash table of pointers*/
typedef point **adjlist;/*adjacency list pointer has been allted.this ia a graph we have been generating..*/

typedef struct _edge{
int u,v;
double cost;

}edge;/*structure for edges of the graph*/

typedef struct _node{
int size;
struct _node *par;
}node;
typedef node *nodeptr;
nodeptr header[maxsize];

/*function for finding the distance between two points*/
double dist(point *A,point *B){
  double d;
  d=sqrt((A->c - B->c)*(A->c - B->c)+(A->d - B->d)*(A->d - B->d));
  return d;

}
double dist1(point p,point q){
double d;
d=sqrt((p.c-q.c)*(p.c-q.c)+(p.d)*(q.d)*(p.d)*(q.d));
return d;
}

/*

This has been over ruled..

void addlist(parray P,adjlist G,int n){
int i,j;double d1=C2/sqrt(n);

for (i=0;i<n;i++){

for(j=0;j<n;j++){

if(dist(P[i],P[j])<d1){ point *t;
    t=(point *)malloc(sizeof(point));
    t->c=P[j].c;
t->d=P[j].d;
t->id=P[j].id;
   t->next=G[i];
    G[i]=t; 
printf("entered (%lf,%lf.%d)",P[j].c,P[j].d,P[j].id);}

}
printf("\n");
}
}

*/
/*generating random points and hashing into hash table m x m grid*/
harray genRandomPoints ( int n, int m ,parray P)
{
   int i, j, k;
   double x, y;
   harray H;
   point *p;

   /* First create an m x m array of list headers */
   H = (harray)malloc(m * sizeof(point **));
   for (i=0; i<m; ++i) {
      H[i] = (point **)malloc(m * sizeof(point *));
      for (j=0; j<m; ++j) {H[i][j] =(point *)malloc(sizeof(point));H[i][j]=NULL;}
   }

   for (k=0; k<n; ++k) {
      /* Generate the x and y coordinates randomly in [0,1) */
      x = (double)rand() / ((double)RAND_MAX + 1);
      y = (double)rand() / ((double)RAND_MAX + 1);

      /*Locate the cell for (x,y) */
      i = (int)(x * (double)m); j = (int)(y * (double)m);

      /* Insert (x,y) in the (i,j)-th list */
      p = (point*)malloc(sizeof(point));
      P[k].c=p -> c = x;P[k].d= p -> d = y;P[k].id=p->id=k; p -> next = H[i][j];
      H[i][j] = p;
/*printf("inserted (%lf,%lf,%d)\n",P[k].c,P[k].d,P[k].id);*/
   }

   return H;
}



/*graph has been initialised*/
void initadjlist(adjlist G,int n){
int i=0;

for(i=0;i<n;i++){
G[i]=(point *)malloc(sizeof(point));
G[i]=NULL;

}
}


/*generation of graph from m x  m grid*/
int adjacencylist(parray P,harray H,adjlist G,int n)
{
		int cnt=0,i,k,a,b,r,j,m=ceil(sqrt(n));
		double d1=C1/sqrt(n);
		r=((int)(d1*(double)m));
for(k=0;k<n;k++)	
{
/*printf("entered loop for point %d-\n",k);*/
	a=  (int)((P[k].c )* (double)m);
	b= (int)((P[k].d ) * (double)m);
	point *t1,*t2;

 		t1=(point *)malloc(sizeof(point));
		t2=(point *)malloc(sizeof(point));
		t1=H[a][b];
	while(t1!=NULL){

         	if((t1->c==P[k].c )&& (t1->d==P[k].d) && (t1->id==P[k].id)) {

							t2=t1;/*printf("found (%lf,%lf,%d)\n",t2->c,t2->d,t2->id);*/ break;}
             t1=t1->next;
}

	for(i=-r;i<=r;i++){

         	for(j=-r;j<=r;j++){
		
           		if((a+i)<0 || (a+i)>(m-1) || (b+j)<0 || (b+j)>(m-1)) continue;
            
             		 point *t;
              		t=(point *)malloc(sizeof(point));
             		 t=H[a+i][b+j];
 
        while(t!=NULL){
 
             if(dist(t2,t)<=d1  && dist(t2,t)!=0){
			
/*printf("entered  p(%lf)\n",dist(t2,t));*/
   
   
			point *t3;
		t3=(point *)malloc(sizeof(point));
			t3->c=t->c;
			t3->d=t->d;
			t3->id=t->id;

                        t3->cost=dist(t2,t);
			t3->next=G[i];

			 G[i]=t3;cnt++;
							

				  }	         
		t=t->next;    }

		      }
		}
 


	}
printf("no edges formed in G is ; %d\n",cnt);
return cnt;}


/*creating edge list for eery vertices*/
void edgearray(edge *E,parray P,harray H,int n){



int k,i,r,j,a,b,cnt=0,m=ceil(sqrt(n));double d1=C1/sqrt(n);
r=((int)(d1*(double)m)); point *t;
              		t=(point *)malloc(sizeof(point));
for(k=0;k<n;k++)	
{
/*printf("entered loop for point %d-\n",k);*/
	a=  (int)((P[k].c )* (double)m);
	b= (int)((P[k].d ) * (double)m);
	point *t1,*t2;

 		t1=(point *)malloc(sizeof(point));
		t2=(point *)malloc(sizeof(point));
		t1=H[a][b];
	while(t1!=NULL){

         	if((t1->c==P[k].c )&& (t1->d==P[k].d) && (t1->id==P[k].id)) {

							t2=t1;/*printf("found (%lf,%lf,%d)\n",t2->c,t2->d,t2->id);*/ break;}
             t1=t1->next;
}

	for(i=-r;i<=r;i++){

         	for(j=-r;j<=r;j++){
		
           		if((a+i)<0 || (a+i)>(m-1) || (b+j)<0 || (b+j)>(m-1)) continue;
            
             		 point *t;
              		t=(point *)malloc(sizeof(point));
             		 t=H[a+i][b+j];
 
        while(t!=NULL){
 
             if(dist(t2,t)<=d1  && dist(t2,t)!=0){
			
printf("entered  p(%lf)\n",dist(t2,t));
   
   
   
			
			E[cnt].u=P[k].id;
			E[cnt].v=t->id;
			

                        E[cnt].cost=dist(t2,t);
			

			
							

			cnt++;	  }	         
		t=t->next;    }

		      }
		}
 


	}
}






/*kruskalsalgorithm*/
void heapify(edge *E,int n,int i){
int l,r,min;edge t;
while(1){
l=2*i+1;r=2*i+2;
if(l>(n-1)) return;
min=((r==n || (E[l].cost)<(E[r].cost)))?l:r;
if((E[min].cost)>E[i].cost) return;
t.cost=E[i].cost;t.u=E[i].u;t.v=E[i].v;
E[i].cost=E[min].cost;E[i].u=E[min].u;E[i].v=E[min].v;
E[min].cost=t.cost;E[min].u=t.u;E[min].v=t.v;
i=min;
}
}

void makeheap(edge *E,int n){
int i;
for(i=(n/2)-1;i>=0;i--){
heapify(E,n,i);}
}
void deletemin(edge *E,int n){
E[0].cost=E[n-1].cost;E[0].u=E[n-1].u;E[0].v=E[n-1].v;
heapify(E,n-1,0);
}
void heapsort(edge *E,int n){
int size;edge min;
makeheap(E,n);
for(size=n;size>1;size--){
min.cost=E[0].cost;min.u=E[0].u;min.v=E[0].v;
deletemin(E,size);
E[size-1].cost=min.cost;E[size-1].u=E[0].u;E[size-1].v=E[0].v;

}
}

void initset(int u){
nodeptr p;
p=(nodeptr)malloc(sizeof(node));p->size=1;p->par=p;header[u]=p;
}

/*nodeptr findset(int u){
r=header[u];
while(r!=r->par)r=r->par;return r;
}
*/
nodeptr findset(int u){
nodeptr p,q,r;
r=header[u];while(r!=r->par)r=r->par;
p=header[u];
while(p->par!=r){
q=p->par;p->par=r;p=q;
}
return r;
}

void mergesets(nodeptr r1,nodeptr r2){
nodeptr r;
if(r1->size<=r2->size) r=r1->par=r2;
else r=r2->par=r1;
r->size=r1->size + r2->size;
}

adjlist kruskalalgo(parray P,int n,int cnt,edge *E){
int u,v,i,ntrees,etot,e;adjlist T;
T=(adjlist)malloc(n*sizeof(point *));
for(i=0;i<n;i++){


T[i]=(point *)malloc(sizeof(point));
T[i]=NULL;}
nodeptr U,V;U=V=(nodeptr)malloc(sizeof(node));

for(i=0;i<n;i++) initset(P[i].id);
e=0;etot=0;
while(etot<(n-1)){

	if(e==cnt){printf("comeon\n");
		return T;exit(0);}
u=E[e].u;v=E[e].v;
U=findset(u);V=findset(v);
if(U!=V){

	 printf("Aded edge (%d,%d)to mst\n",u,v);
point *t1,*t2;t1=(point *)malloc(sizeof(point));t2=(point *)malloc(sizeof(point));
t1->id=u;t2->id=v;t1->c=P[u].c;t2->c=P[v].c;t1->d=P[u].d;t2->d=P[v].d;
t1->next=T[v];
	T[v]=t1;
t2->next=T[u];T[u]=t2;

mergesets(U,V);
etot++;
	}
++e;		
  			}
	


					}


findtrees(int *C,adjlist T,int n){

int i;point *t;t=(point *)malloc(sizeof(point));
for(i=0;i<n;i++){
t=T[i];while(t!=NULL){
C[i]++;
t=t->next;}

}

}


main()
{
  int n,m,i,cnt;
 
  srand((unsigned int)time(NULL));
   printf("enter Value of n \n n= "); scanf("%d", &n);
   if (n <= 0) {
      fprintf(stderr, "Number of intervals should be positive...\n");
      exit(1);
}

 /* here calculating m*/
   m=ceil(sqrt(n));printf("m=%d\n",m);
 harray H;adjlist G,T,T1;parray P;edge *E;E=(edge *)malloc(7*n*sizeof(edge));int *C;C=(int *)malloc(n*sizeof(int));

for(i=0;i<(7*n);i++){
E[i].cost=2.0;E[i].u=-1;E[i].v=-1;}
for(i=0;i<n;i++){
C[i]=0;
}

T1=T=(adjlist)malloc(n*sizeof(point *));
P=(parray)malloc(n*sizeof(point));
 G=(adjlist)malloc(n*sizeof(point *));
 
 H=(harray)malloc(n*sizeof(point **));
 H=genRandomPoints(n,m,P);
 
  initadjlist(G,n);
initadjlist(T,n);
initadjlist(T1,n);
cnt=adjacencylist(P,H,G,n);edgearray(E,P,H,n);
/*for(i=0;i<cnt;i++){
printf("%lf--->",E[i].cost);}*/
heapsort(E,cnt);for(i=0;i<cnt;i++){
printf("\n %lf--->",E[i].cost);}
T=kruskalalgo(P,n,cnt,E);/*findtrees(C,T,n);
for(i=0;i<n;i++){printf("\n C[%d]=%d",i,C[i]);}
*/







}
