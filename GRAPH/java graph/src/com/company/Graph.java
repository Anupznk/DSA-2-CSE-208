package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Graph {

    public static void dfs(ArrayList<List<Integer>> adj, ArrayList<Boolean> vis, int vertex) {
        if (!vis.get(vertex)) {
            vis.set(vertex, true);
            System.out.print(vertex + " ");
        }

        for (int i = 0; i < adj.get(vertex).size(); i++) {
            if (!vis.get(adj.get(vertex).get(i))) {
                dfs(adj, vis, adj.get(vertex).get(i));
            }
        }
    }

    public static void bfs(ArrayList<List<Integer>> adj, ArrayList<Boolean> vis, int vertex) {
        Queue<Integer> q = new LinkedList<>();
        if (!vis.get(vertex)) {
            vis.set(vertex, true);
            q.add(vertex);
            System.out.print(vertex + " ");
        }

        while (!q.isEmpty()) {
            int adjVertex = q.peek();
            q.remove();
            for (int i = 0; i < adj.get(adjVertex).size(); i++) {
                int currVertex = adj.get(adjVertex).get(i);
                if (!vis.get(currVertex)) {
                    vis.set(currVertex, true);
                    q.add(currVertex);
                    System.out.print(currVertex + " ");
                }
            }
        }
    }

    public static void main(String[] args) {

        int v, e;
        Scanner input = null;
        File f = new File("graph.txt");
        try {
            input = new Scanner(f);
        } catch (FileNotFoundException ex) {
            System.out.println("File not found");
            ex.printStackTrace();
        }

        String line = input.nextLine();
        String[] words = line.split(" ");
        v = Integer.parseInt(words[0]);
        e = Integer.parseInt(words[1]);

        ArrayList<List<Integer>> adj = new ArrayList<List<Integer>>(v);
        for (int i = 0; i < v; i++) {
            adj.add(new ArrayList<>()); // initializing the nested ArrayLists
        }

        while (input.hasNextLine()) {
            line = input.nextLine();
            words = line.split(" ");
            int v1 = Integer.parseInt(words[0]);
            int v2 = Integer.parseInt(words[1]);
            adj.get(v1).add(v2);
            adj.get(v2).add(v1);
        }

        ArrayList<Boolean> vis = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            vis.add(false);
        }

        bfs(adj, vis, 0);


    }
}
