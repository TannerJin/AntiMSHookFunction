# AntiMSHookFunction


AntiMSHookFunction is an AntiHook library for MSHookFunction at runtime (make MSHookFunction don't work)    
inlcude `MSHookFunction Check` and `Anti-MSHookFunction`

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
    void* handle = dlopen("/usr/lib/libc.dylib", RTLD_NOW);
    void* ptrace = dlsym(handle, "ptrace");
    
    typedef void Ptrace(int, pid_t, int, int);
    Ptrace *_ptrace = (Ptrace *)ptrace;
    _ptrace(31, 0, 0, 0);
    dlclose(handle);
}

```
