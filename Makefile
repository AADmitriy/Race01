CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = ./obj
SRCDIR = ./src
HEADERFILES = ./inc

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

BINARY = part_of_the_matrix

all: $(BINARY)

$(BINARY): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJFILES): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERFILES)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HEADERFILES)

$(OBJDIR):
	mkdir -p $@

uninstall: clean
	rm -f $(BINARY)

clean:
	rm -r -f $(OBJDIR)

reinstall: uninstall all
