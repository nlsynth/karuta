# Karuta
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
TL;DR:
    High level synthesis (HLS) from scripting language (Karuta) to RTL (Verilog).
    The main objective is to make FPGA development productive.

See [docs/index.rst](docs/index.rst) or its [public copy at readthedocs.io](https://karuta.readthedocs.io/en/latest/) for more details.
In case you really like this software, please be a patron from [Patreon](https://www.patreon.com/karuta).

## Quick overview
Karuta Script is an object oriented scripting language. The syntax is similar to recent programming languages like JavaScript, Python, Ruby or so on.
Minimum code looks like as follows.

     func main() {
       // Do computation, call other methods and some I/O.
     }

This defines a method 'main' of current object. It can be called like this.

     main() // obj.main() can be used to specify an object.

Now some computation is defined within the object, so Karuta compiler can take a snapshot of this object and transform it into RTL.

     compile()  // A snapshot is taken.
     // "my_module_rtl.html" is also possible.
     writeHdl("my_module_rtl.v")

## Important features

This project designed its own language Karuta just only for RTL design instead of reusing existing languages.
So, some of following features are incorporated in the language constructs to make it easy to use.

* Prototype based object system to model design structures
* Flexible data types
    * Integer with width. Custom operators for defined data types like FP16
* Communication primitives
    * Threads, mailboxes, channels and so on
    * AXI, RPC like handshake, GPIO, embedded verilog and so on
* HDL generators and optimizers
    * Generates Verilog or HTML
    * SSA based optimizers
    * Scheduling and allocation based on device parameters

## COPYING

See COPYING file. Feel free to ask me to change to other licenses, if it is inconvenient for you.

The license of course doesn't apply to the outputs of Karuta. It's up to the author of input source code.
