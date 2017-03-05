# -*- coding: utf-8 -*-

# Key: Example key (query parameter 'e')
# Value: Example
#  'n' : title
#  'i' : index for sorting
#  's' : source
EXAMPLES = {
    'h0': {'i' : 0,
           'n' : '00 - Hello World!',
           's' : 'print("Hello World!");'},
    'h1': {'i' : 1,
           'n' : '01 - Function',
           's' : '''def Kernel.main() {
  print("Hello World!");
}

main();
'''},
    'h2': {'i' : 2,
           'n' : '02 - Synth',
           's' : '''def Kernel.main() {
  int i;
  int t = 0;
  for (i = 0; i < 10; i++) {
    print(i);
    t += i;
  }
  print(t);
}

Kernel.main();
Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h3': {'i' : 3,
           'n' : '03 - Memory',
           's' : '''def Kernel.main() {
  int i;
  int t = 0;
  int *p = 0;
  for (i = 0; i < 10; i++) {
    t += i;
  }
  *p = t;
}

int *q = 0;
print(*q);
Kernel.main();
print(*q);

Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h3': {'i' : 3,
           'n' : '03 - Channel',
           's' : '''channel Kernel.in = int #64;
channel Kernel.out = int #64;

def Kernel.main() {
  int #64 arg = *in;
  int i;
  int #64 t = 0;
  for (i = 0; i < arg; i++) {
    t += i;
  }
  *out = t;
}

Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h4': {'i' : 4,
           'n' : '04 - Test',
           's' : '''channel Kernel.in = int;
channel Kernel.out = int;

def Kernel.f(int arg) (int) {
  int i;
  int t = 0;
  for (i = 0; i < arg; i++) {
    t += i;
  }
  return t;
}

def Kernel.main() {
  *out = f(*in);
}

Kernel.compile();
Kernel.writeHdl("sum.v");

object T = Kernel.clone();
def T.main() {
  assert(f(10) == 45);
}

T.main();
T.compile();
T.writeHdl("sum_test.v");

'''},
    'h5': {'i' : 5,
           'n' : '05 - Thread',
           's' : '''channel Kernel.req = int;
channel Kernel.resp = int;

def Kernel.f() {
  *resp = *req + 1;
}

def Kernel.g() {
  *req = 10;
  print(*resp);
}

thread Kernel.t1 = f();
thread Kernel.t2 = g();

Kernel.compile();
Kernel.writeHdl("thr.v");
'''},
    'h6': {'i' : 6,
           'n' : '06 - Member',
           's' : '''object O = Kernel.clone();
object M = Kernel.clone();
object O.M = M;
def M.f(int a) (int) {
  return a + 1;
}

def O.main() {
  print(M.f(10));
}

O.compile();
O.writeHdl("call.v");
'''},
    'h7': {'i' : 7,
           'n' : '07 - External port',
           's' : '''object L = Kernel.clone();

@embed(output = "led")
def L.f(bool b) {
  // print(b);
}

def L.main() {
  bool b = false;
  while (true) {
    wait(10000000);
    f(b);
    b = ~b;
  }
}

L.compile();
L.writeHdl("led.v");
'''},
    'h8': {'i' : 8,
           'n' : '08 - Embedded module',
           's' : '''object M = Kernel.clone();

@embed(    resource = "wait_cycles",
    verilog = "nli_wait.v",
    ack = "ack",
    file= "copy",
    module= "wait_cycles")
def M.my_wait(int cycles) {
  print(cycles);
}

def M.main() {
  my_wait(10);
}

M.compile();
M.writeHdl("wait.v");
'''},
    'h9': {'i' : 9,
           'n' : '09 - Misc',
           's' : '''object M = Kernel.clone();

def M.main() {
  int i;
  for (i = 0; i < 10; i++) {
  }
}

M.setSynthParam("resetPolarity", "0");
M.setDump("zz");
M.compile();
M.writeHdl("dummy.v");
M.writeHdl("dummy.cpp");
'''},
    'default': {'i' : 999,
                'n' : 'Synth example',
         's' : '''def main() {
  int i;
  int s = 0;
  for (i = 0; i < 10; ++i) {
    s += i;
  }
  // TODO: Do real I/O.
  print(s);
}

// Synthesize and output.
compile();
writeHdl("a.v");
writeHdl("a.html");

// Run on interpreter mode.
main();
'''}
}
