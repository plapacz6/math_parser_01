/* author: plapacz6@gmail.com date: 2021-11-23 */
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

void flip_parent_1child(expr_outer *parent, expr_outer *child1){

}


#define TEST_2
#define TEST_1

#ifdef TEST_2
#include <iostream>

int main(){
  std::cout << "testy poziom 2" << std::endl;
  expr_outer *peo1 = new expr_outer();
  expr_outer eo2;
  expr_outer *peo2 = &eo2;
  expr_outer* tpo[10];
  for(int i = 0; i < 10; i++){
    tpo[i] = new expr_outer();
  }

  //2 + (3 * 4) + 5
  //2 + 3 * 4 + 5
  expr_outer *first;
  expr_outer *current;
  expr_outer *dwa = new expr_outer();
  first = dwa;
  current = dwa;
  expr_outer *plus = new expr_outer();
  first = plus;
  current = plus;
  current->add_child(dwa);
  expr_outer *trzy = new expr_outer();
  current->add_child(trzy);
  expr_outer *razy = new expr_outer();
  //razy > plus
  plus->flip(trzy, razy);
  current = razy;
  current->add_child(trzy);
  expr_outer *cztery = new expr_outer();
  razy->add_child(cztery);
  expr_outer *plus2 = new expr_outer();
  plus2->add_child(plus);
  first = plus2;
  current = plus2;
  expr_outer *piec = new expr_outer();
  current->add_child(piec);

  //sum(sum(2, mul(3,4)),5)

  peo1->add_child(peo2);

  for(int i = 0; i < 10; i++){
    delete tpo[i];
  }
  delete peo1;
  return 0;
}
#ifdef TEST_1

#endif //TEST_1
#endif //TEST_2
