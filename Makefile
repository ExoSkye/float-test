.SUFFIXES:

define generate_target
build/$1_$2_$3_test: test.c
	@echo -e "Building Test (Compiler: $1, Optim Level: -$3, Floating Point Type: $2)"
	@mkdir -p times
	@mkdir -p build
	@$1 -$3 -DFLOAT_TYPE=$2 test.c -o build/$1_$2_$3_test
all:: build/$1_$2_$3_test

.PHONY: run_$1_$2_$3_test

run_$1_$2_$3_test: build/$1_$2_$3_test
	@echo -e "Running Test (Compiler: $1, Optim Level: -$3, Floating Point Type: $2)"
	@build/$1_$2_$3_test > times/$1_$2_$3

test:: run_$1_$2_$3_test
endef

OPTIMS := O0 O1 O2 O3 Ofast Os Oz
COMPILERS := clang gcc
FLOATS := float double

define time
echo -e "`cat times`\n$1\n$(shell time $(shell pwd)/$1)" 2> times > times
endef

$(foreach optim,$(OPTIMS),$(eval $(foreach type,$(FLOATS),$(eval $(foreach compiler,$(COMPILERS),$(eval $(call generate_target,$(compiler),$(type),$(optim))))))))

clean:
	rm -rf build times
