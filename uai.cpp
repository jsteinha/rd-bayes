#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "infer.h"

int main(int argc, char** argv){
    setTask("bn2o/bn2o-30-15-150-2b");
    loadNetUAI();
    DSL_network net = getNet();
    int numNodes = net.GetNumberOfNodes();
    printf("Number of nodes in network: %d\n", numNodes);
    int numTargets = 10;
    loadRandomTargets(numTargets);

    Infer* infer = new InferNaieve();
    // only interested in posterior marginal for a single node
    

    loadAllCasesUAI();
    for(int t=0;t<numTargets;t++){
    tic();
    printf("Compiling...\n");
    int target = getTargets()[t];
    infer->compile(getNet(), target);
    printf("Calling inference algorithm...\n");
    printf("probability for node %d: %.3f\n", target, getProbability(infer->infer(getCases()[0]), 0));
    toc(1);
    }

    return 0;    
}
