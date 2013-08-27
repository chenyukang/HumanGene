
/*******************************************************************************
 *
 *      @name   : MAP_H
 *
 *      @author : Yukang Chen (moorekang@gmail.com)
 *      @date   : 2012-09-11 20:25:26
 *
 *      @brief  :
 *
 *******************************************************************************/

#if !defined(MAP_H)
#define MAP_H

#include <vector>
#include <assert.h>
using namespace std;

#define MAX 18605
#define INF 0x7fffffff

class Node{
public:
Node(int id, int dist): id(id), dist(dist)
    { }
Node() : id(0), dist(0)
    { }
    int id;
    int dist;
};

typedef vector<Node> Node_vector;
typedef vector<Node_vector> Map;


class State{
public:
    State():dist(0)
        { };

    State(int id):id(id)
        {
            dist = estimate = 0;
        }

    State(int id, int dist, int estimate):
        id(id), dist(dist), estimate(estimate)
        {
        }

    bool operator < (const State& s) {
        return estimate < s.estimate;
    }

    void show() {
        std::cout<<"now_id:"<<id<<" -> dist:"<<dist<<std::endl;
    }


public:
    int id;
    int dist;
    int estimate;
};

class Path{
public:
    Path():dist(0)
    { };

    Path(int id)
        {
            trace.push_back(id);
            dist = estimate = 0;
        }
    
    void add(int id, int len) {
        assert(id > 0 && len > 0);
        trace.push_back(id);
        dist += len;
    }

    void show() {
        std::cout<<"distance:"<<dist;
        std::cout<<" (";
        for(int i=0; i<trace.size(); i++) {
            std::cout<<" "<< trace[i] << " ";
        }
        std::cout<<")"<<std::endl;
    }

    int last_id() {
        int len = trace.size();
        return trace[len-1];
    }
    
    bool contains(int id) {
        for(int k=0; k<trace.size(); k++) {
            if( trace[k] == id )
                return true;
        }
        return false;
    }

    bool operator < (const Path& s) {
        return estimate < s.estimate;
    }


public:
    vector<int> trace;
    int dist;
    int estimate;
};


#if 0
class State{
public:
    State() { }
    State(Path p, int estimate):
        path(p), estimate(estimate)
        {
            assert(estimate >= p.dist);
        }
    State(int id, int estimate):
        path(id), estimate(estimate)
        {
        }
    
    int last_id() {
        int len = path.trace.size();
        return path.trace[len-1];
    }

    bool operator < (const State& s) {
        return estimate < s.estimate;
    }
    
public:
    
    Path path;
    int  estimate;
};
#endif

    
    
#endif

