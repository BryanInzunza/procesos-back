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
        : Napi::AsyncWorker(callback), iteration(iteration), threadIdMutex(threadIdMutex), resetFlag(false), pauseFlag(false) {}

    void Execute() override {
        for (int i = iteration.load(); i < 100; ++i) {
            if (resetFlag.load()) {
                iteration.store(0);
                resetFlag.store(false);
                i = 0;
            }
            while (pauseFlag.load()) {
                usleep(100000); // Esperar 100ms mientras está en pausa
            }
            iteration = i;
            usleep(500000); // Agregar un retraso de 1 segundo
        }
    }

    void OnOK() override {
        Napi::HandleScope scope(Env());
        Callback().Call({Env().Null(), Napi::String::New(Env(), "Loop completed")});

        CClass myCClass;
        myCClass.method(); // Llamamos al método de otra clase
    }

    void Reset() {
        resetFlag.store(true);
    }

    void Pause() {
        pauseFlag.store(true);
    }

    void Resume() {
        pauseFlag.store(false);
    }

private:
    std::atomic<int>& iteration;
    std::mutex& threadIdMutex;
    std::atomic<bool> resetFlag;
    std::atomic<bool> pauseFlag;
};

std::unique_ptr<LoopWorker> worker1;
std::unique_ptr<LoopWorker> worker2;
std::unique_ptr<LoopWorker> worker3;

Napi::Value StartLoops(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Function callback = info[0].As<Napi::Function>();

    worker1 = std::make_unique<LoopWorker>(callback, iteration1, threadIdMutex1);
    worker2 = std::make_unique<LoopWorker>(callback, iteration2, threadIdMutex2);
    worker3 = std::make_unique<LoopWorker>(callback, iteration3, threadIdMutex3);

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

Napi::Value ResetIteration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int loopNumber = info[0].As<Napi::Number>().Int32Value();

    if (loopNumber == 1 && worker1) {
        worker1->Reset();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 1 reset"));
        return result;
    } else if (loopNumber == 2 && worker2) {
        worker2->Reset();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 2 reset"));
        return result;
    } else if (loopNumber == 3 && worker3) {
        worker3->Reset();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 3 reset"));
        return result;
    }

    Napi::Object result = Napi::Object::New(env);
    result.Set("message", Napi::String::New(env, "Worker not found"));
    return result;
}

Napi::Value PauseIteration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int loopNumber = info[0].As<Napi::Number>().Int32Value();

    if (loopNumber == 1 && worker1) {
        worker1->Pause();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 1 paused"));
        return result;
    } else if (loopNumber == 2 && worker2) {
        worker2->Pause();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 2 paused"));
        return result;
    } else if (loopNumber == 3 && worker3) {
        worker3->Pause();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 3 paused"));
        return result;
    }

    Napi::Object result = Napi::Object::New(env);
    result.Set("message", Napi::String::New(env, "Worker not found"));
    return result;
}

Napi::Value ResumeIteration(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int loopNumber = info[0].As<Napi::Number>().Int32Value();

    if (loopNumber == 1 && worker1) {
        worker1->Resume();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 1 resumed"));
        return result;
    } else if (loopNumber == 2 && worker2) {
        worker2->Resume();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 2 resumed"));
        return result;
    } else if (loopNumber == 3 && worker3) {
        worker3->Resume();
        Napi::Object result = Napi::Object::New(env);
        result.Set("message", Napi::String::New(env, "Iteration 3 resumed"));
        return result;
    }

    Napi::Object result = Napi::Object::New(env);
    result.Set("message", Napi::String::New(env, "Worker not found"));
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
    exports.Set(Napi::String::New(env, "resetIteration"), Napi::Function::New(env, ResetIteration));
    exports.Set(Napi::String::New(env, "pauseIteration"), Napi::Function::New(env, PauseIteration));
    exports.Set(Napi::String::New(env, "resumeIteration"), Napi::Function::New(env, ResumeIteration));
    return exports;
}

NODE_API_MODULE(addon, Init)