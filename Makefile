NAME = svc

CC = cl
CFLAGS = /nologo /Wall /WX /W3 /EHsc /I inc
OFLAG = /Zi

LFLAGS = advapi32.lib $(OFLAG)

OBJ_DIR = obj

SRC = src\main.cpp

OBJ = $(OBJ_DIR)\main.obj

all: $(NAME)

$(NAME): $(OBJ)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(OBJ) /Fe$(NAME) $(LFLAGS)

$(OBJ_DIR)\main.obj: src\main.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) /c $(CFLAGS) $(OFLAG) src\main.cpp /Fo$(OBJ_DIR)\main.obj

clean:
	@if exist $(OBJ_DIR)\*.obj del /Q $(OBJ_DIR)\*.obj
	@if exist $(OBJ_DIR)\*.pdb del /Q $(OBJ_DIR)\*.pdb
	@echo Objects removed

fclean: clean
	@if exist $(NAME) del /Q $(NAME)
	@echo Executable removed

re: fclean all
