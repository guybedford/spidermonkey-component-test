cp patch-host-main.rs preview2-prototyping/host/src/main.rs
cp patch-adapter.rs preview2-prototyping/src/lib.rs
cd preview2-prototyping
cargo build --target wasm32-unknown-unknown --release --features command
cargo build -p host --release
cd ..
wasm-tools component new spidermonkey_component.core.wasm --adapt wasi_snapshot_preview1=preview2-prototyping/target/wasm32-unknown-unknown/release/wasi_snapshot_preview1.wasm -o spidermonkey_component.wasm
./preview2-prototyping/target/release/host spidermonkey_component.wasm
