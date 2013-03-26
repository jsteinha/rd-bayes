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
