all:
	$(MAKE) -C src
	cp src/floacon .

clean:
	$(MAKE) -C src clean