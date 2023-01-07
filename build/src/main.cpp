#include <cstdio>

// TODO: remove these once the warnings are fixed
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#include <jsapi.h>
#include <js/Initialization.h>
#include <js/Exception.h>
#include "js/ContextOptions.h"
#include "js/Initialization.h"
#include "js/SourceText.h"
#include "jsfriendapi.h"
#include <js/Conversions.h>
#include <js/Modules.h>
#include <js/ArrayBuffer.h>

#include "js/ForOfIterator.h"
#include "js/Object.h"
#include "js/Promise.h"

#include <js/CompilationAndEvaluation.h>
#include <js/SourceText.h>

static JSClass global_class = {"global", JSCLASS_GLOBAL_FLAGS, &JS::DefaultGlobalClassOps};

int main () {
  printf("Initializing\n");

  if (!JS_Init())
    return 1;

  auto cx = JS_NewContext(JS::DefaultHeapMaxBytes);
  if (!cx)
    return 1;

  if (!js::UseInternalJobQueues(cx) || !JS::InitSelfHostedCode(cx))
    return 1;

  // // TODO: check if we should set a different creation zone.
  JS::RealmOptions realm_options;
  realm_options.creationOptions()
      .setFreezeBuiltins(true)
      .setStreamsEnabled(true)
      .setReadableByteStreamsEnabled(true)
      .setBYOBStreamReadersEnabled(true)
      .setReadableStreamPipeToEnabled(true)
      .setWritableStreamsEnabled(true)
      .setWeakRefsEnabled(JS::WeakRefSpecifier::EnabledWithoutCleanupSome);

  // JS::DisableIncrementalGC(cx);
  // JS_SetGCParameter(cx, JSGC_MAX_EMPTY_CHUNK_COUNT, 1);
  auto global = JS::PersistentRootedObject(cx, JS_NewGlobalObject(cx, &global_class, nullptr, JS::FireOnNewGlobalHook, realm_options));
  if (!global)
    return 1;

  JSAutoRealm ar(cx, global);
  if (!JS::InitRealmStandardClasses(cx)) {
    return 1;
  }

  const char* js_file = "hello.js";

  JS::CompileOptions compile_options(cx);
  compile_options.setFileAndLine(js_file, 1);

  const char* js_src = R"js(
    export function hello() { return 'world' }
  )js";

  JS::SourceText<mozilla::Utf8Unit> moz_source;
  if (!moz_source.init(cx, js_src, strlen(js_src), JS::SourceOwnership::Borrowed)) {
    return 1;
  }

  JSObject* mod_obj = JS::CompileModule(cx, compile_options, moz_source);
  if (!mod_obj)
    return 1;

  JS::PersistentRootedObject mod(cx, mod_obj);

  if (!JS::ModuleLink(cx, mod))
    return 1;

  // Result value, used for top-level await.
  JS::RootedValue rval(cx);

  // Execute the module bytecode.
  if (!JS::ModuleEvaluate(cx, mod, &rval))
    return 1;

  // Store the namespace
  auto ns = JS::PersistentRootedObject(cx, JS::GetModuleNamespace(cx, mod));

  js::RunJobs(cx);
  JS_MaybeGC(cx);

  printf("Intialization completed successfully\n");
  return 0;
}