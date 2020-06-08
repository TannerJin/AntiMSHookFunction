# AntiMSHookFunction


AntiMSHookFunction is an AntiHook library for MSHookFunction at runtime (make MSHookFunction doesn't work)    
include `MSHookFunction Check` and `Anti-MSHookFunction`

[Swift-Version](https://github.com/TannerJin/IOSSecuritySuite/blob/master/IOSSecuritySuite/MSHookFunctionChecker.swift)

## Usage 

```c
void* orig_antiDebug = antiMSHook(antiDebug);
    
if (orig_antiDebug == NULL) {
    printf("[+++] Not MSHook");
    antiDebug();
} else {
    printf("[+++] AntiMSHook 🚀🚀🚀");
    typedef void AntiDebug(void);
    AntiDebug *_antiDebug = (AntiDebug *)orig_antiDebug;
    _antiDebug();
}

void antiDebug() {
    resetSymbol(@"dlopen");   // anti-fishhook
    resetSymbol(@"dlsym");    // anti-fishhook
    
    void* handle = dlopen("/usr/lib/libc.dylib", RTLD_NOW);
    void* ptrace = dlsym(handle, "ptrace");
    
    typedef int Ptrace(int, pid_t, int, int);
    Ptrace *_ptrace = (Ptrace *)ptrace;
    _ptrace(31, 0, 0, 0);
    dlclose(handle);
}

```
