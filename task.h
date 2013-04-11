#include "smile/smile.h"
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int verbose = 1;


class Task {

 private:

  long long int start;
  long long int end;
  char taskname[1000];
  char filename[1000];
  DSL_network myNet;
  vector<map<int,int> > myCases;
  vector<int> myTargets;

 public:

  Task (const char* tn){
    sprintf(taskname, "%s", tn);
    if (verbose>0){
      printf("Task set to \"%s\"\n", taskname);
    }
  }

  void tic(){
    start = clock();
  }

  void toc(int loud){
    end = clock();
    if(loud || verbose>0){
      printf("%.2f ms elapsed.\n", (end-start)*1000.0/CLOCKS_PER_SEC);
    }
  }

  void toc(){
    toc(0);
  }

  void loadNet(){
    sprintf(filename, "data/%s.net", taskname);
    if (verbose){
      printf("Reading network from %s...\n", filename);
    }
    myNet.ReadFile(filename, DSL_HUGIN_FORMAT);
  }

  DSL_network getNet(){
    return myNet;
  }

  void loadAllCases(){
    myCases.clear();
    sprintf(filename, "data/%s.cases", taskname);
    if (verbose){
      printf("Reading cases from %s...\n", filename);
    }
    FILE *fin = fopen(filename, "r");
    int numCases;
    for (numCases=0; !feof(fin); numCases++){
      map<int,int> curCase;
      int N;
      if (fscanf(fin,"%d", &N) == EOF){
        break; // then we are at the end of the file
      }
      for (int n = 0; n < N; n++){
        int nodeID, outcomeID;
        fscanf(fin, "%d%d", &nodeID, &outcomeID);
        /*if(verbose){
          printf("case: %d, node: %d, outcome: %d\n", numCases, nodeID, outcomeID);
          }*/
        assert(curCase.count(nodeID)==0);
        curCase[nodeID] = outcomeID;
      }
      myCases.push_back(curCase);
    }
    if (verbose){
      printf("%d cases read.\n", numCases);
    }
    fclose(fin);
  }

  int numCases(){
    return myCases.size();
  }
  
  vector<map<int,int> > getCases(){
    return myCases;
  }

  void loadAllTargets(){
    myTargets.clear();
    sprintf(filename, "data/%s.targets", taskname);
    if (verbose){
      printf("Reading targets from %s...\n", filename);
    }
    FILE *fin = fopen(filename, "r");
    while (!feof(fin)){
      int targetID;
      if (fscanf(fin, "%d", &targetID) == EOF){
        break; // then we are at the end of the file
      }
      myTargets.push_back(targetID);
    }
    fclose(fin);
  }
  int numTargets(){
    return myTargets.size();
  }
  vector<int> getTargets(){
    return myTargets;
  }

};