/*
-- File : fml.v
--
-- Contents : DesignWare wrapper -- floating point multiplier.
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

-- entity fml : fml
entity fml is
  port (
    clock : in std_logic;
    ohe_selector_EX : in std_logic;
    fmlA_in : in t_w32;
    fmlB_in : in t_w32;
    fmlC_out : out t_w32);
end fml;

architecture rtl of fml is

  component DW_fp_mult
    generic (sig_width       : integer := 23;
             exp_width       : integer := 8;
             ieee_compliance : integer := 0);
    port (
          a      : in  std_logic_vector(exp_width + sig_width downto 0);
          b      : in  std_logic_vector(exp_width + sig_width downto 0);
          rnd    : in  std_logic_vector(2 downto 0);
          z      : out std_logic_vector(exp_width + sig_width downto 0);
          status : out std_logic_vector(7 downto 0));
  end component;

  constant sig_width       : integer := 23;
  constant exp_width       : integer := 8;
  constant ieee_compliance : integer := 1;

  signal   fmlA      : std_logic_vector(31 downto 0);
  signal   fmlB      : std_logic_vector(31 downto 0);
  signal   fmlC      : std_logic_vector(31 downto 0);
  constant fmlRND    : std_logic_vector( 2 downto 0) := "000"; -- round to nearest (even)
  signal   fmlSTAT   : std_logic_vector( 7 downto 0);  -- unused
  signal   fmlC_DLY1 : std_logic_vector(31 downto 0);

begin

  p_fml_isolate : process(ohe_selector_EX,
                  fmlA_in,
                  fmlB_in)
  begin
    -- operand isolation
    if ohe_selector_EX = '0' then
      fmlA <= (others => '0');
      fmlB <= (others => '0');
    else
      fmlA <= std_logic_vector(fmlA_in);
      fmlB <= std_logic_vector(fmlB_in);
    end if;
  end process p_fml_isolate;

  dw_spmp : DW_fp_mult
    generic map (
      sig_width => sig_width,
      exp_width => exp_width,
      ieee_compliance => ieee_compliance)
    port map (
      a      => fmlA,
      b      => fmlB,
      rnd    => fmlRND,
      z      => fmlC,
      status => fmlSTAT);

  p_ms_fml : process(clock)
  begin
    if clock'event and clock = '1' then
      fmlC_DLY1 <= fmlC;
    end if;
  end process p_ms_fml;

  fmlC_out <= signed(fmlC_DLY1);

end rtl;
