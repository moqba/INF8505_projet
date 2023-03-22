/*
-- File : ffi.v
--
-- Contents : DesignWare wrapper -- floating to integer conversion.
--
-- Copyright (c) 2018-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library flx_lib;
use flx_lib.data_types.all;

-- entity ffi : ffi
entity ffi is
  port (
    ohe_selector_EX : in std_logic;
    ffiA_in : in t_w32;
    ffiC_out : out t_w32);
end ffi;


architecture rtl of ffi is

  component DW_fp_flt2i
    generic (sig_width       : integer := 23;
             exp_width       : integer := 8;
             isize           : integer := 32;
             ieee_compliance : integer := 0);
    port (
          a      : in  std_logic_vector(exp_width+sig_width downto 0);
          rnd    : in  std_logic_vector(2 downto 0);
          z      : out std_logic_vector(isize-1 downto 0);
          status : out std_logic_vector(7 downto 0));
  end component;

  constant sig_width       : integer := 23;
  constant exp_width       : integer := 8;
  constant ieee_compliance : integer := 1;
  constant isize           : integer := 32;

  signal   ffiA    : std_logic_vector(31 downto 0);
  signal   ffiC    : std_logic_vector(31 downto 0);
  constant ffiRND  : std_logic_vector(2 downto 0) := "001"; -- round to zero (truncate) cf. C
  signal   ffiSTAT : std_logic_vector(7 downto 0);  -- unused

begin

  p_ffi_isolate : process(ohe_selector_EX,
                  ffiA_in)
  begin
    -- operand isolation
    if ohe_selector_EX = '0' then
      ffiA <= (others => '0');
    else
      ffiA <= std_logic_vector(ffiA_in);
    end if;
  end process p_ffi_isolate;

  dw_ffi: DW_fp_flt2i
  generic map (
    sig_width       => sig_width,
    exp_width       => exp_width,
    isize           => isize,
    ieee_compliance => ieee_compliance)
  port map (
    a      => ffiA,
    rnd    => ffiRND,
    z      => ffiC,
    status => ffiSTAT);

  ffiC_out <= signed(ffiC);

end rtl;

