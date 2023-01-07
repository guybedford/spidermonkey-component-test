### Preview2 Test

Prerequisites:
* Wasmtime
* wasm-tools in path

```
git clone git@github.com:guybedford/spidermonkey-component-test
cd spidermonkey-component-test
git submodule init && git submodule update
```

### Preview 1 Test

Demonstrates that the example does work:

```
wasmtime spidermonkey_component.core.wasm
```

Result:

```
Initializing
Initialization completed successfully
```

### Preview 2 Test

```
./test-preview2.sh
```

* Builds the preview2 adapter
* Runs `wasm-tools new` to generate the component
* Executes the component with preview2-prototyping host as a command

Result:

```
Initializing
Level::Info I/O: Intialization completed successfully
```

Where the "correct" prompt comes from patching a closed file descriptor to a log

### Building the Embedding

```
cd build
make
```