//
//  JSWeakRefConstructor.cpp
//  NativeScript
//
//  Created by Yavor Georgiev on 02.10.14.
//  Copyright (c) 2014 г. Telerik. All rights reserved.
//

#include "JSWeakRefConstructor.h"
#include "JSWeakRefInstance.h"
#include "JSWeakRefPrototype.h"

namespace NativeScript {
using namespace JSC;

static EncodedJSValue JSC_HOST_CALL construct(ExecState* execState) {
    JSValue argument = execState->argument(0);
    if (!argument.isObject()) {
        VM& vm = execState->vm();
        auto scope = DECLARE_THROW_SCOPE(vm);
        return JSValue::encode(scope.throwException(execState, createError(execState, argument, "must be an object"_s, defaultSourceAppender)));
    }

    GlobalObject* globalObject = jsCast<GlobalObject*>(execState->lexicalGlobalObject());
    auto weakRef = JSWeakRefInstance::create(execState->vm(), globalObject->weakRefInstanceStructure(), argument.toObject(execState));
    return JSValue::encode(weakRef.get());
}

const ClassInfo JSWeakRefConstructor::s_info = { "WeakRef", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSWeakRefConstructor) };

JSWeakRefConstructor::JSWeakRefConstructor(VM& vm, Structure* structure)
    : Base(vm, structure, construct, construct) {
}

void JSWeakRefConstructor::finishCreation(VM& vm, JSWeakRefPrototype* prototype) {
    Base::finishCreation(vm, "WeakRef"_s);

    this->putDirectWithoutTransition(vm, vm.propertyNames->prototype, prototype, PropertyAttribute::DontEnum | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);
    this->putDirectWithoutTransition(vm, vm.propertyNames->length, jsNumber(1), PropertyAttribute::ReadOnly | PropertyAttribute::DontEnum | PropertyAttribute::DontDelete);
}

} // namespace NativeScript
