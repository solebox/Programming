# You may edit this makefile as long as you keep these original 
# target names defined.

# Not intended for manual invocation.
# Invoked if automatic builds are enabled.
# Analyzes only on those sources that have changed.
# Does not build executables.
autobuild:
	$(GNATMAKE) -gnatc -c -k  -d -P -gnat95 "$(GPRPATH)"

# Clean the root project of all build products.
clean:
	$(GNATCLEAN) -P "$(GPRPATH)"

# Clean root project and all imported projects too.
clean_tree:
	$(GNATCLEAN) -P "$(GPRPATH)" -r

# Check *all* sources for errors, even those not changed.
# Does not build executables.
analyze:
	$(GNATMAKE) -d -f  -gnatc -c -gnat95 -k  -P "$(GPRPATH)"

# Build executables for all mains defined by the project.
build:
	$(GNATMAKE) -d -P -gnat95 "$(GPRPATH)"

# Clean, then build executables for all mains defined by the project.
rebuild: clean build
