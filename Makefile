# Makefile for a.out, a.out-test, a.out-cov
# usage: make [FLAGS=<flags>]
# make test: runs unit tests as well as compares expected to actual output
# make cov:  rebuilds project, runs tests, and checks line coverage

FLAGS           ?= -g

BIN             = bin/
MAIN            =
SOURCES         = $(shell find src/ -type f -name "*.cpp" | grep -v "main.cpp")
HEADERS         = $(shell find src/ -type f -name "*.hpp") \
                 $(shell find src/ -type f -name "*.tpp")
TARGET          = libpvn.so

TEST_MAIN       = test/main.cpp
TEST_SOURCES    = $(shell find test/ -type f -name "*.cpp" | grep -v "main.cpp")
TEST_HEADERS    = $(shell find test/ -type f -name "*.hpp")
TARGET_TEST     = a.out-test

GCCOPTS         = -Wall -Wextra -pedantic -std=c99 -I src/
GXXOPTS         = -Wall -Wextra -pedantic -std=c++11 -I src/
LDLIBS          =
CCOPTS          = $(GCCOPTS) $(CCFLAGS) $(FLAGS)
CXXOPTS         = $(GXXOPTS) $(CXXFLAGS) $(FLAGS)
MKDIR           = mkdir -p
PYTHON          = python3

MAIN_OBJ        = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(MAIN))) \
                $(patsubst %.c,$(BIN)%.o, $(filter %.c,$(MAIN)))
OBJ             = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(SOURCES))) \
                $(patsubst %.c,$(BIN)%.o, $(filter %.c,$(SOURCES)))

TEST_MAIN_OBJ   = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(TEST_MAIN))) \
                $(patsubst %.c,$(BIN)%.o, $(filter %.c,$(TEST_MAIN)))
TEST_OBJ        = $(patsubst %.cpp,$(BIN)%.o, $(filter %.cpp,$(TEST_SOURCES))) \
                $(patsubst %.c,$(BIN)%.o, $(filter %.c,$(TEST_SOURCES)))

TARGET_COV      = a.out-cov
GCOV            = gcov
COVOPTS         = -fprofile-arcs -ftest-coverage --coverage -fno-inline -O0 -fno-inline-small-functions -fno-default-inline
GCOVOPTS        = -b -n
GCOVPRNT        = grep -EA 4 "\.c|\.cpp" | grep -v "/usr/include" \
                | sed -E '/^No.*/d' | sed -E 's/(^Lin|^Bra|^Tak|^Cal)/    \1/'

COV_GCDA        = $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(MAIN))) \
                $(patsubst %.c,$(BIN)%.gcda,$(filter %.c,$(MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(SOURCES))) \
                $(patsubst %.c,$(BIN)%.gcda,$(filter %.c,$(SOURCES))) \
                $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(TEST_MAIN))) \
                $(patsubst %.c,$(BIN)%.gcda,$(filter %.c,$(TEST_MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcda,$(filter %.cpp,$(TEST_SOURCES))) \
                $(patsubst %.c,$(BIN)%.gcda,$(filter %.c,$(TEST_SOURCES)))

COV_GCNO        = $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(MAIN))) \
                $(patsubst %.c,$(BIN)%.gcno,$(filter %.c,$(MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(SOURCES))) \
                $(patsubst %.c,$(BIN)%.gcno,$(filter %.c,$(SOURCES))) \
                $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(TEST_MAIN))) \
                $(patsubst %.c,$(BIN)%.gcno,$(filter %.c,$(TEST_MAIN))) \
                $(patsubst %.cpp,$(BIN)%.gcno,$(filter %.cpp,$(TEST_SOURCES))) \
                $(patsubst %.c,$(BIN)%.gcno,$(filter %.c,$(TEST_SOURCES)))

.PHONY: all test cov

all: $(TARGET)

# compile .c source files to objects (.o)
$(BIN)%.o: %.c $(HEADERS) $(TEST_HEADERS)
	@$(MKDIR) $(@D)
	$(CC) $(CCOPTS) -o $@ -c $<

# compile .cpp source files to objects (.o)
$(BIN)%.o: %.cpp $(HEADERS) $(TEST_HEADERS)
	@$(MKDIR) $(@D)
	$(CXX) -fPIC -shared $(CXXOPTS) -o $@ -c $<

# link executable
$(TARGET): $(OBJ) $(MAIN_OBJ)
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

# compile .c source files to objects (.o) with line coverage on
$(BIN)%.gcda: %.c
	@$(MKDIR) $(@D)
	$(CC) $(CCOPTS) $(COVOPTS) -o $(patsubst %.gcda,%.o,$@) -c $<

# compile .cpp source files to objects (.o) with line coverage on
$(BIN)%.gcda: %.cpp
	@$(MKDIR) $(@D)
	$(CXX) -fPIC -shared $(CXXOPTS) $(COVOPTS) -o $(patsubst %.gcda,%.o,$@) -c $<

# link executable with line coverage on
$(TARGET_COV): $(COV_GCDA) $(COV_GCNO)
	$(CXX) -fPIC -shared $(CXXOPTS) $(COVOPTS) -o $(TARGET) $(OBJ) $(MAIN_OBJ) $(LDLIBS)
	@echo "binary compiled: '$(TARGET)'"
	$(CXX) $(CXXOPTS) $(COVOPTS) -o $@ $(OBJ) $(TEST_OBJ) $(TEST_MAIN_OBJ) $(LDLIBS)
	@echo "binary compiled: '$(TARGET_COV)'"

# run tests and view coverage
cov: $(TARGET_COV)
	@echo "testing:"
	./$(TARGET_COV)
	@echo -e "\nchecking coverage '$(TARGET_COV)':"
	@$(GCOV) $(GCOVOPTS) $(COV_GCDA) | $(GCOVPRNT)

# remove objects and executable
clean:
	$(RM) $(TARGET) $(MAIN_OBJ) $(OBJ)
	$(RM) $(TARGET_TEST) $(TEST_MAIN_OBJ) $(TEST_OBJ)
	$(RM) $(TARGET_COV) $(COV_GCDA) $(COV_GCNO)
	$(RM) -r $(PY_CACHE)

# print variables
vars:
	@echo "TARGET                   $(TARGET)"
	@echo "MAIN                     $(MAIN)"
	@echo "SOURCES                  $(SOURCES)"
	@echo "HEADERS                  $(HEADERS)"
	@echo "MAIN_OBJ                 $(MAIN_OBJ)"
	@echo "OBJ                      $(OBJ)"
	@echo
	@echo "TARGET_TEST              $(TARGET_TEST)"
	@echo "TEST_MAIN                $(TEST_MAIN)"
	@echo "TEST_SOURCES             $(TEST_SOURCES)"
	@echo "TEST_HEADERS             $(TEST_HEADERS)"
	@echo
	@echo "TARGET_COV               $(TARGET_COV)"
	@echo