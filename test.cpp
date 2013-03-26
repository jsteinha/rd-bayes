#include <stdio.h>
#include "smile/smile.h"
#include "util.h"
#include "task.h"
#include "infer.h"

int main(int argc, char** argv){

  Task linkTask = Task("link");
  linkTask.loadNet();
  linkTask.loadAllTargets();

  Infer* infer = new InferNaive();

  // only interested in posterior marginal for a single node
  infer->compile(linkTask.getNet(), linkTask.getTargets()[0]);

  linkTask.loadAllCases();

  printf("Calling inference algorithm...\n");
  
  linkTask.tic();
  infer->infer(linkTask.getCases()[26]);
  linkTask.toc(1);

  return 0;    
}
