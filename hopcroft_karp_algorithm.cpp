#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class BipartiteGraph{
public:
    int numNodesA, numNodesB;
    vector<vector<int>> adj; // Adjacency list
    vector<int> pairU, pairV, dist; // Matching pairs and distance array

    BipartiteGraph( int numNodesA, int numNodesB ){
        this->numNodesA = numNodesA;
        this->numNodesB = numNodesB;
        adj.resize( numNodesA + 1 );
        pairU.assign( numNodesA + 1, 0 );
        pairV.assign( numNodesB + 1, 0 );
        dist.resize( numNodesA + 1 );
    }

    void addEdge( int u, int v ){
        adj[u].push_back(v);
    }

    bool bfs(){
        queue<int> q;
        for( int u = 1 ; u <= numNodesA ; u++ ){
            if( pairU[u] == 0 ){ // Unmatched node
                dist[u] = 0;
                q.push( u );
            }else{
                dist[u] = numeric_limits<int>::max();
            }
        }
        dist[0] = numeric_limits<int>::max();

        while( !q.empty() ){
            int u = q.front();
            q.pop();
            if( dist[u] < dist[0] ){
                for( int v : adj[u] ){
                    if( dist[pairV[v]] == numeric_limits<int>::max() ){
                        dist[pairV[v]] = dist[u] + 1;
                        q.push( pairV[v] );
                    }
                }
            }
        }
        return( dist[0] != numeric_limits<int>::max() );
    }

    bool dfs( int u ){
        if( u != 0 ){
            for( int v : adj[u] ){
                if( dist[pairV[v]] == dist[u] + 1 && dfs( pairV[v] ) ){
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            dist[u] = numeric_limits<int>::max();
            return false;
        }
        return true;
    }

    int hopcroftKarp(){
        int matching = 0;
        while( bfs() ){
            for( int u = 1 ; u <= numNodesA ; u++ ){
                if( pairU[u] == 0 && dfs( u ) ){
                    matching++;
                }
            }
        }
        return matching;
    }
};

int main(){
    int numNodesA = 4, numNodesB = 4;
    BipartiteGraph graph( numNodesA, numNodesB );

    // Example edges (1-based indexing)
    graph.addEdge( 1, 1 );
    graph.addEdge( 1, 3 );
    graph.addEdge( 2, 2 );
    graph.addEdge( 2, 3 );
    graph.addEdge( 3, 1 );
    graph.addEdge( 3, 2 );
    graph.addEdge( 3, 4 );
    graph.addEdge( 4, 3 );
    graph.addEdge( 4, 4 );

    int maxMatching = graph.hopcroftKarp();
    cout << "Maximum Bipartite Matching: " << maxMatching << endl;

    return 0;
}
