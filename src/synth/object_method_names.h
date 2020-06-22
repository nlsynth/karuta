// -*- C++ -*-
#ifndef _synth_object_method_names_h_
#define _synth_object_method_names_h_

namespace synth {

const char kAssert[] = "assert";
const char kPrint[] = "print";
const char kMain[] = "main";
const char kAxiLoad[] = "load";
const char kAxiStore[] = "store";
const char kChannelRead[] = "channel_read";
const char kChannelWrite[] = "channel_write";
const char kChannelNoWaitWrite[] = "channel_no_wait_write";
const char kDecrementTick[] = "decrement_tick_count";
const char kGetTickCount[] = "get_tick_count";
const char kIORead[] = "io_read";
const char kIOWrite[] = "io_write";
const char kSlaveWait[] = "wait";
const char kSramRead[] = "sram_read";
const char kSramWrite[] = "sram_write";
const char kMailboxGet[] = "mailbox_get";
const char kMailboxPut[] = "mailbox_put";
const char kMailboxWait[] = "mailbox_wait";
const char kMailboxNotify[] = "mailbox_notify";
const char kMailboxWidth[] = "mailbox_width";

}  // namespace synth

#endif  // _synth_object_method_names_h_
