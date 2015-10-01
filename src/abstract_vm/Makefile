################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS				:= main.cpp Operand.cpp Stack.cpp Instruction.cpp \
						error.cpp parse.cpp VM.cpp

PATH_OBJ			:= obj
PATH_OBJT			:= objt
PATH_SRC			:= src
PATH_INC			:= inc
PATH_TEST			:= test

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.cpp, $(PATH_OBJ)/%.o, $(SRCS))
OBJECTS_TEST		:= $(patsubst %.cpp, $(PATH_OBJT)/%, $(SRCS_TEST))

TEST_CMD			:= $(patsubst %.cpp, $(PATH_OBJT)/%;, $(SRCS_TEST))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

# export DIR_TYPE	:= ../libtype

# LIB_TYPE			:= -L$(DIR_TYPE) -ltype

# export DIR_LIB 		:= $(DIR_TYPE)
LIBRARY				:=
INCLUDES			:= -I$(DIR_GLFW)/inc -I ~/.brew/include \
						-I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all test

all: $(APP)

$(APP): $(OBJECTS)
	$(COMP) -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

test: $(OBJECTS)
	@echo plopasdi
	@rm -rf $(PATH_OBJT)
	@$(MAKE)
	@$(MAKE) $(OBJECTS_TEST)
	@$(TEST_CMD)

$(PATH_OBJT)/%: $(addprefix $(PATH_TEST)/,%.cpp)
	@mkdir -p $(PATH_OBJT)
	$(COMP) -o $@ $^ $(filter-out ,$(VAR)) $(DEBUG) $(LIBRARY) $(INCLUDES) -L. -lmath

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.cpp)
	@mkdir -p $(PATH_OBJ)
	$(COMP) -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(APP)

re: fclean $(APP)
