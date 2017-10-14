#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int v,w,peso;
    Edge(int v=-1,int w=-1,int peso=-1){
        this->v=v;
        this->w=w;
        this->peso=peso;
    }
};

struct Graph{
    vector <vector <int > > adj;
    int Vcnt, Ecnt;
    bool digraph;
    int V() const{
        return Vcnt;
    }
    int E() const{
        return Ecnt;
    }
    int insert (Edge edge1){
        if(adj[edge1.v][edge1.w]==-1){
            adj[edge1.v][edge1.w]=edge1.peso;
            Ecnt++;
        }
    }

    bool edge(int a,int b){
        return adj[a][b];
    }

    Graph(int V, bool digraph = true) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph) {
        for (int i =0; i < V; i++)
            adj[i].assign(V, -1);
    }

    class adjIterator{
    public:
        const Graph &G;
        int i, v;
        adjIterator(const Graph &G, int v) :  G(G), v(v), i(-1) { }
        int beg() {
            i = -1; return nxt();
        }
        int nxt() {
            for (i++; i < G.V(); i++)
                if (G.adj[v][i] == true)
                    return i;
            return -1;
        }
        bool end() {
            return i >= G.V();
        }
    };
};


template <class Graph>
vector <Edge> edges(Graph &G) {
    int E = 0;
    vector <Edge> a(G.E());
    for (int v = 0; v < G.V(); v++) {
        typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt())
            if (G.directed() || v < w)
                a[E++] = Edge(v, w);
    }
    return a;
}

template <class Graph>
void show(const Graph &G) {
    for (int s = 0; s < G.V(); s++) {
        cout.width(2); cout << s << ":";
        typename Graph::adjIterator A(G, s);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            cout.width(2); cout << t << " ";
        }
        cout << endl;
    }
}

template <class Graph>
void printMatrix(const Graph &G) {
    for (int s = 0; s < G.V(); s++) {
        for (int t = 0; t < G.V(); t++) {
            cout<<G.adj[s][t];
            cout.width(2);
        }
        cout << endl;
    }
}


void printVectorArray(vector<int*>v){
    for(int a=0;a<v.size();a++){
        if(v[a]==NULL)
            cout<<"-,- | ";
        else
            cout<<v[a][0]<<","<<v[a][1]<<" | ";
    }
    cout<<endl;
}


void printVector(vector<int>v){
    for(int a=0;a<v.size();a++){
        cout<<v[a]<<" ";
    }
    cout<<endl;
}
bool findInVector(vector<int>v,int x){
    for(int a=0;a<v.size();a++)
        if(v[a]==x)
            return true;
    return false;
}

void printCamino(vector<int*>v,int fin){
    vector<int>camino;
    camino.push_back(fin);
    if(v[fin]==NULL)
        cout<<"No hay camino"<<endl;
    else
        while(v[fin][1]!=-1){
            camino.insert(camino.begin(),v[fin][1]);
            fin=v[fin][1];
        }
    printVector(camino);
}

void dijkstra(Graph G,int ini,int fin){
    vector<int*>camino(G.V(),NULL); //Elementos de camino
    vector<int>temp; //Vertices temporales para ir visitando
    int t1[2]={0,-1};
    camino[ini]=t1;
    temp.push_back(ini);
    while(temp.size()>0){
        for(int tfin=0;tfin<G.V();tfin++){
            int pesoTfin=G.adj[temp[0]][tfin];
            if(pesoTfin>0){
                //cout<<" - "<<pesoTfin<<" -> "<<tfin<<endl;
                if(camino[tfin]==NULL or pesoTfin+camino[temp[0]][0]<camino[tfin][0]){
                    int* arrTemp = new int[10];
                    arrTemp[0]=pesoTfin+camino[temp[0]][0];
                    arrTemp[1]=temp[0];
                    if(!findInVector(temp,tfin))
                        temp.push_back(tfin);
                    camino[tfin]=arrTemp;
                }
            }
        }
        //printVectorArray(camino);
        temp.erase(temp.begin());
        //printVector(temp);
    }
    printCamino(camino,fin);
}

void scan() {
    int nv, ne, u, v, w;
    cin >> nv >> ne;
    Graph G(nv);
    for(int a=0;a<ne;a++){
        cin >> u >> v >> w;
        G.insert(Edge(u, v, w));
    }
    int busquedas;
    cin>>busquedas;
    for(int a=0;a<busquedas;a++) {
        int ini,fin;
        cin>>ini>>fin;
        dijkstra(G,ini,fin);
    }

}


void generarAristas(int numVertices,int numAristas){
    ofstream myfile;
    myfile.open ("puntos.txt");
    myfile <<numVertices<<" "<<numAristas<<endl;
    for(int a=0;a<numAristas;a++){
        int x=rand()%numVertices;
        int y=rand()%numVertices;
        int peso=rand()%7;
        myfile << x<<" "<<y<<" "<<peso;
        myfile<<endl;
    }
    myfile.close();
}


int main() {
    scan();
    //generarAristas(10000,100000);
    return 0;
}