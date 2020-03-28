/*

    This is an implementation of RFM algorithm.
    The goal of this implementation is to find the best path to get from node A to node B in a graph.
    Consider that the graph used is weighted and undirected 
    The nodes' are numbered from 1 to N 
    the weight is positive and a integer that fits in an integer 

*/


#include <bits/stdc++.h>

using namespace std;

// N is the number of node and M is the number of M edges  
int N, M;

int start, finaln;

//size of the OPEN set
int s;

// we are implementing a prearity queue for OPEN set, for this we are using a heap. 
int OPEN[100];

// CLOSE is the set of the node that have been visited
int CLOSE[100];

// cost is used to know the current cost of each node.
int cost[100];

// This array helps to eliminate easy and fast from OPEN 
int positions[100];

// adyacency matrix to save the graph, we are using a matrix because is faster to delete any edge once is used. 
// We can change it this for a list instead of a matrix, but for deleting edges we will have to take more time or sort the list and do a binary search. 
// Or we might use a balance tree instead.
// For reasons of simplicity we are going to keep the matrix 
int amatrix[100][100]; 


//take an element out from open
int pop(int pos){
    int r = OPEN[pos];
    positions[OPEN[pos]] = 0;
    OPEN[pos] = OPEN[s--]; 
    positions[OPEN[pos]] = pos;
    if(r == 5){
        cout << s << endl;
    }
    if(s == 0){
        cout << "\n\n\n end \n\n\n";
        return r;
    }
    while(pos <= s){
        int a = pos * 2 <= s ? pos * 2 : N + 1;
        int b = pos * 2 + 1 <= s? pos * 2 + 1: N + 1;
        if(cost[OPEN[a]] < cost[OPEN[b]] && cost[OPEN[a]] < cost[OPEN[pos]]){
            swap(OPEN[pos], OPEN[a]);
            swap(positions[a] , positions[pos]);
            pos = a;
        }else if(cost[OPEN[b]] < cost[OPEN[a]] && cost[OPEN[b]] < cost[OPEN[pos]]){
            swap(OPEN[pos], OPEN[b]);
            swap(positions[b] , positions[pos]);
            pos = b;
        }else break;  
    }
    return r; 
}

// insert in OPEN list
void add(int node){
    //check if is in the OPEN list and remove it
    if(positions[node]){
        pop(positions[node]);
    }
    int index = ++s;
    while(cost[node] < cost[OPEN[index/2]]){
        positions[OPEN[index/2]] = index;
        OPEN[index] = OPEN[index/2];
        index /= 2;
    }
    OPEN[index] = node;
    positions[node] = index;
}
///declare the size of the elements because we are using static memory and set everything in 0, 0 means not used
void ini(){
    /*OPEN = (int*) malloc(sizeof(int) * (N + 2));
    CLOSE = (int*) malloc(sizeof(int) * (N + 2));
    positions = (int*) malloc(sizeof(int) * (N + 2));
    //amatrix = (int**) malloc(sizeof(int)* (N + 3));
    cost = (int*)malloc(sizeof(int) * (N + 2)); 
    */
    for(int i = 0; i <= N; i++)
    {
        //amatrix[i] = (int*) malloc(sizeof(int)*(N + 2));
        //memset(amatrix[i], 0, N + 2);
        cost[i] = INT_MAX;
    }
    memset(OPEN, 0, N + 2);
    memset(CLOSE, 0, N + 2);
    memset(positions, 0, N + 2);
    //memset(cost, INT_MAX, N + 2);
    
    cost[0] = INT_MIN;
    cost[N + 1] = INT_MAX;
    OPEN[N + 1] = N + 1;
}


void read(){
    cout << "insert the number of nodes and edges\n";
    cin >> N >> M;
    
    ini();
    cout << "insert the " << M << " edges, edge is read from A to B with a cost C (C has to positive)\n";
    for(int i = 1; i <= M; i++){
        int a, b, c;
        cin >> a >> b >> c; 
        amatrix[a][b] = c;
        amatrix[b][a] = c;
        
    }

    cout << "insert initial state\n";
    cin >> start; 
    cout << "inisert final state\n";
    cin >> finaln;
    cost[start] = 0;

}

vector<int> getPath(){
    cout << "todo bien aja la baraja\n";
    int actual = CLOSE[finaln];
    cout << "aca andamos \n";
    vector<int> r;
    cout << "entro";
    while(actual != start){
        r.push_back(actual);
    }
    r.push_back(actual);
    reverse(r.begin(), r.end());
    cout << "salio \n";
    return r;
}

vector<int> RFM(){
    add(start);
    while(s != 0){
       
        int actual = pop(1);
        
        if(actual == finaln){
            cout << "aqui andamos compa\n";
            break;
        }
        cout << "/n/n -------- entro : " << actual << " ------ \n\n";
        for(int i = 1; i <= N; i++){
            if(amatrix[actual][i] != 0){

                int c = amatrix[actual][i];
                //removing edge 
                amatrix[actual][i] = 0; 
                amatrix[i][actual] = 0;

                //if it improves update or add the cost in OPEN set
                cout << actual << " actual: " << cost[actual] + c << " ----" << i << " : " << cost[i] << endl;
                if(c + cost[actual] < cost[i]){
                    cout << i << endl;
                    cost[i] = c + cost[actual];
                    add(i);
                    CLOSE[i] = actual; 
                }
            }
        }
        cout << "/n/n -------- salio : " << actual << " ------ \n\n";
        
        cout << "\n" << s << " : " << OPEN[1] << "\n";
    }
    cout << "que paso aqui \n";
    return getPath();
}

void printRFM(vector<int> path){
    cout << "cost to get to B is: " << cost[finaln] << "\n";
    cout << "the path to follow is: ";
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << "\n";
    } 
    cout << "\n";
}

int main(){
    read();
    vector<int> path = RFM();
    printRFM(path);
}