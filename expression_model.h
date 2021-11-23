#include <vector>
using std::vector;

namespace expression_model_01 {
  
  class expr_outer;
  class expr_inner;

  typedef double value_t;
  typedef value_t(*op2_t)(value_t, value_t);
  typedef std::vector<expr_outer*> arg_list_t ;

  class expr_outer {
      friend class expr_inner;

      expr_outer *parent;
      expr_inner *inside;
      value_t value;    
    public:
      void calculate();
      expr_outer();
      ~expr_outer();
  };

  class expr_inner {
      expr_outer *owner;
      op2_t fn2;
      arg_list_t arg;
    public:
      void add_child(expr_outer *_child);
      void cacluate();
      expr_inner(expr_outer *_owner, op2_t _fn2);
      ~expr_inner();
  };
}