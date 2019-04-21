# -*- coding: utf-8 -*-

# Key: Example key (query parameter 'e')
# Value: Example
#  'n' : title
#  'i' : index for sorting
#  's' : source
EXAMPLES = {
    'h0': {'i' : 0,
           'n' : '00 - Hello World!',
           's' : 'print("Hello World!")'},
    'h1': {'i' : 1,
           'n' : '01 - Function',
           's' : '''def main() {
  print("Hello World!")
}

main()
'''},
    'h2': {'i' : 2,
           'n' : '02 - Synth',
           's' : '''def Kernel.main() {
  var i int
  var t int = 0
  for i = 0; i < 10; i++ {
    print(i)
    t += i
  }
  print(t)
}

Kernel.main()
Kernel.compile()
Kernel.writeHdl("sum.v")

'''},
    'h3': {'i' : 3,
           'n' : '03 - Memory',
           's' : '''def Kernel.main() {
  var i int
  var t int = 0
  for i = 0; i < 10; i++ {
    t += i
  }
  Memory.write(0, t)
}

print(Memory.read(0))
Kernel.main()
print(Memory.read(0))

Kernel.compile()
Kernel.writeHdl("sum.v")

'''},
    'h4': {'i' : 4,
           'n' : '04 - Ext entry',
           's' : '''@ExtEntry()
def Kernel.fn(in #32) (#32) {
  var i int
  var t #32 = 0
  for i = 0; i < in; i++ {
    t += i
  }
  return t
}

Kernel.compile()
Kernel.writeHdl("sum.v")

'''},
    'h5': {'i' : 5,
           'n' : '05 - Test',
           's' : '''channel Kernel.in int
channel Kernel.out int

def Kernel.f(arg int) (int) {
  var i int
  var t int = 0
  for i = 0; i < arg; i++ {
    t += i
  }
  return t
}

def Kernel.main() {
  out.write(f(in.read()))
}

Kernel.compile()
Kernel.writeHdl("sum.v")

var T object = Kernel.clone()
def T.main() {
  assert(f(10) == 45)
}

T.main()
T.compile()
T.writeHdl("sum_test.v")

'''},
    'h6': {'i' : 6,
           'n' : '06 - Thread',
           's' : '''channel Kernel.req int
channel Kernel.resp int

@ThreadEntry()
def Kernel.f() {
  resp.write(req.read() + 1)
}

@ThreadEntry()
def Kernel.g() {
  req.write(10)
  print(resp.read())
}

Kernel.compile()
Kernel.writeHdl("thr.v")
'''},
    'h7': {'i' : 7,
           'n' : '07 - Member',
           's' : '''var O object = Kernel.clone()
var M object = Kernel.clone()
var O.M object = M
def M.f(a int) (int) {
  return a + 1
}

def O.main() {
  print(M.f(10))
}

O.compile()
O.writeHdl("call.v")
'''},
    'h8': {'i' : 8,
           'n' : '08 - External port',
           's' : '''var L object = Kernel.clone()

@embed(output = "led")
def L.f(b bool) {
  // print(b)
}

def L.main() {
  var b bool = false;
  while (true) {
    wait(10000000)
    f(b)
    b = ~b
  }
}

L.compile();
L.writeHdl("led.v")
'''},
    'h9': {'i' : 9,
           'n' : '09 - Embedded module',
           's' : '''var M object = Kernel.clone();

@embed(    resource = "wait_cycles",
    verilog = "karuta_wait.v",
    ack = "ack",
    file= "copy",
    module= "wait_cycles")
def M.my_wait(cycles int) {
  print(cycles)
}

def M.main() {
  my_wait(10)
}

M.compile()
M.writeHdl("wait.v")
'''},
    'h10': {'i' : 10,
           'n' : '10 - Misc',
           's' : '''var M object = Kernel.clone()

def M.main() {
  var i int
  for i = 0; i < 10; i++ {
  }
}

M.setSynthParam("resetPolarity", "0")
M.setDump("zz")
M.compile()
M.writeHdl("dummy.v")
M.writeHdl("dummy.cpp")
'''},
    'default': {'i' : 999,
                'n' : 'Synth example',
         's' : '''def main() {
  var i int
  var s int = 0
  for i = 0; i < 10; ++i {
    s += i
  }
  // TODO: Do real I/O.
  print(s)
}

// Synthesize and output.
compile()
writeHdl("a.v")
writeHdl("a.html")

// Run on interpreter mode.
main()
'''}
}
