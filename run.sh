
#*******************************************************************************/
# 
#       RUN_SH
# 
#       @brief
# 
#       @author   Yukang Chen  @date  2012-09-11 20:26:02
# 
#       COPYRIGHT (C) 2012, ALL RIGHTS RESERVED.
# 
# ******************************************************************************/

#!/bin/sh
g++ -c main.cc -O3 -o main.o
g++ -c alg.cc -O3 -o alg.o
g++ alg.o main.o -O3 -o main
#./main;
