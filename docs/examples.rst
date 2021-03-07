==============
Examples (WIP)
==============

Examples in this page are to understand concepts of Karuta language quickly (I hope everything is within your familiar concepts and paradigms).

.. contents::

Just a module
=============

.. code-block:: none

   module {
     reg r int
     ram a int[16]

     process p() {
       a[r]++
     }
   }

*module* keyword specifies an object and allows to define members inside it.

Communication
=============

.. code-block:: none

   module {
     channel ch int

     process p1() {
       ch.write(1)
     }

     process p2() {
       ch.read()
     }
   }

channels, regs, rams and most of member objects are accessible from multiple processes.

Module hierarchy
================

.. code-block:: none

   module {
     shared m module = new()

     process p() {
       m.ch.write(1)
     }
   }

   module m {
     channel ch int
     process p() {
       p.ch.read()
     }
   }

Matrix multiplication
=====================

.. code-block:: none

   module m {
     ram a int[4][4]
     ram b int[4][4]
     ram x int[4][4]

     func mult() {
       for var i int = 0; i < 4; ++i {
         for var j int = 0; j < 4; ++j {
           var t int = 0
           for var k int = 0; k < 4; ++k {
             t += a[i][k] * b[k][j]
           }
           x[i][j] = t
         }
       }
     }
     process p() {
       mult()
     }
   }
