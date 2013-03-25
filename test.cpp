#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "infer.h"

int main(int argc, char** argv){
    setTask("link");
    loadNet();
    loadAllTargets();

    Infer* infer = new InferNaive();
    // only interested in posterior marginal for a single node
    infer->compile(getNet(), getTargets()[0]);
    

    loadAllCases();
    printf("Calling inference algorithm...\n");
    tic();
    infer->infer(getCases()[26]);
    toc(1);

    return 0;    
}
