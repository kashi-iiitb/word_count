CXX=g++
IDIR=../include
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS=AVL.h WordFreq.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
#DEPS=$(patsubst pattern,replacement,text)

_OBJ=AVL.o WordFreq.o nokia_code_whiz.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

NokiaCodeWhiz: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o 
	rm NokiaCodeWhiz