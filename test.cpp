#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "task.h"
#include "infer.h"

int main(int argc, char** argv){

<<<<<<< HEAD
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
=======
  Task linkTask = Task("link");
  linkTask.loadNet();
  linkTask.loadAllTargets();

  Infer* infer = new InferNaive();
>>>>>>> 1f85fb22640434b6ec221aaf878bba87d86e5da1

  // only interested in posterior marginal for a single node
  infer->compile(linkTask.getNet(), linkTask.getTargets()[0]);

  linkTask.loadAllCases();

  printf("Calling inference algorithm...\n");
  
  linkTask.tic();
  infer->infer(linkTask.getCases()[26]);
  linkTask.toc(1);

  return 0;    
}
