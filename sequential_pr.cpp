
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PR_INITIAL_VALUE 0.0f
#define PR_DAMPING_FACTOR 0.85f
#define PR_TOLERANCE 0.005f

using namespace std;

int main(int argc, char **argv){
  fstream input_file, cusha_file;
  // FILE * input_file, *cusha_file;
  for (int i = 1; i < argc; i++){
    if(!strcmp(argv[i], "--input")){
      i++;
      input_file.open(argv[i], ios::in | ios::binary);
      // input_file = fopen(argv[i], "r");
    }else if(!strcmp(argv[i], "--cusha")){
      i++;
      cusha_file.open(argv[i], ios::in | ios::binary);
    }
  }

  // fscanf(input_file, "%s\n", buf);
  // printf("%s\n", buf);
  // printf("awdawdwadawwad\n");


  int vertices_count = 0;
  long long edges_count = 0;

  input_file.read((char*)(&vertices_count), sizeof(int));
  input_file.read((char*)(&edges_count), sizeof(long long));
  cout << "Graph has " << vertices_count << " vertices" << endl;
  cout << "Graph has " << edges_count << " edges" << endl;


  float *rank =  new float[vertices_count];
  float *old_rank = new float[vertices_count];
  int *edges = new int[3*edges_count];
  // unsigned *neigbors = (unsigned*)calloc(vertex_count, sizeof(unsigned));

  char cont = 1;

  for(unsigned i = 0; i < vertices_count; i++){
      rank[i] = PR_INITIAL_VALUE;
      // old_rank[i] = 0.0;
      // neigbors[i] = 0;
  }

  for(long long i = 0; i < edges_count; i++){
    // printf("%u\n",i);

     input_file.read((char*)(&edges[3*i]), sizeof(int));
     input_file.read((char*)(&edges[3*i + 1]), sizeof(int));
     input_file.read((char*)(&edges[3*i + 2]), sizeof(int));

    // fscanf(input_file, "%u %u %u\n", &edges[3*i], &edges[3*i+1], &edges[3*i+2]);
    // printf("%i %i %i\n", edges[3*i], edges[3*i + 1], edges[3*i + 2]);
    // neigbors[edges[2*i]] =  1;
  }

  // for(unsigned i = 0; i < vertex_count; i++){
  //     rank[i] = PR_INITIAL_VALUE;
  // }
  unsigned iter = 0;

  while(cont){
    cont = 0;
    for(unsigned i = 0; i < vertices_count; i++){
        old_rank[i] = rank[i];
        rank[i] = 0.0;
    }

    for(long long  i = 0; i < edges_count; i++){
      unsigned from = edges[3*i];
      unsigned to = edges[3*i + 1];
      unsigned neigbors = edges[3*i + 2];
      if(neigbors)
        rank[to] += old_rank[from] / neigbors;
        // rank[to] += rank[from] / neigbors;

    }

    for(int i = 0; i < vertices_count; i++){
      rank[i] = (1-PR_DAMPING_FACTOR) + rank[i]*PR_DAMPING_FACTOR;

      if(!cont && fabs(rank[i]- old_rank[i]) > PR_TOLERANCE ){
        cont = 1;
      }
    }
    iter++;

  }
  printf("FINISHED in %u iterations\n", iter);
  unsigned _cur_vertex = 0;
  float value = 0, max = 0, max_value = 0;

  for(int i = 0; i < vertices_count; i++){
      // fscanf(cusha_file, "%u: %f\n", &_cur_vertex, &value);
      cusha_file.read((char*)(&value), sizeof(float));
      if(fabs(rank[i] - value) > max){
        max = fabs(rank[i] - value);
      }
      if(rank[i] > max_value){
        max_value = rank[i];
      }
      // printf("%u: seq=%f cusha= %f\n", i, rank[i], value);
  }
  printf("max = %f, max_value = %f  \n", max, max_value);


}
