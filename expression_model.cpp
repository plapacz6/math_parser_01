#include "expression_model.h"
using namespace  expression_model_01;

void expr_outer::calculate(){
  inside->cacluate();
}
expr_outer::expr_outer(){
  inside = NULL;  
}
expr_outer::~expr_outer(){

}

void expr_inner::add_child(expr_outer *_child){
  _child->parent = owner;
  arg.push_back(_child);
}
void expr_inner::cacluate(){
  owner->value = fn2(arg[0]->value, arg[1]->value);
}
expr_inner::expr_inner(expr_outer *_owner, op2_t _fn2){
  owner = _owner;
  fn2 = _fn2;
}
expr_inner::~expr_inner(){

}