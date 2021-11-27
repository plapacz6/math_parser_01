#include <vector>
#include <cstdlib>
using namespace std;

class expr_inside;
class expr_outside;

typedef double value_t;
typedef value_t (operator2_t)(value_t, value_t);
typedef vector<expr_outside*> arg_list_t;

class expr_outside {
  friend class expr_inside;
  expr_inside *inside;
  value_t value;
  expr_outside *parent;
  public:
    void calculate();
};
class expr_inside {
  //friend class expr_outside;
  expr_outside *owner;
  operator2_t *fn2;
  arg_list_t arg;
  public:
    expr_inside(expr_outside *_owner, operator2_t *_fn2);
    ~expr_inside();
    void add_child(expr_outside *child);
    value_t calculate();
};
void expr_inside::add_child(expr_outside *child){
  child->parent = this->owner;
  arg.push_back(child);
}
value_t expr_inside::calculate(){
  return fn2(arg[0]->value, arg[1]->value);
}
void expr_outside::calculate(){
  value = inside->calculate();
}
expr_inside::expr_inside(expr_outside *_owner, operator2_t *_fn2){
  owner = _owner;
  owner->inside = this;
  fn2 = _fn2;
}
expr_inside::~expr_inside(){

}
