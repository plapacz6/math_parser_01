cc=g++
flags=-Wall -g
tests = expression_model_tests 
executable = 

# test list
testy: $(tests)

expression_model_tests: expression_model.cpp expression_model.h
	$(cc) $(flags) expression_model.cpp -o expression_model_tests


.PHONY: clean
clean:
	-rm $(tests)
	-rm *.o
	-rm $(executable)