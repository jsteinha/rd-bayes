#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "infer.h"

int main(int argc, char** argv){
    setTask("link");
    loadNet();
    loadAllTargets();

    Infer* infer = new InferNaieve();
    // only interested in posterior marginal for a single node
    

    loadAllCases();
    for(int t=0;t<20;t++){
    tic();
    printf("Compiling...\n");
    infer->compile(getNet(), getTargets()[t]);
    printf("Calling inference algorithm...\n");
    printf("probability for node %d: %.3f\n", t, getProbability(infer->infer(getCases()[16]), 0));
    toc(1);
    }

    return 0;    
}
