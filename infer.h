#include "smile/smile.h"
#include <map>
using namespace std;

class Infer {
    public:
        virtual void compile(DSL_network net, int targetID) = 0;
        virtual DSL_nodeValue* infer(map<int,int> evidence) = 0;
};

class InferNaive : public Infer {
    private:
        DSL_network myNet;
        int myTargetID;
    public:
        void compile(DSL_network net, int targetID){
            myNet = net;
            myTargetID = targetID;
            myNet.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);
            if(verbose){
                printf("Setting node %d to be target node...\n", targetID);
            }
            myNet.SetTarget(myTargetID);
        }
        DSL_nodeValue* infer(map<int,int> evidence){
            myNet.ClearAllEvidence();
            for(map<int,int>::iterator it = evidence.begin(); it != evidence.end(); ++it){
                //printf("Setting evidence[%d] = %d\n", it->first, it->second);
                myNet.GetNode(it->first)->Value()->SetEvidence(it->second);
            }
            if(verbose){
                printf("Recomputing beliefs...\n");
            }
            myNet.UpdateBeliefs();
            return myNet.GetNode(myTargetID)->Value();
        }
};
