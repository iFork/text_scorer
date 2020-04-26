EXE:=main
S:=$(wildcard src/*.cpp)
H:=$(patsubst src/%.hpp,inc/%.hpp,$(wildcard src/*.hpp))
O:=$(patsubst src/%.cpp,obj/%.o,$(S))
D:=$(patsubst src/%.cpp,obj/%.dep,$(S))

INC := -Iinc -I ../../inc \
	-I$(HOME)/boost_1_72_0 
LIBS := -l dictionary -L ../../lib \
	-lm 
LD_PATH := ../../lib

all: $(EXE) $(H) 


$(EXE): $(O)
	gcc $^ -lstdc++ $(LIBS) -o $@ 

obj/%.o: src/%.cpp
	gcc -xc++ -c $< -o $@ $(INC)

obj/%.dep: src/%.cpp
	@mkdir -p obj
	gcc -xc++ -MM $< -MT "$@ $(patsubst obj/%.dep,obj/%.o,$@)" -o $@ $(INC)

inc/%.hpp: src/%.hpp
	@mkdir -p inc
	ln $< inc 

-include $(D)

.PHONY: clean
clean: 
	rm -r obj $(EXE) output.txt inc 

.PHONY: doxyclean
doxyclean: 
	rm -r doxygen/html doxygen/latex 

.PHONY: test 
test: $(EXE)
	$(MAKE)
	export LD_LIBRARY_PATH=$(LD_PATH) ; ./main 
	@if cmp -s output/output.txt golden/golden.txt ; \
	       	then echo test succesfully passed! ; \
	       	else echo test faild ; fi


