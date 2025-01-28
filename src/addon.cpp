#include <napi.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <sstream>
#include <unistd.h> // Para obtener el PID

std::atomic<int> iteration1(0);
std::atomic<int> iteration2(0);
std::atomic<int> iteration3(0);

std::thread::id threadId1;
std::thread::id threadId2;
std::thread::id threadId3;

void runLoop(std::atomic<int> &iteration, std::thread::id &threadId)
{
    threadId = std::this_thread::get_id();
    for (int i = 0; i < 10000000; ++i)
    {
        iteration = i;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Agregar un retraso de 1 segundo
    }
}

Napi::Value StartLoops(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    std::thread t1(runLoop, std::ref(iteration1), std::ref(threadId1));
    std::thread t2(runLoop, std::ref(iteration2), std::ref(threadId2));
    std::thread t3(runLoop, std::ref(iteration3), std::ref(threadId3));
    t1.detach();
    t2.detach();
    t3.detach();
    return Napi::String::New(env, "Loops started");
}

Napi::Value GetIteration(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int loopNumber = info[0].As<Napi::Number>().Int32Value();
    int iteration = 0;
    std::thread::id threadId;
    if (loopNumber == 1)
    {
        iteration = iteration1.load();
        threadId = threadId1;
    }
    else if (loopNumber == 2)
    {
        iteration = iteration2.load();
        threadId = threadId2;
    }
    else if (loopNumber == 3)
    {
        iteration = iteration3.load();
        threadId = threadId3;
    }

    pid_t pid = getpid(); // Obtener el PID del proceso

    std::ostringstream oss;
    oss << "Iteration: " << iteration << ", Thread ID: " << threadId << ", PID: " << pid;

    return Napi::String::New(env, oss.str());
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "startLoops"), Napi::Function::New(env, StartLoops));
    exports.Set(Napi::String::New(env, "getIteration"), Napi::Function::New(env, GetIteration));
    return exports;
}

NODE_API_MODULE(addon, Init)