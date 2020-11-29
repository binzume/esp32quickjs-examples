#pragma once

#include "M5Atom.h"
#include "esp32/QuickJS.h"

class M5QuickJS : public ESP32QuickJS {
 protected:
  static const int MATRIX_SIZE = 5;
  uint8_t display_buf[2 + MATRIX_SIZE * MATRIX_SIZE * 3] = {MATRIX_SIZE,
                                                            MATRIX_SIZE};
  void setup(JSContext *ctx, JSValue global) override {
    ESP32QuickJS::setup(ctx, global);
    M5.dis.displaybuff(display_buf);

    static const JSCFunctionListEntry m5_funcs[] = {
        JSCFunctionListEntry{
            "buttonState", 0, JS_DEF_CGETSET, 0, {getset : {btn_state, nullptr}}},
    };

    JSValue m5 = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, global, "m5", m5);
    JS_SetPropertyFunctionList(ctx, m5, m5_funcs,
                               sizeof(m5_funcs) / sizeof(JSCFunctionListEntry));

    // setup matrix
    JSValue matrix = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, m5, "matrix", matrix);
    JS_SetPropertyStr(ctx, matrix, "set",
                      JS_NewCFunction(ctx, matrix_set, "set", 2));
  }

  static JSValue matrix_set(JSContext *ctx, JSValueConst jsThis, int argc,
                            JSValueConst *argv) {
    M5QuickJS *qjs = (M5QuickJS *)JS_GetContextOpaque(ctx);
    uint32_t pos, color;
    JS_ToUint32(ctx, &pos, argv[0]);
    JS_ToUint32(ctx, &color, argv[1]);
    if (pos >= MATRIX_SIZE * MATRIX_SIZE) {
      return JS_UNDEFINED;
    }
    qjs->display_buf[pos * 3 + 2] = (uint8_t)(color >> 16);
    qjs->display_buf[pos * 3 + 3] = (uint8_t)(color >> 8);
    qjs->display_buf[pos * 3 + 4] = (uint8_t)color;
    M5.dis.displaybuff(qjs->display_buf);
    return JS_UNDEFINED;
  }

  static JSValue btn_state(JSContext *ctx, JSValueConst jsThis, int argc,
                           JSValueConst *argv) {
    return JS_NewBool(ctx, M5.Btn.isPressed());
  }
};
