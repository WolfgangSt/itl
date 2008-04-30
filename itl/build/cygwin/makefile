#------------------------------------------------------------------------------
# makefile for the inteval template library
#------------------------------------------------------------------------------

#--- Platformdependent variables ----------------------------------------------
#--- cygwin
EXE_TAG = .exe
#--- unix
#EXE_TAG = 


#------------------------------------------------------------------------------
# Locations
#------------------------------------------------------------------------------

#--- location of this makefile ------------------------------------------------
MAKE_PATH = .
#--- location of the interval template library rootpath -----------------------
ITL_ROOT_PATH = ../..
#--- root directory of the interval template library --------------------------
ITL_SRC_PATH  = $(ITL_ROOT_PATH)/src


#--- location of the compiler -------------------------------------------------
CMP_PATH = /opt/conceptgcc-boostcon
#CMP_PATH = /opt/conceptgcc-4.1.1-alpha-5

#--- binaries -----------------------------------------------------------------
BIN_PATH    = $(ITL_ROOT_PATH)/bin
OBJ_PATH    = $(BIN_PATH)/obj

#--- include pathes -----------------------------------------------------------
ITL_INCL = $(addprefix -I,$(ITL_SRC_PATH))
STD_INCL = -I/usr/include
#GCC_INCL = $(addprefix -I,$(CMP_PATH))/include
GCC_INCL = -I/opt/conceptgcc-boostcon/include

INCLUDE  = $(GCC_INCL) $(ITL_INCL) 
#INCLUDE  = $(STD_INCL) $(ITL_INCL)

#SOURCES = ./test/itvset_shell/itvset_shell.cpp 
#SOURCES = itl_test.cpp 
#SOURCES = ./src/validate/gentor/gentorprofile.cpp

#--- libraries ----------------------------------------------------------------
#LOAD_LIBS  = -L$(CMP_PATH)/lib
LOAD_LIBS  = -L/usr/lib 

#--- loadflags ----------------------------------------------------------------
LOAD_FLAGS = $(LOAD_LIBS) -lstdc++

#--- compileflags ---------------------------------------------------
# COMPILE_FLAGS = -o2 -DUSE_CONCEPTS
COMPILE_FLAGS = -o2

#--- compiler -----------------------------------------------------------------
#COMPILE = $(CMP_PATH)/bin/gcc
#COMPILE = /opt/conceptgcc-boostcon/bin/gcc
COMPILE = gcc


all:
	make examples
	make tests
	make devels

# The concept_gcc compiles does not yet digest my loki::typelist based tuple type
# tag 'all_concept' covers the parts that can be compiled
all_concept:
	make examples
	make tests
	
examples:
	make party
	make interval
	make interval_container
	make overlap_counter
	make history
	make amount_cube

tests:
	make itvset_shell
	make splititvmap_shell
	make auto_itv_test
	make labatea
	
devels:
	make validate

#--- projects -----------------------------------------------------------------
#--- group examples -----------------------------------------------------------

#--- project party ---------------------------------------------------------
EXAMPLE_DIR = example
party_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/party
party_MAIN = $(party_PATH)/party.cpp
party_SOURCES = $(party_MAIN)
party_TARGET  = $(BIN_PATH)/party$(EXE_TAG)

party:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(party_SOURCES) $(LOAD_FLAGS) -o $(party_TARGET)

#--- project interval ---------------------------------------------------------
interval_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/interval
interval_MAIN = $(interval_PATH)/interval.cpp
interval_SOURCES = $(interval_MAIN)
interval_TARGET  = $(BIN_PATH)/interval$(EXE_TAG)

interval:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(interval_SOURCES) $(LOAD_FLAGS) -o $(interval_TARGET)

#--- project interval_container --------------------------------------------------
interval_container_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/interval_container
interval_container_MAIN = $(interval_container_PATH)/interval_container.cpp
interval_container_SOURCES = $(interval_container_MAIN)
interval_container_TARGET  = $(BIN_PATH)/interval_container$(EXE_TAG)

interval_container:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(interval_container_SOURCES) $(LOAD_FLAGS) -o $(interval_container_TARGET)

#--- project overlap_counter --------------------------------------------------
overlap_counter_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/overlap_counter
overlap_counter_MAIN = $(overlap_counter_PATH)/overlap_counter.cpp
overlap_counter_SOURCES = $(overlap_counter_MAIN)
overlap_counter_TARGET  = $(BIN_PATH)/overlap_counter$(EXE_TAG)

overlap_counter:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(overlap_counter_SOURCES) $(LOAD_FLAGS) -o $(overlap_counter_TARGET)

#--- project history --------------------------------------------------
history_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/history
history_MAIN = $(history_PATH)/history.cpp
history_SOURCES = $(history_MAIN)
history_TARGET  = $(BIN_PATH)/history$(EXE_TAG)

history:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(history_SOURCES) $(LOAD_FLAGS) -o $(history_TARGET)

#--- project amount_cube --------------------------------------------------
amount_cube_PATH = $(ITL_ROOT_PATH)/$(EXAMPLE_DIR)/amount_cube
amount_cube_MAIN = $(amount_cube_PATH)/amount_cube.cpp
amount_cube_SOURCES = $(amount_cube_MAIN)
amount_cube_TARGET  = $(BIN_PATH)/amount_cube$(EXE_TAG)

