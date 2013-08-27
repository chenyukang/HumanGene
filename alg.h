
/*******************************************************************************
 *
 *      @name   : ALG_H
 *
 *      @author : Yukang Chen (moorekang@gmail.com)
 *      @date   : 2012-09-11 20:24:46
 *
 *      @brief  :
 *
 *******************************************************************************/

#if !defined(ALG_H)
#define ALG_H

#include "map.h"

void Dijkstra(const Map& map, int id, int* dist);
int astar(const Map& map, int S, int T, int K);
int astar2(const Map& map, int S, int T);
int algro(const Map& map, int S, int T, int K);
bool verify_map(const Map& map);
void init_table(const Map& map);

#endif

