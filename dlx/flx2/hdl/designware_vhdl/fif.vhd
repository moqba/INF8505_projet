/*
-- File : fif.v
--
-- Contents : DesignWare wrapper -- integer to float conversion.
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

-- entity fif : fif
entity fif is
  port (
    ohe_selector_EX : in std_logic;
    fifA_in : in t_w32;
    fifC_out : out t_w32);
end fif;

architecture rtl of fif is

  component DW_fp_i2flt
    generic (sig_width : integer := 23;
             exp_width : integer := 8;
             isize     : integer := 32;
             isign     : integer := 1);
    port (
          a      : in  std_logic_vector(isize-1 downto 0);
          rnd    : in  std_logic_vector(2 downto 0);
          z      : out std_logic_vector(exp_width + sig_width downto 0);
          status : out std_logic_vector(7 downto 0));
  end component;

  constant sig_width : integer := 23;
  constant exp_width : integer := 8;
  constant isize     : integer := 32;
  constant isign     : integer := 1;

  signal   fifA    : std_logic_vector(31 downto 0);
  signal   fifC    : std_logic_vector(31 downto 0);
  constant fifRND  : std_logic_vector(2 downto 0) := "000"; -- round to nearest (even)
  signal   fifSTAT : std_logic_vector(7 downto 0);  -- unused

begin

  p_fif_isolate : process(ohe_selector_EX,
                  fifA_in)
  begin
    -- operand isolation
    if ohe_selector_EX = '0' then
      fifA <= (others => '0');
    else
      fifA <= std_logic_vector(fifA_in);
    end if;
  end process p_fif_isolate;

  dw_fif: DW_fp_i2flt
  generic map (
    sig_width => sig_width,
    exp_width => exp_width,
    isize     => isize,
    isign     => isign)
  port map (
    a      => fifA,
    rnd    => fifRND,
    z      => fifC,
    status => fifSTAT);

  fifC_out <= signed(fifC);

end rtl;
