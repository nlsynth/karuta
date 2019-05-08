Experimental features
=====================

.. contents::

Karuta has some experimental and premature features to see their feasibility and implementation difficulty.

They might be remove without notice, probably due to low convenience against high maintenance burden.

---------
Data flow
---------

.. code-block:: none

   @DataFlowEntry()
   func f(x int) {
   }

.. code-block:: none

   @ExtFlowStub(name="e")
   func f(x int) (int) {
   }

-------------------------
Thread member declaration
-------------------------

Threads can be declared as a member object instead of @ThreadEntry().

.. code-block:: none

   func f() {
   }
   thread Kernel.thr1 = f()
   run()

------------------------
External SRAM operations
------------------------

Memory object represents an address space and can be accessed by read/write method.
This assumes 32bit address/data for now.

.. code-block:: none

   Memory.read(addr)
   Memory.write(addr, data)
