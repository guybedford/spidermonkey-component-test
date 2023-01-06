import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';

const wasi = new WASI({});

const wasm = await WebAssembly.compile(
  await readFile(new URL('./spidermonkey_component.core.wasm', import.meta.url))
);

const instance = await WebAssembly.instantiate(wasm, {
  wasi_snapshot_preview1: wasi.wasiImport
});

wasi.start(instance);
