#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void dfs(int v, int par, vector<vector<int>>& adj, vector<int>& dist)
{
    // iterate over all links of node 'v'
    for (int i : adj[v]) {
        // if 'i' is not the parent of 'v'
        if (i != par) {
            // store the distance from root to 'i'
            dist[i] = dist[v] + 1;
 
            // recurse for the child 'i'
            dfs(i, v, adj, dist);
        }
    }
}

int solution(vector<int> &A, vector<int> &B) {
    int N = (int)A.size() + 1;

    // store the adjacency list of the tree
    vector<vector<int>> adj(N);

    for (int i = 0; i < N-1; i++) {
        // add the link in the adjacency list
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    // stores the distance from root to 'i'
    vector<int> dist(N);

    // dfs with '0' as the root of the tree
    dfs(0, -1, adj, dist);

    // store the size of sets 'L' and 'R'
    int L = 0, R = 0;

    // iterate over all the nodes of the tree
    for (int i = 0; i < N; i++) {
        // if 'i' is at an even distance
        if ((dist[i] & 0x1) == 0) {
            // increment the size of set 'L'
            L++;
        } else {
            // increment the size of set 'R'
            R++;
        }
    }

    return L * R;
}

typedef struct _MyMap {
    vector<int> A;
    vector<int> B;
    int output;
} MyMap;

const string ANSI_RESET = "\u001B[0m";
const string ANSI_RED = "\u001B[31m";
const string ANSI_GREEN = "\u001B[32m";

int main(void) {
    vector<MyMap> tests = {
        {{0,3,4,2,6,3}, {3,1,3,3,3,5}, 6},
        {{0,4,2,2,4}, {1,3,1,3,5}, 9},
        {{0,4,4,2,7,6,3}, {3,5,1,3,4,3,4}, 16},
    };

    const string passed = ANSI_GREEN+"PASSED"+ANSI_RESET;
    const string failed = ANSI_RED+"FAILED"+ANSI_RESET;

    int R = 0;
    for (auto in : tests) {
        R = solution(in.A, in.B);
        cout << "Solution for: " << in.A[0] << "\t is: " << R << ". Test: " << ((R == in.output) ? passed : failed) << endl;
    }

    return 0;
}
