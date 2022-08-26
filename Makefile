all:
	$(MAKE) -C src
	cp src/floacon .

.PHONY: test clean

test:
	$(MAKE) -C test

clean:
	$(MAKE) -C src clean