CXX=g++
DEPS=AVL.h WordFreq.h
OBJ=AVL.o WordFreq.o nokia_code_whiz.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $<

NokiaCodeWhiz: $(OBJ)
	$(CXX) $^ -o $@

clean:
	rm *.o 
	rm NokiaCodeWhiz