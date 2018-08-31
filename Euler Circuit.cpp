/*
res will contain the traversing order of node in Euler Circuit
Need to reverse the res vector
"I am not sure about the virtual edge between the start and end node
if the graph has Euler path"
Runtime is O(E)
Condition for directed graph :
    Euler Circuit :
        1.All node's in-degree & out-degree will be same
    Euler Path:
        1.All node's in-degree & out-degree will be same
        except the start & end node.
        2.For start node out-degree - in-degree = 1
        3.For end node in-degree - out-degree = 1
*/
void EulerTour(int u){
    while(!adj[u].empty()){
        int v = adj[u].back(); adj[u].pop_back();
        EulerTour(v);
    }
    res.pb(u);
}
