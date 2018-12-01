# Karuta Language Reference Manual

## Program structure

A program is comprised of top level environment and method environment.
Methods and various things can be declared only in top level environment.

    // * Top level environment
    // Modifying objects by declaring member variables.
    //
    def f() {
      // * Method environment
      // Object modification is not allowed (hence synthesizable).
    }

TODO: Consider non synthesizable methods.

### Methods

A method is declared as a member of an object.
If no object name is given in the declaration, the method will belong to the current file object.

    // This method belong to the current file object.
    def f() {
    }
    
    @Annotation(key1="value1", key2="value2")
    def mod.f(x, y #32) (#16, #16) {
      return (0, 0)
    }

A method declaration can have an argument list and return value list.


### Threads

A thread can be be declared either by an annotation to a method or by using thread declaration syntax.

    @ThreadEntry()
    def f() {
      print("hello?")
    }
    // The interpreter to start all threads.
    run()

or

    def f() {
    }
    thread Kernel.thr1 = f()
    run()

@SoftThreadEntry() can be used instead of @ThreadEntry() to specify the method is not a target of synthesis (only for tests).

### Data flow

A method can be an entry of a data flow instead of FSM.

    @DataFlowEntry()
    def f(x int) {
    }

NOTE: WIP.

## Types

### Width spec

    var x #32
    var x int  // Same as #32
    var x #0
    var x bool // Same as bool

### Strings

    var s string = "abc"
    s = s + "1"

### Objects

    var o object = Kernel

### Arrays

    var M.x int[32]
    var M.y #16[4] = {1,2,3,4}

## Expressions

### Names

prefix '__' is reserved for implementation

### Numerics

    123    // Decimal
    0x123  // Hexadecimal
    0b1010 // Binary

### Operators

* +, -
 * Addition and subtraction.
* *
* << >>
 * shift amount should be constant.
* :: bit concat
* [l:r] range should be constant.

## Object

### Object hierarchy

An object can have member objects.

    var O.m1 object = SubObj
    def O.f() {
      m1.h()
    }

### Type object

    var Numerics.Int32 object = Object.clone()
    func Numerics.Int32.Build(arg #32) (#32) {
      return arg
    }

    func Numerics.Int32.Add(lhs, rhs #32) (#32) {
      return lhs + rhs
    }

    // Type class can't be accessed from top level environment.
    func f() {
      var x #Int32
      x = Numerics.Int32.Build(1)
      print(x + x)
    }

    // Add a method for the type.
    func Numerics.Int32.IsZero(arg #32) (bool) {
      return arg == 0
    }

    func g() {
      var x #Int32
      x = Numerics.Int32.Build(1)
      print(x.IsZero())
      x + x
    }

## Statements

### Control

* if
 * "if" statement can take a non bool number as its condition.
* for

TODO: switch/case statement

### Declarations

As for variable declaration, please see types section.

### Import

    import "fn.n"

## External communication

### Ext I/O

    @ExtIO(output = "o")
    def L.f(b bool) {
    }

    @ExtIO(input = "i")
    def L.g() (bool) {
      return true
    }

### Ext call/stub with method interface

    // f() will be callable outside of the design.
    @ExtEntry(name="e")
    def f(x int) (int) {
      return 0
    }

    // Actual implementation of f() will be outside of the design.
    @ExtStub(name="e")
    def f(x int) (int) {
      return 0
    }

#### Ext data flow

    @ExtFlowStub(name="e")
    def f(x int) (int) {
    }

#### Ext combinational logic.

    @ExtCombinational(resource = "a", verilog = "resource.v", file="copy", module="hello")
    def f(x #32) (#32) {
      return x
    }

#### AXI

    // @AxiMaster(addrWidth = "64") // or "32" to specify the width.
    // @AxiMaster(sramConnection = "shared") // or "exclusive" (default).
    @AxiMaster()
    var M.x int[32]
    def f() {
      x.load(mem_addr, count, array_addr)
    }

    @AxiSlave()
    var M.x int[32]

### Channel

A channel can be declared like

    channel M.c1 int

It can be accessed like

    c1.write(1)
    c1.read()

## Misc features (or to be classified)

### Built in methods

* Object
    * Kernel
        * Module

* Object.clone()
* Object.dump()
* Object.setDump()
* Object.assert()
* Object.Kernel()

* Kernel.abort()
* Kernel.compile()
* Kernel.exit()
* Kernel.print()
* Kernel.writeHdl()
* Kernel.bool()
* Kernel.Object()
* Kernel.Module ()

* .$compiled_module
* .$dump_file_name

#### Memory operations

Memory object represents an address space and can be accessed by read/write method.

    Memory.read(addr)

    Memory.write(addr, data)

This assumes 32bit address/data for now.

#### Iroha related methods

* setIrohaPath(p string)
* setIROuput(p string)
* runIroha(opts string)
    * e.g. runIroha("-v -S -o x.v")

#### Object distance.

WIP.

### Mailbox

    mailbox M.m1 int
    def M.f() {
      m1.put(1)
      m1.get()
    }

### Shared register

    var M.x int

### Thread local

    @ThreadLocal()
    var M.x int

## RTL generation

When compilation is requested by calling compile() method, the synthesizer takes a snapshot of the object and generates IR from the structure and computation.

    setSynthParam("resetPolarity", 0) // set negative reset (e.g. rst_n).
    setSynthParam("maxDelayPs", 10000) // 10ns
    compile()

### Profile Guided Optimization (PGO)

    Env.clearProfile()
    Env.enableProfile()
    // Run actual code.
    Env.disableProfile()

NOTE: In development.

## Format this document

 markdown LRM > LRM.html
