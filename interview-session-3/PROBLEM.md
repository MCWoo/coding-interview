# Path Exists in Graph

You're given an undirected graph with `n` nodes, labeled `0` to `n - 1`, and
a list of `edges` where each `edges[i] = [a, b]` indicates an undirected
edge between node `a` and node `b`. Given two nodes `source` and
`destination`, return `true` if there is a path between them, `false`
otherwise.

**Signature:** `bool solution(int n, vector<vector<int>>& edges, int source, int destination)`

**Constraints:**
- `1 <= n <= 2 * 10^5`
- `0 <= edges.length <= min(2 * 10^5, n * (n - 1) / 2)`
- `edges[i].length == 2`
- `0 <= edges[i][0], edges[i][1] < n`
- No self-loops (`edges[i][0] != edges[i][1]`) and no repeated edges
- `0 <= source, destination < n`

**Examples:**
- `n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2` → `true`
- `n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5` → `false` (two disconnected components: `{0,1,2}` and `{3,4,5}`)
- `n = 1, edges = [], source = 0, destination = 0` → `true` (a node trivially has a path to itself)
