# Makefile for a.out, a.out-test, a.out-cov
# usage: make [FLAGS=<flags>]
# make test: runs unit tests as well as compares expected to actual output
# make cov:  rebuilds project, runs tests, and checks line coverage

FLAGS           ?= -g

BIN             = bin/
SOURCES         = $(shell find src/ -type f -name "*.cpp" | grep -v "main.cpp")
HEADERS         = $(shell find src/ -type f -name "*.hpp") \
                 $(shell find src/ -type f -name "*.tpp")
TARGET          = libpvn.so

TEST_MAIN       = test/main.cpp
TEST_SOURCES    = $(shell find test/ -type f -name "*.cpp" | grep -v "main.cpp")
TEST_HEADERS    = $(shell find test/ -type f -name "*.hpp")
TARGET_TEST     = a.out-test

GXXOPTS         = -Wall -Wextra -pedantic -std=c++11 -I src/
LDLIBS          =
CXXOPTS         = $(GXXOPTS) $(CXXFLAGS) $(FLAGS)
MKDIR           = mkdir -p

OBJ             = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(SOURCES)))

TEST_MAIN_OBJ   = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(TEST_MAIN)))
TEST_OBJ        = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(TEST_SOURCES)))

TARGET_COV      = a.out-cov
COVOPTS         = -fprofile-arcs -ftest-coverage --coverage -fno-inline \
                  -O0 -fno-inline-small-functions -fno-default-inline
GCOV            = gcov -rpbj

COV_GCDA        = $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(SOURCES))) \
                $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(TEST_MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(TEST_SOURCES)))

COV_GCNO        = $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(SOURCES))) \
                $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(TEST_MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(TEST_SOURCES)))

.PHONY: all test cov covr vars

all: $(TARGET)

# compile .cpp source files to objects (.o)
$(BIN)%.o: %.cpp $(HEADERS) $(TEST_HEADERS)
	@$(MKDIR) $(@D)
	$(CXX) -fPIC -shared $(CXXOPTS) -o $@ -c $<

# link executable
$(TARGET): $(OBJ)
	$(CXX) -fPIC -shared $(CXXOPTS) -o $@ $^ $(LDLIBS)
	@echo "binary compiled: '$(TARGET)'"

# link test executable
$(TARGET_TEST): $(OBJ) $(TEST_OBJ) $(TEST_MAIN_OBJ)
	$(CXX) $(CXXOPTS) -o $@ $^ $(LDLIBS)
	@echo "binary compiled: '$(TARGET_TEST)'"

# run test executable
test: $(TARGET) $(TARGET_TEST)
	@echo "unit testing:"
	./$(TARGET_TEST)

# compile .cpp source files to objects (.o) with line coverage on
$(BIN)%.gcda: %.cpp
	@$(MKDIR) $(@D)
	$(CXX) -fPIC -shared $(CXXOPTS) $(COVOPTS) -o $(patsubst %.gcda,%.o,$@) -c $<

# link executable with line coverage on
$(TARGET_COV): $(COV_GCDA) $(COV_GCNO)
	$(CXX) $(CXXOPTS) $(COVOPTS) -o $@ $(OBJ) $(TEST_OBJ) $(TEST_MAIN_OBJ) $(LDLIBS)
	@echo "binary compiled: '$(TARGET_COV)'"

# run tests and view coverage
cov: $(TARGET_COV)
	@echo "testing:"
	./$(TARGET_COV)
	@echo -e "\nchecking coverage '$(TARGET_COV)':"
	@$(GCOV) -n $(COV_GCDA) | awk '/^File/ {f=0} /^File.+\.cpp|^File.+\.tpp/ \
	{f=1; t="\n"} (f==1) {if (!($$0 ~ /^No /)) {print t $$0} t="    "} '

# make coverage files for each source
covr: cov
	@$(GCOV) $(COV_GCDA) | grep -E "^Creating" | cut -d"'" -f2 \
	| awk -F"#" 'BEGIN{print "set -x"} {o="$(BIN)" $$0; gsub("#","/",o); d=o; \
	gsub($$NF,"",d); printf("mkdir -p %s; mv %s %s\n", d, $$0, o)}' | bash

# remove objects and executable
clean:
	$(RM) $(TARGET) $(OBJ)
	$(RM) $(TARGET_TEST) $(TEST_MAIN_OBJ) $(TEST_OBJ)
	$(RM) $(TARGET_COV) $(COV_GCDA) $(COV_GCNO)

# print variables
vars:
	@echo "CXX                      $(CXX)"
	@echo "CXXOPTS                  $(CXXOPTS)"
	@echo
	@echo "TARGET                   $(TARGET)"
	@echo "SOURCES                  $(SOURCES)"
	@echo "HEADERS                  $(HEADERS)"
	@echo "OBJ                      $(OBJ)"
	@echo
	@echo "TARGET_TEST              $(TARGET_TEST)"
	@echo "TEST_MAIN                $(TEST_MAIN)"
	@echo "TEST_SOURCES             $(TEST_SOURCES)"
	@echo "TEST_HEADERS             $(TEST_HEADERS)"
	@echo
	@echo "TARGET_COV               $(TARGET_COV)"
	@echo "COVOPTS                  $(COVOPTS)"
	@echo "GCOV                     $(GCOV)"
	@echo "COV_GCDA                 $(COV_GCDA)"
	@echo
