all:
	$(MAKE) -C src/ipf_unpacker

clean:
	$(MAKE) clean -C src/ipf_unpacker

release:
	$(MAKE) release -C src/ipf_unpacker
