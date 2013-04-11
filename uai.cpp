#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "task.h"
#include "infer.h"

int main(int argc, char** argv){
    Task bn20 = Task("bn2o/bn2o-30-15-150-2b", Task::UAI);
    bn20.loadNet();
    int numTargets = 10;
    bn20.loadRandomTargets(numTargets);

    Infer* infer = new InferNaive();

    bn20.loadAllCases();
    for(int t=0;t<numTargets;t++){
        bn20.tic();
        printf("Compiling...\n");
        int target = bn20.getTargets()[t];
        infer->compile(bn20.getNet(), target);
        printf("Calling inference algorithm...\n");
        printf("probability for node %d: %.3f\n", target,
            getProbability(infer->infer(bn20.getCases()[0]), 0));
        bn20.toc(1);
    }

    return 0;    
}
