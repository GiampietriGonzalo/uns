import java.util.*;

public class Result {

    static int result = 0;

    public static void main(String[] args) {
        ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
        boolean[] nodeHasCat;
        int nodesCount;
        int consecutiveNodesWithCatsAllowed;
        Scanner inputScanner = new Scanner(System.in);
        

        // read n and m
        nodesCount = inputScanner.nextInt();
        consecutiveNodesWithCatsAllowed = inputScanner.nextInt();

        // nodeHasCat array initialization
        nodeHasCat = new boolean[nodesCount + 1];
        int i = 1;
        while (i <= nodesCount) {
            nodeHasCat[i] = inputScanner.nextInt() == 1;
            i++;
        }

        // tree initialization
        i = 0;
        while (i < nodesCount + 1) {
            graph.add(new ArrayList<>());
            i++;
        }

        // tree building
        i = 0;
        while (i < nodesCount - 1) {
            int n1 = inputScanner.nextInt();
            int n2 = inputScanner.nextInt();
            graph.get(n1).add(n2);
            graph.get(n2).add(n1);
            i++;
        }
        inputScanner.close();

        dfs(graph, consecutiveNodesWithCatsAllowed, nodeHasCat);
        System.out.println(result);
    }

    private static void dfs(ArrayList<ArrayList<Integer>> graph,int consecutiveNodesWithCatsAllowed, boolean[] nodeHasCat) {
        //System.out.println("DFS");
        Stack<Integer> stack = new Stack<>();
        boolean[] visited = new boolean[graph.size()];
        int consecutiveCatsCount = 0;

        for (int i=1; i<graph.size(); i++) {
            visited[i] = false; // 0 means not visited yet
        }

        int root = 1;
        if (nodeHasCat[root]) {
            consecutiveCatsCount++;
        }

        if (consecutiveCatsCount > consecutiveNodesWithCatsAllowed) {
            result = 0;
            return;
        }

        visited[root] = true; //
        stack.push(root);
        visitDFS(graph, stack, visited, nodeHasCat, consecutiveNodesWithCatsAllowed, consecutiveCatsCount);
    }

    private static void visitDFS(ArrayList<ArrayList<Integer>> graph, Stack<Integer> stack, boolean[] visisted, boolean[] nodeHasCat, int consecutiveNodesWithCatsAllowed, int consecutiveCatsCount) {

        while(!stack.empty()) {
            Integer node = stack.peek();

            if (nodeHasCat[node]) {
                consecutiveCatsCount++;
            } else {
                consecutiveCatsCount = 0;
            }


            if (isLeaf(graph, node, visisted)) { //is a leaf

                //System.out.println("nodo: " + node + " es una hoja");
                //System.out.println("consecutiveCatsCount: " + consecutiveCatsCount);
                //System.out.println("consecutiveNodesWithCatsAllowed: " + consecutiveNodesWithCatsAllowed);
                if (consecutiveCatsCount <= consecutiveNodesWithCatsAllowed) {
                    result++;
                }

                visisted[node] = true;
                stack.pop();
            } else { //is not a leaf
                ArrayList<Integer> adyascents = graph.get(node);
                int nextNeighbor = -1;

                for (int i= 0; i < adyascents.size(); i++) {
                    int neighbor = adyascents.get(i);
                    if (!visisted[neighbor]) {
                        nextNeighbor = neighbor;
                    }
                }

                if (nextNeighbor != - 1) {
                    stack.push(nextNeighbor);
                } else {
                    visisted[node] = true;
                    stack.pop();
                }
            }
        }
    }

    static boolean isLeaf(ArrayList<ArrayList<Integer>> graph, int node, boolean[] visisted) {
        boolean isLeaf = true;
        ArrayList<Integer> adyascents = graph.get(node);
        int i = 0;
        while (isLeaf && i < adyascents.size()) {
            int neighbor = adyascents.get(i);
            if (!visisted[neighbor]) {
                isLeaf = false;
            }

            i++;
        }

        return isLeaf;
    }
}