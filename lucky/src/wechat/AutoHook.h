#ifndef _AUTOHOOK_H
#define _AUTOHOOK_H

#include <memory>
#include <iostream>
#include <type_traits>
#include <utility>
#include <functional>
#include <windows.h>

enum class HookModel {
    BEFORE = 0,    //执行完成HOOK函数再进入原来的函数
    RETURN = 1,    //执行完成HOOK函数就返回
    AFTER = 2      //先执行原来的函数再执行HOOK函数
};

//Hook方式
struct HookMethod {
    virtual int32_t Hook(void* o, void* n) = 0;
    virtual int32_t UnHook(void* o, void* n) = 0;
};

typedef std::shared_ptr<HookMethod> HookMethodPtr;

struct DetoursHook : public HookMethod {
    virtual int32_t Hook(void* o, void* n);
    virtual int32_t UnHook(void* o, void* n);
};

struct HookPoint {
    virtual ~HookPoint();
};

typedef std::shared_ptr<HookPoint> HookPointPtr;

template<typename T>
struct AutoHook;


//处理函数指针
template<typename RET, typename ...ARGS>
struct AutoHook<RET(*)(ARGS...)> {

    using FunctionPtr = RET(*)(ARGS...);
    using FunctionType = RET(*)(ARGS...);

    AutoHook(
        HookModel model,
        uint64_t hookAddr,
        FunctionType newFunc,
        HookMethodPtr method) {

        model_ = model;
        newFunc_ = newFunc;
        method_ = method;
        hookAddr_ = reinterpret_cast<FunctionPtr>(hookAddr);
        hookProxy = [this](ARGS...args)-> RET {
            return callInner(args...);
        };
        if (method_->Hook(&hookAddr_, &call) != 0) {
            OutputDebugString("HOOK FAIL\n");
        }
    }

    ~AutoHook() {
        std::stringstream ss;
        ss << "AutoHook~:" << std::hex  << ":" << hookAddr_ << ":" << this;
        OutputDebugString(ss.str().c_str());

        method_->UnHook(&hookAddr_, &call);
    }

    RET callInner(ARGS... args) {
        if (model_ == HookModel::RETURN) {
            return newFunc_(args...); //HOOK函数直接返回
        }
        if (model_ == HookModel::AFTER) {
            hookAddr_(args...);    //执行到旧函数
            return  newFunc_(args...); //执行到新函数
        }
        //默认
        newFunc_(args...); //执行到新函数
        return  hookAddr_(args...); //执行到旧函数
    }

    static RET call(ARGS... args) {
        return  hookProxy(args...);
    }
    HookModel model_ = HookModel::RETURN;
    FunctionPtr hookAddr_ = nullptr;
    FunctionPtr newFunc_ = nullptr;
    HookMethodPtr method_;
    static std::function<RET(ARGS...)> hookProxy;
};
template<typename RET, typename ...ARGS>
std::function<RET(ARGS...)> AutoHook<RET(*)(ARGS...)>::hookProxy;

//处理成员函数指针
template<typename Class, typename RET, typename... ARGS>
struct AutoHook<RET(Class::*)(ARGS...)> {

    using FunctionPtr = RET(*)(ARGS...);
    using FunctionType = std::function<RET(ARGS...)>;

    AutoHook(
        HookModel model,
        uint64_t hookAddr,
        FunctionType newFunc,
        HookMethodPtr  method) {

        model_ = model;
        newFunc_ = newFunc;
        method_ = method;
        hookAddr_ = reinterpret_cast<FunctionPtr>(hookAddr);


        OutputDebugString("AutoHook::AutoHook()");

        std::stringstream ss;
        ss << "hookAddr_" << std::hex << hookAddr << ":" << hookAddr_ << ":" << this;
        OutputDebugString(ss.str().c_str());


        hookProxy = [this](ARGS...args)-> RET {
            return callInner(args...);
        };
        if (method_->Hook(&hookAddr_, &call) != 0) {
            OutputDebugString("HOOK FAIL\n");
        }

        std::stringstream s2;
        s2 << "hookAddr_ s2 " << std::hex << hookAddr << ":" << hookAddr_ << ":" << this;
        OutputDebugString(s2.str().c_str());

    }
    ~AutoHook() {
        method_->UnHook(&hookAddr_, &call);
    }

    RET callInner(ARGS... args) {
        OutputDebugString("AutoHook::callInner");
        std::stringstream ss;
        ss << "hookAddr_" << std::hex << this->hookAddr_ << ":" << this;
        OutputDebugString(ss.str().c_str());
        if (model_ == HookModel::RETURN) {
            return newFunc_(args...); //HOOK函数直接返回
        }
        if (model_ ==  HookModel::AFTER) {
            hookAddr_(args...);   //执行到旧函数
            return  newFunc_(args...); //执行到新函数
        }
        //默认
        this->newFunc_(args...); //执行到新函数
        return  this->hookAddr_(args...); //执行到旧函数
    }

    static RET call(ARGS... args) {
        return  hookProxy(args...);
    }
    HookModel model_ = HookModel::RETURN;
    std::function<RET(ARGS...)> newFunc_;
    HookMethodPtr method_;
     FunctionPtr hookAddr_ ;
    static std::function<RET(ARGS...)> hookProxy;
};

template<typename Class, typename Ret, typename... Args>
std::function<Ret(Args...)> AutoHook<Ret(Class::*)(Args...)>::hookProxy;


//成员函数指针void返回值
template<typename Class, typename... ARGS>
struct AutoHook<void(Class::*)(ARGS...)> {

    using FunctionPtr = void(*)(ARGS...);
    using FunctionType = std::function<void(ARGS...)>;

    AutoHook(
        HookModel model,
        uint64_t hookAddr,
        FunctionType newFunc,
        HookMethodPtr  method) {
       
        model_ = model;
        newFunc_ = newFunc;
        method_ = method;
        hookAddr_ = reinterpret_cast<FunctionPtr>(hookAddr);
        hookProxy = [this](ARGS...args){
            callInner(args...);
        };

        if (method_->Hook(&hookAddr_, &call) != 0) {
            OutputDebugString("HOOK FAIL\n");
        }
    }
    ~AutoHook() {
        method_->UnHook(&hookAddr_, &call);
    }
    void callInner(ARGS... args) {

        if (model_ == HookModel::RETURN) {
            return newFunc_(args...); //HOOK函数直接返回
        }
        if (model_ == HookModel::AFTER) {
            hookAddr_(args...);   //执行到旧函数
            return  newFunc_(args...); //执行到新函数
        }
        //默认
        newFunc_(args...); //执行到新函数
        return  hookAddr_(args...); //执行到旧函数
    }

    static void call(ARGS... args) {
         hookProxy(args...);
    }
    HookModel model_ = HookModel::RETURN;
    std::function<void(ARGS...)> newFunc_;
    HookMethodPtr method_;
    FunctionPtr hookAddr_;
    static std::function<void(ARGS...)> hookProxy;
};

template<typename Class,typename... Args>
std::function<void(Args...)> AutoHook<void(Class::*)(Args...)>::hookProxy;

template<HookModel model, uint64_t offset, typename T>
struct AutoHookEx : public HookPoint, public AutoHook<T> {
    AutoHookEx(
        uint64_t base,
        typename AutoHook<T>::FunctionType newFunc,
        HookMethodPtr method
    ) : AutoHook<T>(model, base + offset, newFunc, method) {
    }
    ~AutoHookEx() {

    }
};


#endif // !_AUTOHOOK_H


