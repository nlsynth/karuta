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
   def f(x int) {
   }

.. code-block:: none

   @ExtFlowStub(name="e")
   def f(x int) (int) {
   }
