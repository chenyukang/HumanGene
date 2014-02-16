/*******************************************************************************
 *
 *      @name   : main.cc
 *
 *      @author : Yukang Chen (moorekang@gmail.com)
 *      @date   : 2012-09-09 20:59:11
 *
 *      @brief  : compute k-shortest-path for Prof YD
 *
 *******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <time.h>

#include "map.h"
#include "alg.h"

using namespace std;


Map map;
vector<int> ids;
int kth = -1;

void read_data(const char* filename) {
    string line , s;

    map.resize(MAX);
    ifstream fin(filename, ios::in);
    if(fin == 0) {
        cout<<"open file error: "<<filename<<std::endl;
        exit(1);
    }

    vector<string> res;
    size_t pos = 0, last_pos = 0, index;
    int idy, idx = 1;
    while(getline(fin, line)) {
        pos = last_pos = 0;
        idy = 1;
        while((index=line.find(',', last_pos)) != string::npos ) {
            s = line.substr(last_pos, index - last_pos);
            if(s!= "Inf"){
                map[idx].push_back(Node(idy, atoi(s.c_str())));
            }
            last_pos = index + 1;
            idy++;
        }
        if(last_pos != line.length()) {
            s = line.substr(last_pos);
            if(s != "Inf")
                map[idx].push_back(Node(idy, atoi(s.c_str())));
        }
        idx++;
        if( idx % 100 == 0){
            printf("reading: %.2f%%\n", (float)(idx*100)/((float)MAX));
        }
    }
}

void read_ids(const char* filename) {
    string line , s;

    ifstream fin(filename, ios::in);
    if(fin == 0) {
        cout<<"open file error: "<<filename<<std::endl;
        exit(1);
    }

    while(getline(fin, line)) {
        int value = atoi(line.c_str());
        if(kth == -1) {
            kth = value;
            continue;
        }else {
            ids.push_back(value);
        }
    }
}

void show_map() {
    for(int i=0; i<MAX; i++) {
        if(map[i].size() != 0) {
            for(int j=0; j<map[i].size(); j++) {
                Node& n = map[i][j];
                cout<<"(id:"<<n.id<<" dist:"<<n.dist<<") ";
            }
            cout<<std::endl;
        }
    }
}

void run_pairs(const Map& map, vector<int>& ids) {
    for(int i=0; i<ids.size() -1; i++){
        for(int j=i+1; j<ids.size(); j++) {
            printf("compute pair ... (%d %d)\n", ids[i], ids[j]);
            astar(map, ids[i], ids[j], kth);
        }
    }
}

int main(int argc, const char** argv){
    if(argc < 3){
        std::cout<<"usage: ./main arg1 arg2"<<std::endl;
        std::cout<<" arg1 is map matrix file."<<std::endl;
        std::cout<<" arg2 is pairs input file."<<std::endl;
        exit(1);
    }
    const char* data_file = argv[1];
    const char* pairs_file = argv[2];
    assert(data_file && pairs_file);
    read_data(data_file);
    verify_map(map);
    read_ids(pairs_file);
    run_pairs(map, ids);

#if 0
    time_t begin, end;
    begin = time(NULL);
    astar(map, 2722, 13964);
    end = time(NULL);
    printf("cost time: %d\n", end - begin);

    begin = time(NULL);
    astar(map, 85, 2242);
    end = time(NULL);
    printf("cost time: %d\n", end - begin);
#endif

#if 0
    begin = time(NULL);
    astar(map, 77, 3736);
    end = time(NULL);
    printf("cost time: %d\n", end - begin);
#endif

#if 0
    begin = time(NULL);
    astar(map, 77, 2716);
    end = time(NULL);
    printf("cost time: %d\n", end - begin);
#endif


#if 0
    int path[9] = {1, 46, 158, 3617, 761, 115, 148, 484, 2};

    int res = 0;
    for(int k=0; k<8; k++) {
        int id = path[k];
        int id_next = path[k+1];
        bool found = false;
        for(int i=0; i<map[id].size(); ++i) {
            if(map[id][i].id == id_next) {
                res += map[id][i].dist;
                found = true;
                break;
            }
        }
        if(!found) {
            std::cout<<"error"<<std::endl;
            break;
        }
    }
    std::cout<<"cost:"<<res<<std::endl;
#endif
#if 0
    std::cout<<"finished read map"<<std::endl;
    astar2(map, 1, 2);
    //Dijkstra(1, map);
#endif
#if 0
    Path a;
    Path b;
    a = b;
    a.show();
    b.show();
    a.add(1, 10);
    b = a;
    a.show();
    b.show();
    b.add(2, 12);
    b.show();
    a = b;
    a.show();
#endif
    return 0;
    //show_map();

}
