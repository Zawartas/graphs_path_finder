#include<iostream>
#include <list>
#include <map>

using namespace std;

class SafeMap {
public:
    int V;
    list<int> *adj;
    SafeMap(int);
    void addSafeRoute(int, int);
    int isReachable(int, int);
};

SafeMap::SafeMap(int V)
{
    this->V = V;
    adj = new list<int> [V];
}

void SafeMap::addSafeRoute(int v, int w)
{
    adj[v].push_back(w); // Add w to v's list.
}

int SafeMap::isReachable(int s, int d)
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    bool *in_queue = new bool[V];
    for (int i = 0; i < V; i++)
        in_queue[i] = false;

    list<int> queue;

    list<int>::iterator i;

    if (s == d) return 0;

    map<int, int> path;
    int temp = s;
    do {
        if (!queue.empty()) queue.pop_front();
        visited[s] = true;
        for (i = adj[s].begin(); i != adj[s].end(); i++){
            if(visited[*i] == false && in_queue[*i] == false){
                queue.push_back(*i);
                in_queue[*i] = true;
                path[*i] = s;
            }
        }
        s = queue.front();
    }
    while (!queue.empty() && s != d);

    if (s != d) return -1;

    queue.clear();
    while (temp != d){
        queue.push_front(d);
        d = path[d];
    }

   return queue.size();
}

int main() {

  SafeMap g(7);
  g.addSafeRoute(0, 2);
  g.addSafeRoute(6, 3);
  g.addSafeRoute(2, 3);
  g.addSafeRoute(4, 7);
  g.addSafeRoute(5, 2);
  g.addSafeRoute(2, 4);

  cout << g.isReachable(2, 7);

return 0;
}
