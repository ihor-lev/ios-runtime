//
//  ReferenceTypeInstance.h
//  NativeScript
//
//  Created by Yavor Georgiev on 21.06.14.
//  Copyright (c) 2014 г. Telerik. All rights reserved.
//

#ifndef __NativeScript__ReferenceTypeInstance__
#define __NativeScript__ReferenceTypeInstance__

#include "FFIType.h"
#include <JavaScriptCore/JSObject.h>
#include <string>

namespace NativeScript {
class ReferenceTypeInstance : public JSC::JSDestructibleObject {
public:
    typedef JSC::JSDestructibleObject Base;

    static JSC::Strong<ReferenceTypeInstance> create(JSC::VM& vm, JSC::Structure* structure, JSC::JSCell* innerType) {
        JSC::Strong<ReferenceTypeInstance> cell(vm, new (NotNull, JSC::allocateCell<ReferenceTypeInstance>(vm.heap)) ReferenceTypeInstance(vm, structure));
        cell->finishCreation(vm, innerType);
        return cell;
    }

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype) {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

    JSC::JSCell* innerType() const {
        return this->_innerType.get();
    }

    const FFITypeMethodTable& ffiTypeMethodTable() const {
        return this->_ffiTypeMethodTable;
    }

protected:
    ReferenceTypeInstance(JSC::VM& vm, JSC::Structure* structure)
        : Base(vm, structure) {
    }
    FFITypeMethodTable _ffiTypeMethodTable;
    void finishCreation(JSC::VM&, JSC::JSCell*);
    JSC::WriteBarrier<JSC::JSCell> _innerType;
    static void visitChildren(JSC::JSCell*, JSC::SlotVisitor&);
    static JSC::CallType getCallData(JSC::JSCell* cell, JSC::CallData& callData);

private:
    static void destroy(JSC::JSCell* cell) {
        static_cast<ReferenceTypeInstance*>(cell)->~ReferenceTypeInstance();
    }

    static JSC::JSValue read(JSC::ExecState*, void const*, JSC::JSCell*);

    static void write(JSC::ExecState*, const JSC::JSValue&, void*, JSC::JSCell*);

    static bool canConvert(JSC::ExecState*, const JSC::JSValue&, JSC::JSCell*);

    static const char* encode(JSC::VM&, JSC::JSCell*);

    std::string _compilerEncoding;
};
} // namespace NativeScript

#endif /* defined(__NativeScript__ReferenceTypeInstance__) */
