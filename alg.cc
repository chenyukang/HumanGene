
/*******************************************************************************
 *
 *      @name   : alg.cc
 *
 *      @author : Yukang Chen (moorekang@gmail.com)
 *      @date   : 2012-09-11 20:33:39
 *
 *      @brief  :
 *
 *******************************************************************************/


#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "alg.h"
using namespace std;


bool mark[MAX];
int  dist[MAX];
int  s_dist[MAX];
int  d_dist[MAX];

bool operator < (const State& a,const State& b) {
    return a.estimate > b.estimate;
}

bool operator < (const Path& a,const Path& b) {
    return a.estimate > b.estimate;
}

//Dijkstra 算法 找出各个点到T的最短距离
void Dijkstra(const Map& map, int id, int* dist) {
    memset(mark, false, sizeof(mark));
    for(int i=0; i<MAX; i++) {
        dist[i] = INF;
    }
    
    dist[id] = 0;
    int u, v, min;
    while(1) {
        u = -1, min = INF;
        for(int i=1;i<MAX; i++) {
            if(!mark[i] && dist[i]<min) {
                min = dist[i];
                u = i;
            }
        }
        if(u == -1) break;
        mark[u] = true;
        for(int k=0; k<map[u].size(); ++k) {
            v = map[u][k].id;
            if(!mark[v] && dist[v]>dist[u]+map[u][k].dist)
                dist[v] = dist[u]+map[u][k].dist;
        }
    }

    int num = 0;
    for(int k=0; k<MAX; k++){
        if(dist[k] != INF){
            num++;
        }
    }
    //std::cout<<"num:"<<num<<std::endl;
}


Map table;

void init_table(const Map& map) {
    int dist[MAX];
    table.resize(MAX);
    for(int i=1; i<MAX; i++){
        Dijkstra(map, i, &dist[0]);
        std::cout<<"now :"<<i<<std::endl;
        for(int j=1;j <MAX; j++){
            if(dist[j] != INF) {
                table[j].push_back(Node(i, dist[j]));
            }
        }
    }
}


int algro(const Map& map, int S, int T, int K) {
    int cnt[MAX];
    Dijkstra(map, S, &s_dist[0]);
    Dijkstra(map, T, &d_dist[0]);
    for(int i=0; i<MAX; i++) {
        if(s_dist[i] != INF &&
           d_dist[i] != INF) {
            dist[i] = s_dist[i] + d_dist[i];
        } else {
            dist[i] = INF;
        }
    }

    int res[K+1];
    int idx = 1;
    for(int i=0; i<K+1; i++) {
        res[i] = INF;
    }
    sort(dist, dist+MAX);
    for(int i=0; i<MAX; i++) {
        if(dist[i] != res[idx-1]) {
            //std::cout<<i<<" -> distance:"<<dist[i]<<std::endl;
            res[idx] = dist[i];
            if(idx == K) break;
            idx++;
        }
    }
    for(int i=K; i>=1; i--) {
        if(res[i] != INF) {
            return res[i];
        }
    }
}


int astar2(const Map& map, int S, int T) {
    int cnt[MAX];
    Dijkstra(map, T, &dist[0]);
    if(dist[S] == INF) return -1;
    memset(cnt, 0, sizeof(cnt));
    priority_queue<State> Q;
    Q.push(State(S, 0, dist[S]));
    while(!Q.empty()) {
        State now = Q.top();
        int  id = now.id;
        Q.pop();
        cnt[id]++;
        //std::cout<<id<< " "<< Q.size()<<std::endl;
        if(id == T) {
            std::cout<<"cnt:"<<cnt[T]<< " ";
            now.show();
        }
        for(int i=0; i<map[id].size(); i++) {
            int v = map[id][i].id;
            if(cnt[v] >=1 )
                continue;
            State next = now;
            next.id = v;
            next.dist = next.dist + map[id][i].dist;
            next.estimate = next.dist + dist[v];
            Q.push(next);
        }
    }
    return 0 ;
}

int astar(const Map& map, int S, int T, int K) {
    int cnt[MAX];
    int prev = INF;
    int* dist = &d_dist[0];
    int max_dist = algro(map, S, T, K);
    int res_count = 0;
    
    if(dist[S] == INF) return -1;
    memset(cnt, 0, sizeof(cnt));
    priority_queue<Path> Q;
    Q.push(Path(S));
    while(!Q.empty()) {
        Path now = Q.top();
        int  id = now.last_id();
        Q.pop();
        cnt[id]++;
        if(id == T && now.dist != prev) {
            //std::cout<<"cnt:"<<cnt[T]<< " ";
            now.show();
            prev = now.dist;
            res_count++;
            if(res_count >= K) {
                break;
            }
            continue;
        }
        for(int i=0; i<map[id].size(); i++) {
            int v = map[id][i].id;
            if(dist[v] > max_dist)
                continue;
            if(now.contains(v)) 
                continue;
            if(now.trace.size() > 20)
                continue;
            Path p = now;
            p.add(v, map[id][i].dist);
            p.estimate = p.dist + dist[v];
            if(p.dist > max_dist ||
               p.estimate > max_dist) { // a strong limit
                continue;
            }
            Q.push(p);
        }
    }
    printf("========================================\n");
    return 0 ;
}


bool verify_map(const Map& map) {
    for(int i=1; i<map.size(); i++) {
        bool found = false;
        for(int j=0; j<map[i].size(); j++) {
            int id = map[i][j].id;
            for(int k=0; k<map[id].size(); k++){
                if(map[id][k].id== i){
                    found = true;
                    break;
                }
            }
            if(!found) {
                printf("error: %d %d\n", i, id);
            }
        }
    }
    std::cout<<"finished verify map"<<std::endl;
}
