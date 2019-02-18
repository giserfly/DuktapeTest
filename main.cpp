#include "duktape.h"

int main(int argc, const char *argv[]) {	
	(void) argc; (void) argv;

	duk_context *ctx = duk_create_heap_default();
#if 0
	//duk_eval_string run crash	
	duk_eval_string(ctx, "'中'+'2'");	
	printf("result: %s\n", duk_get_string(ctx, -1));/* result:(null) */
	duk_pop(ctx);
#endif

#if 1
	//duk_peval_string run success, but result is null
	duk_peval_string(ctx, "'中'+'2'");	
	printf("result: %s\n", duk_get_string(ctx, -1));/* result:(null) */
	duk_pop(ctx);
#endif

#if 1 
	//CJK as parameter run success.
	duk_push_string(ctx, "function (x,y) { return x+y; }");
	duk_push_string(ctx, "function");
	duk_compile(ctx, DUK_COMPILE_FUNCTION);
	duk_push_string(ctx, "中");
	duk_push_string(ctx, "b");
	duk_call(ctx, 2);      /* [ func 中 b ] -> [ 中b ] */
	printf("function result: %s\n", duk_get_string(ctx, -1));
	duk_pop(ctx);
#endif

#if 0
	//CJK in js code run crash.
	duk_push_string(ctx, "function () { return '中'; }");
	duk_push_string(ctx, "function");
	duk_compile(ctx, DUK_COMPILE_FUNCTION);/* crash here*/
	duk_call(ctx, 0); 
	printf("function result: %s\n", duk_get_string(ctx, -1));
	duk_pop(ctx);
#endif

	duk_destroy_heap(ctx);
	exit(0);
}
