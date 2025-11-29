PROGRAMS = q1 q2 q3 q4 q5

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

%: %.c
	gcc -o $@ $< -Wall -g
