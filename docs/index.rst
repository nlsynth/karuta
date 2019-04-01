(WIP) Welcome to Karuta's documentation! (WIP)
==============================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


NOTE: There may be mistakes or glitches in this document due to my English skill. Please feel free to point out (or ignore...) them.

NOTE: The word Karuta means Japanese playing cards.

Author: Yusuke Tabata (tabata.yusuke@gmail.com)

Karuta is an object-oriented scripting language and its compiler to design logic circuits. The main objective of Karuta is to improve the productivity of logic circuit design. This kind of software is usually known as HLS (High Level Synthesis).

Karuta has various features to support hardware design.

===========
Quick start
===========

Quick start

.. code-block:: none

    def main() {}

=================
Program structure
=================

======================
External communication
======================

======
Values
======

=======
Objects
=======

=====================
Source code structure
=====================

* src/

  * Command and common utilities.
* src/base

  * Common code for other components.
* src/compiler

  * Karuta Script to bytecode.
* src/fe

  * Karuta Script parser.
* src/synth

  * Bytecode to Iroha IR.
* src/vm

  * Bytecode executor.
* iroha/

  * Iroha backend.

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
