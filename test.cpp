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

int verbose = 1;
long long int start, end;
void tic(){
    start = clock();
}
void toc(int loud){
    end = clock();
    if(loud || verbose) printf("%.2f ms elapsed.\n", (end-start)*1000.0/CLOCKS_PER_SEC);
}
void toc(){toc(0);}

int main(){
    const char* dataset = "link";
    char filename[1000];
    sprintf(filename,"data/%s.net", dataset);
    DSL_network net;
    printf("Reading from %s... ", filename); fflush(stdout);
    tic(); net.ReadFile(filename, DSL_HUGIN_FORMAT); toc(0);
    int networkSize = net.GetNumberOfNodes();
    printf("Network has %d nodes total.\n", networkSize);

    net.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);

    printf("Computing initial beliefs... "); fflush(stdout);
    tic(); net.UpdateBeliefs(); toc(0);

    sprintf(filename, "data/%s.cases", dataset);
    printf("Opening %s...\n", filename);
    FILE *fin = fopen(filename, "r");
    
    for(int caseNum = 1; !feof(fin); caseNum++){
        net.ClearAllEvidence();
        printf("Reading test case number %d\n", caseNum);
        int N; fscanf(fin, "%d", &N);
        printf("Conditioning on %d nodes\n", N);
        for(int n = 0; n < N; n++){
            int nodeID, outcomeID;
            fscanf(fin, "%d%d", &nodeID, &outcomeID);
            net.GetNode(nodeID)->Value()->SetEvidence(outcomeID);
        }
        printf("Recomputing beliefs... "); fflush(stdout);
        tic(); net.UpdateBeliefs(); toc();
    }

    fclose(fin);

    return 0;    
}
