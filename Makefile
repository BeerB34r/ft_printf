CC				= cc
CPPFLAGS		= $(INC) -g
CFLAGS			= -Wall -Wextra -Werror -O3
LDFLAGS			=
ARFLAGS			= crs

VPATH			= $(SRCDIR)
SRC				= fa_c_alloc.c ft_printf.c get_argument.c handle_format.c handle_precision.c handle_raw.c handle_sign.c handle_width.c parse_argument.c \
					specifier_percent.c specifier_character.c specifier_string.c specifier_signed_integer.c specifier_octal.c specifier_hexadecimal.c specifier_unsigned_integer.c specifier_float.c specifier_store.c specifier_pointer.c
SRCDIR			= src/fa_c src/specifiers src/

INC				= -Iinc/

BIN				= $(addprefix $(BINDIR),$(SRC:.c=.o))
BINDIR			= bin/

DEP				= $(addprefix $(DEPDIR),$(SRC:.c=.d))
DEPDIR			= dep/
DEPFLAG			= -MM -MF $@ -MT $@ -MT $(BINDIR)$(notdir $(basename $(<:.c=.o)))

RM				= rm -fr

NAME			= libftprintf.a

MAKEFLAGS		= j
.DEFAULT_GOAL	= all
.PRECIOUS		: $(BINDIR) $(DEPDIR) $(BIN)
.PHONY			: clean fclean re all

-include $(DEP)

all				: $(NAME)

test			: $(NAME)
	$(CC) main.c $(NAME) -o test
	./test
	$(RM) test

$(NAME)			: $(NAME)($(BIN))
	$(AR) $(ARFLAGS) $@ $?

$(DEPDIR)%.d	: %.c | $(DEPDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAG) $<
$(BINDIR)%.o	: %.c | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

(%)				: % ;

%/				:
	mkdir -p $@

clean			:
	$(RM) $(BINDIR)
fclean			: clean
	$(RM) $(DEPDIR)
	$(RM) $(NAME)
re				:
	$(MAKE) fclean
	$(MAKE) all
