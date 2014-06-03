NAME	=	client
OBJ_DIR	=	obj
CC	=	g++

SRC	=	$(shell find . -name "*.cpp" -printf "%P ")
OBJ	=	$(SRC:%.cpp=$(OBJ_DIR)/%.o)
TMP	=	$(SRC:%=%~)
DEPS	=	$(OBJ:.o=.d)

OBJDBG	=	$(OBJ:%=%.dbg)
DEPSDBG	=	$(DEPS:%=%.dbg)
NAMEDBG	=	$(NAME:%=%.dbg)

LIB	=	-lzmq
INC	=	
CXXFLAGS =	-std=c++11 -W -Wall -O3 $(LIB) $(INC)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

-include $(DEPS)
$(OBJ_DIR)/%.o	:	%.cpp
			@mkdir -p `dirname $@`
			$(CC) -MM -MF $(@:.o=.d) -MT $@ $< $(CXXFLAGS)
			$(CC) -c -o $@ $< $(CXXFLAGS)


$(NAMEDBG)	:	$(OBJDBG)
			@mkdir -p $(BIN_DIR)
			$(CC) $(SHARED) -g -o $(NAMEDBG) $(OBJDBG) $(CXXFLAGS)

-include $(DEPSDBG)
$(OBJ_DIR)/%.o.dbg	:	%.cpp
				@mkdir -p `dirname $@`
				$(CC) -MM -MF $(@:.o.dbg=.d.dbg) -MT $@ $< $(CXXFLAGS)
				$(CC) -g -c -o $@ $< $(CXXFLAGS)


all	:	$(NAME)

debug	:	$(NAMEDBG)

clean	:
		rm -rf $(OBJ) $(TMP) $(DEPS) $(OBJDBG) $(DEPSDBG) *~

fclean	:	clean
		rm -rf $(NAME) $(NAMEDBG)

re	:	fclean all

redebug	:	fclean debug

run	:	$(NAME)
		@./$(NAME) $(ARGS)
