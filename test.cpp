#include <node/node.h> // 중요 1. header
#include <nan.h>
#include <iostream>
#include<string>


 namespace demo {
      
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Number;
    using v8::Value;
       
    void Method1(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();
            args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
    }
    
    void Method2(const FunctionCallbackInfo<Value>& args) {
        if (args.Length() != 2) {
            std::cout<<"Invalid Parameters"<<std::endl;
                return;
        }
        if (args[0]->IsNumber() && args[1]->IsNumber()) {
            double value = args[0]->NumberValue() + args[1]->NumberValue();
                Isolate* isolate = args.GetIsolate();
            Local<Number> num = Number::New(isolate, value);
                args.GetReturnValue().Set(num);
        }
    }

    // parse json data example
    void Method3(const FunctionCallbackInfo<Value> &args){

        v8::Local<v8::Object> jsonObj = args[0]->ToObject();

        v8::Local<v8::String> fooProp = Nan::New("foo").ToLocalChecked();
        v8::Local<v8::String> barProp = Nan::New("bar").ToLocalChecked();

        int foo = 0;
        std::string bar = "";

        if (Nan::HasOwnProperty(jsonObj, fooProp).FromJust()) {
        v8::Local<v8::Value> fooValue = Nan::Get(jsonObj, fooProp).ToLocalChecked();
        foo = fooValue->NumberValue();
        }

        if (Nan::HasOwnProperty(jsonObj, barProp).FromJust()) {
        v8::Local<v8::Value> barValue = Nan::Get(jsonObj, barProp).ToLocalChecked();
        bar = std::string(*Nan::Utf8String(barValue->ToString()));
        }

        std::cout << "foo : " << foo << " bar : " << bar <<std::endl;        
    }

    // write json data example
    void Method4(const FunctionCallbackInfo<Value> &args)
    {
        v8::Local<v8::Object> jsonObject = Nan::New<v8::Object>();

        v8::Local<v8::String> fooProp = Nan::New("foo").ToLocalChecked();
        v8::Local<v8::String> barProp = Nan::New("bar").ToLocalChecked();

        v8::Local<v8::Value> fooValue = Nan::New(456);
        v8::Local<v8::Value> barValue = Nan::New("awesome").ToLocalChecked();

        Nan::Set(jsonObject, fooProp, fooValue);
        Nan::Set(jsonObject, barProp, barValue);

        args.GetReturnValue().Set(jsonObject);
    }
        
    void init(Local<Object> exports) { // 중요 3. Method 정의
        NODE_SET_METHOD(exports, "hello", Method1);
        NODE_SET_METHOD(exports, "sum", Method2);
        NODE_SET_METHOD(exports, "AA", Method3);
    }
    
    NODE_MODULE(addon, init) // 중요 2. 모듈 정의
        
 }

