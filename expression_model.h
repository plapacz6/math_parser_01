/* author: plapacz6@gmail.com date: 2021-11-23 */
#include <vector>
using std::vector;

namespace expression_model_01 {
  
  class expr_outer;
  class expr_inner;

  typedef double value_t;
  typedef value_t(*op2_t)(value_t, value_t);
  typedef std::vector<expr_outer*> arg_list_t ;
  ///Klasa reprezentujaca wyrażenie widziane jako jedna wartość
  class expr_outer {
      friend class expr_inner;
      friend void flip_parent_1child(expr_outer *parent, expr_outer *child1);

      expr_outer *parent;
      expr_inner *inside;
      value_t value;    
    public:
      expr_outer();
      ~expr_outer();

      void add_child(expr_outer *_child);

      ///Oblicza wartość wyrażenia
      void calculate();
      
  };
  ///Klasa reprezentujaca jeden pozmiom wewnętrznej budowy wyrażenia złożonego
  ///Pokazuje od czego i jak zależy wartotość całego wyrażenia.
  class expr_inner {
      expr_outer *owner;
      op2_t fn2; ///<- Funkcja obliczajaca wartosć wyrażenia na podstawie posiadanych argumentów.
      arg_list_t arg;
    public:
      expr_inner(expr_outer *_owner, op2_t _fn2);
      ~expr_inner();

      ///Dodaje wyrażenie kolejnego poziomu jako argument dla wyrażenia bierzącego poziomu.
      ///@ _child - Wskaznik do wyrażenia dodawanego jako argument.
      ///Ponieważ arg_list jest zaimplementowane jako vector, ilosć argumentów można uzyskać metodą size().
      void add_child(expr_outer *_child);
      
      //operator wyzszego rzedu
      ///po napotkaniu operatora wyzszego rzedu
      ///zwraca aktualny drugi argument a na jego miejsce wstawia _newOperatorHigherPriorytet
      ///i jako 1 arg _newCurrent wstawia ten zwracany
      ///zapisuje bierzacy current na stosie
      ///ustaiwa _newOperatorHigherPriorytet jako current      
      expr_outer flip_with2arg(expr_outer *_newOperatorHigherPriorytet);  //overMakeNewOperator

      //operator tego samego rzedu
      ///wstawia aktualny operator jako 1 arg nowo utworzonego
      ///i ustawia nowo utwozony jako current
      ///zwraca ten nowo utworzony
      ///nie zapisuje bierzacego current na sosie, bo to ten sam poziom priorytetow
      expr_outer underMakeNewOperator(expr_outer *_newOperatorTheSamePrioritet);

      ///operator nizszego rzedu
      
      /*
      if current != first        
        umieszcza bierzacy operator jako 1 argument _newLowerOperator
        stos -> current
      else  //stos jest pusty
        umieszcza bierzacy operator jako 1 argument _newLowerOperator
        current = _newLoweOperator
         first = current           
         //stos pozostaje pusty do czasu napostania wyzszego priorytetu
      */
      expr_outer underMakeLowerNewOperator(expr_outer *_newLowerOperator);
      

      ///Oblicza wartosć całęgo wyrażenia i zapisuje ją do cześci 'outer'
      void cacluate();

      
  };

  ///Zamienia miejscami wyrażenie poziomu poprzedniego z pierszym jego dzieckiem.
  ///@ _parent - Wskaznik do wyrażenia rodzica.
  ///@ _child - Wskaznik do wyrażenia pierwszego dziecka.
  ///result  Rezultatem jest efekt uboczny \
              będący zamianą tych dwóch wyrażeń miejscami w modelu struktury wyrażenia złożonego.
  void flip_parent_1child(expr_outer *parent, expr_outer *child1);
}