WASI_SDK ?= /opt/wasi-sdk
WASI_CXX ?= $(WASI_SDK)/bin/clang++
WASI_CC ?= $(WASI_SDK)/bin/clang
WASM_TOOLS ?= $(shell which wasm-tools)
WASM_OPT ?= ../binaryen/bin/wasm-opt
WIT_BINDGEN := $(shell which wit-bindgen)

ifndef WIT_BINDGEN
	WIT_BINDGEN = $(error No wit-bindgen in PATH, consider doing cargo install --git https://github.com/bytecodealliance/wit-bindgen wit-bindgen-cli)
endif

ifndef JSCT
	JSCT = $(error No JSCT in PATH. Run npm install -g jsct)
endif

ifndef WASM_OPT
	WASM_OPT = $(error No Binaryen wasm-opt in PATH)
endif

ifndef WASM_TOOLS
	WASM_TOOLS = $(error No wasm-tools in PATH. First run "cargo install wasm-tools")
endif

SM_SRC := spidermonkey-wasi-embedding/release

CXX_FLAGS := -std=gnu++20 -Wall -Werror -Qunused-arguments
CXX_FLAGS += -fno-sized-deallocation -fno-aligned-new -mthread-model single
CXX_FLAGS += -fPIC -fno-rtti -fno-exceptions -fno-math-errno -pipe
CXX_FLAGS += -fno-omit-frame-pointer -funwind-tables -I$(SM_SRC/include)
CXX_FLAGS += --sysroot=$(WASI_SDK)/share/wasi-sysroot# -DDEBUG

CXX_OPT ?= -O2

CFLAGS := -Wall -Werror -Wno-unknown-attributes -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

LD_FLAGS := -Wl,-z,stack-size=1048576 -Wl,--stack-first -lwasi-emulated-getpid

DEFINES ?=

# This is required when using spidermonkey headers, as it allows us to enable
# the streams library when setting up the js context.
DEFINES += -DMOZ_JS_STREAMS

OBJS := $(patsubst src/%.cpp,obj/%.o,$(wildcard src/*.cpp))

../spidermonkey_component.core.wasm: $(OBJS) | $(SM_SRC)
	PATH="$(FSM_SRC)/scripts:$$PATH" $(WASI_CXX) $(CXX_FLAGS) $(CXX_OPT) $(DEFINES) $(LD_FLAGS) -o $@ $^ $(SM_SRC)/lib/*.o $(SM_SRC)/lib/*.a

../spidermonkey_component.core.opt.wasm: ../spidermonkey_component.core.wasm
	$(WASM_OPT) --strip-debug -o $@ $^

obj/%.o: src/%.cpp Makefile | $(SM_SRC) obj
	$(WASI_CXX) $(CXX_FLAGS) -O2 $(DEFINES) -I $(SM_SRC)/include -Iworld -MMD -MP -c -o $@ $<

obj:
	mkdir -p obj

$(SM_SRC):
	cd spidermonkey-wasi-embedding && ./download-engine.sh

clean:
	rm -r obj && rm component-runtime.wasm
