#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>

#define PR_INITIAL_VALUE 0.0f
#define PR_DAMPING_FACTOR 0.85f
#define PR_TOLERANCE 0.005f

int main(int argc, char **argv){
  FILE * input_file, *cusha_file;
  for (int i = 1; i < argc; i++){
    if(!strcmp(argv[i], "--in")){
      i++;
      input_file = fopen(argv[i], "r");
    }else if(!strcmp(argv[i], "--cusha")){
      i++;
      cusha_file = fopen(argv[i], "r");
    }
  }

  // fscanf(input_file, "%s\n", buf);
  // printf("%s\n", buf);
  // printf("awdawdwadawwad\n");


  unsigned vertex_count, edges_count;
  fscanf(input_file, "%u %u\n", &vertex_count, &edges_count);
  float *rank = (float*)calloc(vertex_count, sizeof(float));
  float *old_rank = (float*)calloc(vertex_count, sizeof(float));
  unsigned *edges = (unsigned*)calloc(3*edges_count, sizeof(unsigned));
  // unsigned *neigbors = (unsigned*)calloc(vertex_count, sizeof(unsigned));

  char cont = 1;

  for(unsigned i = 0; i < vertex_count; i++){
      rank[i] = PR_INITIAL_VALUE;
      // old_rank[i] = 0.0;
      // neigbors[i] = 0;
  }

  for(unsigned i = 0; i < edges_count; i++){
    // printf("%u\n",i);
    fscanf(input_file, "%u %u %u\n", &edges[3*i], &edges[3*i+1], &edges[3*i+2]);
    // printf("%i %i %i\n", edges[3*i], edges[3*i + 1], edges[3*i + 2]);
    // neigbors[edges[2*i]] =  1;
  }

  // for(unsigned i = 0; i < vertex_count; i++){
  //     rank[i] = PR_INITIAL_VALUE;
  // }
  unsigned iter = 0;

  while(cont){
    cont = 0;
    for(unsigned i = 0; i < vertex_count; i++){
        old_rank[i] = rank[i];
        rank[i] = 0.0;
    }

    for(unsigned i = 0; i < edges_count; i++){
      unsigned from = edges[3*i];
      unsigned to = edges[3*i + 1];
      unsigned neigbors = edges[3*i + 2];
      if(neigbors)
        rank[to] += old_rank[from] / neigbors;
        // rank[to] += rank[from] / neigbors;

    }

    for(unsigned i = 0; i < vertex_count; i++){
      rank[i] = (1-PR_DAMPING_FACTOR) + rank[i]*PR_DAMPING_FACTOR;

      if(!cont && fabs(rank[i]- old_rank[i]) > PR_TOLERANCE ){
        cont = 1;
      }
    }
    iter++;

  }
  printf("FINISHED in %u iterations\n", iter);
  unsigned _cur_vertex = 0;
  float value = 0, max = 0;

  for(unsigned i = 0; i < vertex_count; i++){
      fscanf(cusha_file, "%u: %f\n", &_cur_vertex, &value);
      if(fabs(rank[i] - value) > max){
        max = fabs(rank[i] - value);
      }
      // printf("%u: %f\n", i, rank[i]);
  }
  printf("max = %f \n", max);



  fclose(input_file);
  fclose(cusha_file);

}
