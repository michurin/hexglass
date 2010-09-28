B = build
S = ../src/logic
O = $(B)/logic.o \
    $(B)/figure.o \
    $(B)/abstract_place.o \
    $(B)/lplace.o \
    $(B)/pplace.o \
    $(B)/figure_iter.o \
    $(B)/figure_trans.o \
    $(B)/figures_bank.o

logic: $(O)
	c++ -o $@ $(O)
$(B)/logic.o:          logic.cpp
	c++ -c -I $(S) -o $@ $<
$(B)/figure.o:         $(S)/figure.cpp
	c++ -c -o $@ $<
$(B)/abstract_place.o: $(S)/abstract_place.cpp
	c++ -c -o $@ $<
$(B)/lplace.o:         $(S)/lplace.cpp
	c++ -c -o $@ $<
$(B)/pplace.o:         $(S)/pplace.cpp
	c++ -c -o $@ $<
$(B)/figure_iter.o:    $(S)/figure_iter.cpp
	c++ -c -o $@ $<
$(B)/figure_trans.o:   $(S)/figure_trans.cpp
	c++ -c -o $@ $<
$(B)/figures_bank.o:   $(S)/figures_bank.cpp
	c++ -c -o $@ $<
