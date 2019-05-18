
SHELL=/bin/bash
ifndef .VERBOSE
    .SILENT:
endif
ROOT=$(shell pwd)
CXX=clang++
CC=clang
CCIGNORE=
CXXIGNORE=
CCFLAGS=-fPIC -Wall -Wpedantic --static
CXXFLAGS=-std=c++17 -fPIC -Wall -Wpedantic --static
LINK=
SOURCE=src
INCLUDE_DIR=include
INCLUDE=
BUILD=build
COMMON_INCLUDE=-I$(ROOT)/$(INCLUDE_DIR) $(INCLUDE)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[1;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C++ object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef

all: build-finxi.out
clean: clean-finxi.out
install: install-finxi.out
uninstall: uninstall-finxi.out

# FINXI.OUT {{{

FINXI.OUT=finxi.out
FINXI.OUT_FILES=$(SOURCE)/main.c
FINXI.OUT_OBJS=$(FINXI.OUT_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(FINXI.OUT_OBJS:.o=.d)

build-finxi.out: build-libfinxi.a pre-finxi.out $(FINXI.OUT)
	$(call complete_target,$(shell basename $(FINXI.OUT)))

clean-finxi.out:
	$(call clean_target,$(shell basename $(FINXI.OUT)))
	if [ -e "$(FINXI.OUT)" ]; then rm $(FINXI.OUT); fi

pre-finxi.out:
	$(call scan_target,$(shell basename $(FINXI.OUT)))

$(FINXI.OUT): $(FINXI.OUT_OBJS) FORCE
	$(call print_link_exe,$(shell basename $(FINXI.OUT)))
	$(CXX) $(FINXI.OUT_OBJS) $(LIBFINXI.A) $(LINK) $(COMMON_INCLUDE) -o $(FINXI.OUT)

install-finxi.out: build-finxi.out
	$(call install_target,$(shell basename $(FINXI.OUT)))
	mkdir -p $(INSTALL_PATH)/bin/
	cp $(FINXI.OUT) $(INSTALL_PATH)/bin

uninstall-finxi.out:
	$(call uninstall_target,$(shell basename $(FINXI.OUT)))
	if [ -e "$(INSTALL_PATH)/bin/$(shell basename $(FINXI.OUT))" ]; then rm $(INSTALL_PATH)/bin/$(shell basename $(FINXI.OUT)); fi

# }}}
# LIBFINXI.A {{{

LIBFINXI.A=$(BUILD)/libfinxi.a
LIBFINXI.A_FILES=$(filter-out $(SOURCE)/main.c, $(shell find "$(SOURCE)/" -name "*.c"))
LIBFINXI.A_OBJS=$(LIBFINXI.A_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(LIBFINXI.A_OBJS:.o=.d)

build-libfinxi.a:  pre-libfinxi.a $(LIBFINXI.A)
	$(call complete_target,$(shell basename $(LIBFINXI.A)))

clean-libfinxi.a: 
	$(call clean_target,$(shell basename $(LIBFINXI.A)))
	if [ -e "$(LIBFINXI.A)" ]; then rm $(LIBFINXI.A); fi

pre-libfinxi.a:
	$(call scan_target,$(shell basename $(LIBFINXI.A)))

$(LIBFINXI.A): $(LIBFINXI.A_OBJS) FORCE
	$(call print_link_lib,$(shell basename $(LIBFINXI.A)))
	ar rcs $@ $(LIBFINXI.A_OBJS)
	

install-libfinxi.a: build-libfinxi.a
	$(call install_target,$(shell basename $(LIBFINXI.A)))
	mkdir -p $(INSTALL_PATH)/lib/
	mkdir -p $(INSTALL_PATH)/include/$(NAME)/
	cp $(LIBFINXI.A) $(INSTALL_PATH)/lib
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.h") $(INSTALL_PATH)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.hpp") $(INSTALL_PATH)/include/$(NAME); fi

uninstall-libfinxi.a:
	$(call uninstall_target,$(shell basename $(LIBFINXI.A)))
	if [ ! -e "$(INSTALL_PATH)/lib/$(shell basename $(LIBFINXI.A))" ]; then rm $(INSTALL_PATH)/lib/$(shell basename $(LIBFINXI.A)); fi
	if [ ! -e "$(INSTALL_PATH)/include/$(NAME)" ]; then rm $(INSTALL_PATH)/include/$(NAME) -r; fi

# }}}

$(ROOT)/$(BUILD)/%.cpp.o: %.cpp
	mkdir -p $(@D)
	$(call print_build_cpp,$@)
	$(CXX) $(CXXFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

$(ROOT)/$(BUILD)/%.c.o: %.c
	mkdir -p $(@D)
	$(call print_build_c,$@)
	$(CC) $(CCFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

FORCE:
