#include <napi.h>
#include <atomic>
#include <chrono>
#include <sstream>
#include <unistd.h> // Para obtener el PID
#include <mutex>
#include "CClass.hpp"

std::atomic<int> iteration1(0);
std::atomic<int> iteration2(0);
std::atomic<int> iteration3(0);

std::mutex threadIdMutex1;
std::mutex threadIdMutex2;
std::mutex threadIdMutex3;

class LoopWorker : public Napi::AsyncWorker {
public:
    LoopWorker(Napi::Function& callback, std::atomic<int>& iteration, std::mutex& threadIdMutex)
        : Napi::AsyncWorker(callback), iteration(iteration), threadIdMutex(threadIdMutex) {}

    void Execute() override {
        for (int i = 0; i < 10000000; ++i) {
            iteration = i;
            // Reemplazar std::this_thread::sleep_for con una alternativa
            usleep(1000); // Agregar un retraso de 1 milisegundo
        }
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        Callback().Call({Env().Null(), Napi::String::New(Env(), "Loop completed")});
        
        CClass cl;
        cl.method();
    }

private:
    std::atomic<int>& iteration;
    std::mutex& threadIdMutex;
};

Napi::Value StartLoops(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Function callback = info[0].As<Napi::Function>();

    LoopWorker* worker1 = new LoopWorker(callback, iteration1, threadIdMutex1);
    LoopWorker* worker2 = new LoopWorker(callback, iteration2, threadIdMutex2);
    LoopWorker* worker3 = new LoopWorker(callback, iteration3, threadIdMutex3);

    worker1->Queue();
    worker2->Queue();
    worker3->Queue();

    return Napi::String::New(env, "Loops started");
}

Napi::Value GetIteration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int loopNumber = info[0].As<Napi::Number>().Int32Value();
    int iteration = 0;
    if (loopNumber == 1) {
        iteration = iteration1.load();
    } else if (loopNumber == 2) {
        iteration = iteration2.load();
    } else if (loopNumber == 3) {
        iteration = iteration3.load();
    }

    pid_t pid = getpid(); // Obtener el PID del proceso

    Napi::Object result = Napi::Object::New(env);
    result.Set("iteration", Napi::Number::New(env, iteration));
    result.Set("pid", Napi::Number::New(env, pid));

    return result;
}

Napi::Value GetPIDs(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    pid_t pid = getpid(); // Obtener el PID del proceso

    Napi::Array pids = Napi::Array::New(env, 3);
    pids.Set((uint32_t)0, Napi::Number::New(env, pid));
    pids.Set((uint32_t)1, Napi::Number::New(env, pid));
    pids.Set((uint32_t)2, Napi::Number::New(env, pid));

    return pids;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "startLoops"), Napi::Function::New(env, StartLoops));
    exports.Set(Napi::String::New(env, "getIteration"), Napi::Function::New(env, GetIteration));
    exports.Set(Napi::String::New(env, "getPIDs"), Napi::Function::New(env, GetPIDs));
    return exports;
}

NODE_API_MODULE(addon, Init)