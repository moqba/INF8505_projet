/*
-- File : fas.v
--
-- Contents : DesignWare wrapper -- floating point adder.
--
-- Copyright (c) 2018-2019 Synopsys, Inc. This Synopsys processor model
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

-- entity fas : fas
entity fas is
  port (
    clock : in std_logic;
    ohe_selector_EX : in std_logic;
    fasA_in : in t_w32;
    fasB_in : in t_w32;
    fasM_in : in t_uint1;
    fasC_out : out t_w32);
end fas;


architecture rtl of fas is

  component DW_fp_addsub
    generic (sig_width       : integer := 23;
             exp_width       : integer := 8;
             ieee_compliance : integer := 0);
    port (
          a      : in  std_logic_vector(sig_width+exp_width downto 0);
          b      : in  std_logic_vector(sig_width+exp_width downto 0);
          rnd    : in  std_logic_vector(2 downto 0);
          op     : in  std_logic;
          z      : out std_logic_vector(sig_width+exp_width downto 0);
          status : out std_logic_vector(7 downto 0));
  end component;

  constant sig_width       : integer := 15;
  constant exp_width       : integer := 8;
  constant data_width      : integer := 1 + exp_width + sig_width;
  constant ieee_compliance : integer := 1;

  signal   fasA      : std_logic_vector(data_width-1 downto 0);
  signal   fasB      : std_logic_vector(data_width-1 downto 0);
  signal   fasC      : std_logic_vector(data_width-1 downto 0);
  signal   fasM      : std_logic;
  constant fasRND    : std_logic_vector(2 downto 0) := "000"; -- round to nearest (even)
  signal   fasSTAT   : std_logic_vector(7 downto 0);  -- unused
  signal   fasC_DLY1 : std_logic_vector(data_width-1 downto 0);

begin

  p_fas_isolate : process(ohe_selector_EX,
                  fasA_in,
                  fasB_in,
                  fasM_in)
  begin
    -- operand isolation
    if ohe_selector_EX = '0' then
      fasA <= (others => '0');
      fasB <= (others => '0');
      fasM <= '0';
    else
      fasA <= std_logic_vector(fasA_in(data_width-1 downto 0));
      fasB <= std_logic_vector(fasB_in(data_width-1 downto 0));
      fasM <= std_logic(fasM_in);
    end if;
  end process p_fas_isolate;

  dw_fas: DW_fp_addsub
  generic map (
    sig_width       => sig_width,
    exp_width       => exp_width,
    ieee_compliance => ieee_compliance)
  port map (
    a      => fasA,
    b      => fasB,
    rnd    => fasRND,
    op     => fasM,
    z      => fasC,
    status => fasSTAT);

  p_ms_fas : process(clock)
  begin
    if clock'event and clock = '1' then
      fasC_DLY1 <= fasC;
    end if;
  end process p_ms_fas;

  fasC_out <= signed("00000000" & fasC_DLY1);

end rtl;

