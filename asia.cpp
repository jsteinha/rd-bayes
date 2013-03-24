#include <stdio.h>
#include "smile/smile.h"

const char* int2str(int status){
    return status ? "no" : "yes"; // oddly, 0 means yes
}

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

int main(){
    DSL_network net;
    net.ReadFile("asia.net", DSL_HUGIN_FORMAT);
    net.SetDefaultBNAlgorithm(DSL_ALG_BN_LAURITZEN);

    int asia = net.FindNode("asia");
    int tub = net.FindNode("tub");
    int lung = net.FindNode("lung");
    int xray = net.FindNode("xray");
    //printf("asia id: %d\n", asia);
    //printf("tub id: %d\n", tub);
    //printf("lung id: %d\n", lung);
    //printf("xray id: %d\n", xray);
    //printf("\n");

    printf("Computing initial beliefs...\n");
    net.UpdateBeliefs();
    printf("P(lung = yes) = %f\n", getProbability(net.GetNode(lung), "yes"));
    printf("P(tub = yes) = %f\n", getProbability(net.GetNode(tub), "yes"));
    printf("P(asia = yes) = %f\n", getProbability(net.GetNode(asia), "yes"));
    printf("\n");

    printf("Adding and computing probability of evidence (xray = yes)...\n");
    int yes = 0, no = 1;
    net.GetNode(xray)->Value()->SetEvidence(yes);
    double p_evidence;
    net.CalcProbEvidence(p_evidence);
    printf("P(xray = yes) = %f\n", p_evidence);
    printf("\n");

    printf("Updating beliefs given xray = yes...\n");
    net.UpdateBeliefs();
    printf("P(lung = yes | xray = yes) = %f\n", getProbability(net.GetNode(lung), "yes"));
    printf("P(tub = yes | xray = yes) = %f\n", getProbability(net.GetNode(tub), "yes"));
    printf("P(asia = yes | xray = yes) = %f\n", getProbability(net.GetNode(asia), "yes"));

    return 0;    
}
