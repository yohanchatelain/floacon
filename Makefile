all:
	$(MAKE) -C src

.PHONY: test clean

test:
	$(MAKE) -C test

clean:
	$(MAKE) -C src clean