=====================
Experimental features
=====================

.. contents::

Karuta has some experimental and premature features to see their feasibility and implementation difficulty. This section describes such features.

They might be remove without notice, probably due to low convenience against high maintenance burden.

Data flow
=========

.. code-block:: none

   @data_flow_entry()
   func f(x int) {
   }

.. code-block:: none

   @ext_flow_stub(name="e")
   func f(x int) (int) {
   }

External SRAM operations
========================

Memory object represents an address space and can be accessed by read/write method.
This assumes 32bit address/data for now.

.. code-block:: none

   Memory.read(addr)
   Memory.write(addr, data)

Multi dimensional arrays
========================

Multi dimensional array is just an additional view of a normal 1 dimensional array.

.. code-block:: none

   shared a int[4][4]

   func main() {
     x[1][2]
   }
