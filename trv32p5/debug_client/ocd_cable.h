/*
-- File : ocd_cable.h
--
-- Contents : Physical OCD link - abstract interface.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef _ocd_cable_h
#define _ocd_cable_h

#include <string>
#include <AddressType.h>

/*

 The ocd_cable class specifies an abstract interface for the physical
 connection of an on chip debugging implementation. It specifies the methods
 that are required to write to and read from the registers of the debug
 controller. These methods are called in the pdc_commands class.

 The interface assumes that communication is buffered. The add_ functions do
 not directly perform their action, but rather add this action to a buffer. The
 buffer is flushed when the send_and_receive() method is called. At that point
 in time, the get_next_data() function can be called to collect that results of
 the various read commands that were added to the buffer. It is the
 responsibility of the derived class to implement the buffer.

*/


class ocd_cable {
public:

    ocd_cable(int id, std::string srvr, int port)
        : coreid(id), server(srvr), port(port) { };

    /* Constructor: can initialize the data structures that are needed to
     * operate the physical link and the buffer. There are two parameters:
     * - id: the identifier of the core in a multi core system.
     * - srvr: the name of the host in case the cable is driven by a separate
     *   machine.
     */

    virtual ~ocd_cable() { }

    enum reg_type { data, addr, inst, stat, ctxt };

    /* The Go-generated debug controller contains 4 registers:
     * data : selects the nML register with property ocd_data_register.
     * addr : selects the nML register with property ocd_address_register.
     * inst : selects the nML register with property ocd_instruction_register.
     * stat : selects the internal status register of the debug controller.
     * ctxt : selects the nML register with property ocd_context_register.
     */

    virtual int open() = 0;
    virtual int close() = 0;

    virtual int add_iwrite(long long) = 0;

    /* Write a debugger instruction code into the JTAG_IREG register or it's
     * equivalent in case of a non-JTAG based implementation.
     */

    virtual int add_dwrite(reg_type, const DataType&) = 0;

    /* Write a value to the selected debug controller register. */

    virtual int add_dread(reg_type) = 0;

    /* Read a value from the selected debug controller register. */

    virtual int add_dwrite_dread(reg_type, const DataType&) = 0;

    /* Read a value from the selected debug controller register, while
     * simultaneously writing to the same register.
     */

    virtual int send_and_receive() = 0;

    /* Send the buffered read and write commands to device and capture the
     * replies to the read commands.
     */

    virtual int get_next_data(DataType&) = 0;

    /* Retrieve next buffered reply. */

    virtual bool buffer_overflow_imminent() { return false; }
    virtual bool buffer_is_empty() { return true; }

    virtual void set_verbose(int) = 0;

protected:
    int coreid;
    std::string server;
    int port;
};

#endif
