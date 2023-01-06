### Preview2 Test

Prerequisites:
* Node.js
* wasm-tools in path

```
git clone git@github.com:guybedford/spidermonkey-component-test
cd preview2-test
git submodule init && git submodule update
```

### Preview 1 Test

Demonstrates that the example does work:

```
node --experimental-wasi-unstable-preview1 test-preview1.js
```

* Executes `spidermokey_component.core.wasm` with some custom binding wrapping.

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
