#include <iostream>
#include <stack>
#define INF 10000000 // 무한의 값을 나타내기 위한 수.

using namespace std;

class Graph
{
private:
    int** length; // 이차원 배열
    int* dist;    // 일차원 배열
    int* path;     // 최단 경로를 위한 일차원 배열.
    bool* s;      // 일차원 배열. 방문 여부 판단.
    int n;        // 정점의 수
public:
    Graph(const int vertices = 0) : n(vertices)
    {
        dist = new int[n];
        s = new bool[n];
        length = new int* [n]; // 이차원 배열의 동적생성
        path = new int[n];    // 일차원 배열 생성.
        for (int i = 0; i < n; i++) // 방향 그래프 초기화.
        {
            length[i] = new int[n];
            for (int j = 0; j < n; j++) {
                if (i == j) length[i][j] = 0; // 자기 자신으로의 경로는 0
                else length[i][j] = INF; // 나머지는 일단 INF로 초기화.(입력되지 않으면 INF값을 가져야 하니까.)
            }
        }
    }
    inline void Insert(const int, const int, const int); // 간선과 가중치 입력.
    void ShortestPath(const int); // 시작정점에서 각 정점까지의 갈수있는 경우중 가중치의 최소값.
    int choose(const int); // dist에 저장된 값중 방문안한 곳중에 최소값 선정. 
    void Print_dist(); // 최소비용 출력
    void Print_graph(); // 방향 그래프 출력
    void Print_path(); // 최소비용 경로 출력.
};

inline void Graph::Insert(const int a, const int b, const int w) // inline을 사용해서 간단한 경로의 입력을 구현.
{
    length[a][b] = w;
}

void Graph::ShortestPath(const int v) // 시작 정점으로부터 다른 정점들 까지의 최소비용구하기(dist배열)
{
    for (int i = 0; i < n; i++) // 초기화 부분.
    {
        s[i] = false;  // 초기 방문은 거짓으로.
        dist[i] = length[v][i]; // dist 초기화.
        path[i] = v; // path도 처음에는 시작 정점 번호로 전부 초기화.
    }
    
    s[v] = true; // 시작정점 방문처리.(dist 초기화때 이미 시작정점으로부터 다른 정점들 까지의 거리가 입력되어 있음.)
    dist[v] = 0; // 
    for (int i = 0; i < n - 2; i++) // 정점 v로부터 n-1개 경로를 결정.
    {
        int u = choose(n); // choose로 부터  dist[u] = minimum dist[w]인 u를 반환.
        s[u] = true; // 선택 후 방문처리.
        
        for (int w = 0; w < n; w++)
        {
            if (!s[w]) { // 방문처리 되지 않은 경우.
                if (dist[u] + length[u][w] < dist[w]) // 만약 갱신되어 마땅하다면 갱신.
                {
                    dist[w] = dist[u] + length[u][w]; // dist 갱신하고
                    path[w] = u; // path도 갱신.
                }
            }
        }
    }
}

int Graph::choose(const int a)
{
    int min = INF; // INF로 초기화
    int u = 0; // 초기값은 0으로 합니다.
    for (int i = 0; i < n; i++)
    {
        if (dist[i] < min && !s[i]) // 방문처리 되지 않은 노드중 dist값이 최소인 노드 선택합시다.
        {
            u = i;
            min = dist[i];
        }
    }
    return u; // 선택된 노드 반환.
}

void Graph::Print_dist() // dist 출력
{
    cout << "dist : ";
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << "\n\n";
}
void Graph::Print_graph() // 방향그래프 출력
{
    cout << "Graph는 아래와 같습니다.\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (length[i][j] == INF) cout << "INF ";
            else cout << length[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
void Graph::Print_path() // stack을 이용해 최소비용경로를 구합니다.
{
    stack<int > my_stack;
    cout << "각 정점까지의 최소비용경로는 다음과 같습니다.\n";
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INF) cout << i << "번 정점 : 경로 없음\n";
        else if (i == path[i]) cout << i << "번 정점 : 자기 자신으로의 경로 없음..\n";
        else
        {
            int j = i;
            while (j != path[j])
            {
                my_stack.push(j);
                j = path[j];
            }
            my_stack.push(j);
            cout << i << "번 정점 : ";
            while (!my_stack.empty())
            {
                cout << my_stack.top() << " ";
                my_stack.pop();
            }
            cout << "\n";
        }
    }
}

int main()
{
    int n, m; // n : 정점의 수, m : 간선의 수

    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;// a는 출발간선, b는 도착간선, c는 a->b 가중치.
        cin >> a >> b >> c;
        g.Insert(a, b, c); // 입력.
    }
    int start_point; // 시작 정점
    cin >> start_point;

    g.ShortestPath(start_point);
    g.Print_dist();
    g.Print_graph();
    g.Print_path();

    return 0;
}
