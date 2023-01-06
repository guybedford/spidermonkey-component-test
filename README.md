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
Error: error while executing at wasm backtrace:
    0: 0x543191 - <unknown>!<wasm function 1>
    1: 0x1c58 - <unknown>!wasi_snapshot_preview1::bindings::wasi_poll::write_stream::h9856baf29daf0aa1
    2: 0x1474 - <unknown>!fd_write
    3: 0x54325d - <unknown>!<wasm function 15>
    4: 0x4df391 - <unknown>!<wasm function 12473>
    5: 0x4e1090 - <unknown>!<wasm function 12522>
    6: 0x4e1109 - <unknown>!<wasm function 12523>
    7: 0x4e1d77 - <unknown>!<wasm function 12552>
    8: 0x4e1798 - <unknown>!<wasm function 12533>
    9: 0x4e1c33 - <unknown>!<wasm function 12546>
   10: 0x922e - <unknown>!<wasm function 25>
   11: 0x8bc2 - <unknown>!<wasm function 20>
   12:  0x6fc - <unknown>!command

Caused by:
    StreamError
```