amount_cube:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(amount_cube_SOURCES) $(LOAD_FLAGS) -o $(amount_cube_TARGET)

#--- group tests --------------------------------------------------------------
#--- project itvset_shell -----------------------------------------------------
TEST_DIR = test
itvset_shell_PATH = $(ITL_ROOT_PATH)/$(TEST_DIR)/itvset_shell
itvset_shell_MAIN = $(itvset_shell_PATH)/itvset_shell.cpp
itvset_shell_SOURCES = $(itvset_shell_MAIN)
itvset_shell_TARGET  = $(BIN_PATH)/itvset_shell$(EXE_TAG)

itvset_shell:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(itvset_shell_SOURCES) $(LOAD_FLAGS) -o $(itvset_shell_TARGET)

#--- project splititvmap_shell ------------------------------------------------
splititvmap_shell_PATH = $(ITL_ROOT_PATH)/$(TEST_DIR)/splititvmap_shell
splititvmap_shell_MAIN = $(splititvmap_shell_PATH)/splititvmap_shell.cpp
splititvmap_shell_SOURCES = $(splititvmap_shell_MAIN)
splititvmap_shell_TARGET  = $(BIN_PATH)/splititvmap_shell$(EXE_TAG)

splititvmap_shell:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(splititvmap_shell_SOURCES) $(LOAD_FLAGS) -o $(splititvmap_shell_TARGET)

#--- project auto_itv_test -----------------------------------------------------
auto_itv_test_PATH = $(ITL_ROOT_PATH)/$(TEST_DIR)/auto_itv_test
auto_itv_test_MAIN = $(auto_itv_test_PATH)/auto_itv_test.cpp
auto_itv_test_SOURCES = $(auto_itv_test_MAIN)
auto_itv_test_TARGET  = $(BIN_PATH)/auto_itv_test$(EXE_TAG)

auto_itv_test:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(auto_itv_test_SOURCES) $(LOAD_FLAGS) -o $(auto_itv_test_TARGET)

#--- project labatea -----------------------------------------------------
labatea_PATH = $(ITL_ROOT_PATH)/$(TEST_DIR)/labatea
labatea_MAIN = $(labatea_PATH)/labatea.cpp
labatea_SOURCES = $(ITL_SRC_PATH)/validate/gentor/gentorprofile.cpp $(labatea_MAIN)
labatea_TARGET  = $(BIN_PATH)/labatea$(EXE_TAG)

labatea:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(labatea_SOURCES) $(LOAD_FLAGS) -o $(labatea_TARGET)


	
#--- group devels --------------------------------------------------------------
#--- project itvset_shell -----------------------------------------------------
DEVEL_DIR = devel
validate_PATH = $(ITL_ROOT_PATH)/$(DEVEL_DIR)/validate
validate_MAIN = $(validate_PATH)/validate.cpp
validate_SOURCES = $(ITL_SRC_PATH)/validate/gentor/gentorprofile.cpp $(validate_MAIN)
validate_TARGET  = $(BIN_PATH)/validate$(EXE_TAG)

validate:
	$(COMPILE) $(COMPILE_FLAGS)  $(INCLUDE) $(validate_SOURCES) $(LOAD_FLAGS) -o $(validate_TARGET)


show_temps:
	find $(ITL_ROOT_PATH) -name \*.pdb; \
	find $(ITL_ROOT_PATH) -name \*.exe; \
	find $(ITL_ROOT_PATH) -name \*.obj; \
	find $(ITL_ROOT_PATH) -name \*.pdb; \
	find $(ITL_ROOT_PATH) -name \*.idb; \
	find $(ITL_ROOT_PATH) -name \*.ilk; \
	find $(ITL_ROOT_PATH) -name \*.dep; \
	find $(ITL_ROOT_PATH) -name \*.manifest*; \
	find $(ITL_ROOT_PATH) -name BuildLog.htm; \
	find $(ITL_ROOT_PATH) -name BuildLog.htm; \
	find $(ITL_ROOT_PATH)/doc/html -name *; \
	find $(ITL_ROOT_PATH) -name \*.ncb; \
	find $(ITL_ROOT_PATH) -name \*.suo; \
	find $(ITL_ROOT_PATH) -name \*.user; \
	
win_clean:
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.exe; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.obj; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.pdb; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.idb; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.ilk; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.dep; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.manifest; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin \*.manifest.*; \
	../script/rm_temps $(ITL_ROOT_PATH)/bin BuildLog.htm; \
	../script/rm_temps $(ITL_ROOT_PATH) \*.ncb; \
	../script/rm_temps $(ITL_ROOT_PATH) \*.suo; \
	../script/rm_temps $(ITL_ROOT_PATH) \*.user;
	
bin_clean:
	rm -rf $(ITL_ROOT_PATH)/bin/* ;

dox_clean:
	../script/rm_temps $(ITL_ROOT_PATH)/doc/html \*.html; \
	../script/rm_temps $(ITL_ROOT_PATH)/doc/html \*.png; \
	../script/rm_temps $(ITL_ROOT_PATH)/doc/html \*.css; \
	../script/rm_temps $(ITL_ROOT_PATH)/doc/html \*.gif; \

clean:
	make win_clean 
	make dox_clean
	
#	echo `find $(ITL_ROOT_PATH)/doc/html -name \*.png`  
	
	