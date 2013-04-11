#include <stdio.h>
#include "smile/smile.h"

double getProbability(DSL_nodeValue* value, int stateIndex){
    DSL_sysCoordinates coord(*value);
    coord[0] = stateIndex;
    coord.GoToCurrentPosition();
    return coord.UncheckedValue();
}

double getProbability(DSL_node* node, const char* stateName){
    DSL_nodeValue* value = node->Value();
    int stateIndex = node->Definition()->GetOutcomesNames()->FindPosition(stateName);
    return getProbability(value, stateIndex);
}

int verbose;
long long int start, end;
void tic(){
    start = clock();
}
void toc(int loud){
    end = clock();
    if(loud || verbose) printf("%.2f ms elapsed.\n", (end-start)*1000.0/CLOCKS_PER_SEC);
}

int main(int argc, char** argv){
    assert(argc>=3);
    int seed; sscanf(argv[1], "%d", &seed); srand(seed);
    char filename[1000];
    sprintf(filename,"data/%s.net", argv[2]);
    if(argc>=4) sscanf(argv[3],"%d", &verbose); else verbose = 1;
    int numEvidence; if(argc>=5) sscanf(argv[4],"%d", &numEvidence); else numEvidence = 1;
    DSL_network net;
    if(verbose) { printf("Reading from %s... ", filename); fflush(stdout); }
    tic(); net.ReadFile(filename, DSL_HUGIN_FORMAT); toc(0);
    int networkSize = net.GetNumberOfNodes();
    if(verbose) printf("Network has %d nodes total.\n", networkSize);

    net.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);

    /*printf("Computing initial beliefs... "); fflush(stdout);
    tic(); net.UpdateBeliefs(); toc();*/

    //printf("numEvidence = %d\n", numEvidence);
    sprintf(filename, "run-%s-%d.log", argv[2], seed);
    FILE *fout = fopen(filename, "w");
    fprintf(fout, "numEvidence: %d\n", numEvidence);
    for(int i = 0; i < numEvidence; i++){
        int nodeIndex = rand()%networkSize;
        DSL_node* node = net.GetNode(nodeIndex);
        int numOutcomes = node->Definition()->GetNumberOfOutcomes();
        int outcome = rand()%numOutcomes;
        fprintf(fout,"%d: %d\n", nodeIndex, outcome);
        if(verbose) { printf("Setting evidence of node %d to outcome %d... ", nodeIndex, outcome); fflush(stdout); }
        //tic(); 
        node->Value()->SetEvidence(outcome); //toc(0);
    }
    if(verbose) printf("\n");
    printf("Updating beliefs... "); fflush(stdout);
    tic(); net.UpdateBeliefs(); toc(1);
    fprintf(fout, "timeElapsed: %lld\n", ((end-start)*1000)/CLOCKS_PER_SEC);

    return 0;    
}
