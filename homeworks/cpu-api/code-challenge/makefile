PROGRAMS = q1 q2

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

%: %.c
	gcc -o $@ $< -Wall -g
