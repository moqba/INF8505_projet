/*
-- File : fcp.v
--
-- Contents : DesignWare wrapper -- floating point comparator.
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
use flx_lib.fcp_cst.all;

-- entity fcp : fcp
entity fcp is
  port (
    bin_selector_EX : in std_logic_vector(1 downto 0);
    fcpA_in : in t_w32;
    fcpB_in : in t_w32;
    fcpC_out : out t_w32);
end fcp;


architecture rtl of fcp is

  component DW_fp_cmp
    generic (sig_width       : integer := 23;
             exp_width       : integer := 8;
             ieee_compliance : integer := 0);
    port (
          a         : in  std_logic_vector(sig_width + exp_width downto 0);
          b         : in  std_logic_vector(sig_width + exp_width downto 0);
          zctr      : in  std_logic;
          aeqb      : out std_logic;
          altb      : out std_logic;
          agtb      : out std_logic;
          unordered : out std_logic;
          z0        : out std_logic_vector(sig_width + exp_width downto 0);
          z1        : out std_logic_vector(sig_width + exp_width downto 0);
          status0   : out std_logic_vector(7 downto 0);
          status1   : out std_logic_vector(7 downto 0));
  end component;

  constant sig_width       : integer := 15;
  constant exp_width       : integer := 8;
  constant data_width      : integer := 1 + exp_width + sig_width;
  constant ieee_compliance : integer := 1;

  signal   fcpA  : std_logic_vector(data_width-1 downto 0);
  signal   fcpB  : std_logic_vector(data_width-1 downto 0);
  signal   fcpC  : std_logic_vector(31 downto 0);
  signal   fcpLT : std_logic;
  signal   fcpGT : std_logic;
  signal   fcpEQ : std_logic;
  signal   fcpUO : std_logic;
  constant fcpZ  : std_logic := '0';
  signal   fcpZ0 : std_logic_vector(data_width-1 downto 0);
  signal   fcpZ1 : std_logic_vector(data_width-1 downto 0);
  signal   fcpS0 : std_logic_vector(7 downto 0);
  signal   fcpS1 : std_logic_vector(7 downto 0);

begin

  p_fcp_isolate : process(bin_selector_EX,
                  fcpA_in,
                  fcpB_in)
  begin
    -- operand isolation
    if bin_selector_EX = "00" then
      fcpA <= (others => '0');
      fcpB <= (others => '0');
    else
      fcpA <= std_logic_vector(fcpA_in(data_width-1 downto 0));
      fcpB <= std_logic_vector(fcpB_in(data_width-1 downto 0));
    end if;
  end process p_fcp_isolate;

  dw_fcp: DW_fp_cmp
    generic map (
      sig_width => sig_width,
      exp_width => exp_width,
      ieee_compliance => ieee_compliance)
    port map (
      a         => fcpA,
      b         => fcpB,
      zctr      => fcpZ,
      aeqb      => fcpEQ,
      altb      => fcpLT,
      agtb      => fcpGT,
      unordered => fcpUO,
      z0        => fcpZ0,
      z1        => fcpZ1,
      status0   => fcpS0,
      status1   => fcpS1);

  p_fcp_result : process(bin_selector_EX,
                         fcpLT,
                         fcpEQ)
  begin
    fcpC <= "00000000000000000000000000000000";
    case bin_selector_EX is
      when sel_sfle_w32 =>
          if (fcpLT = '1' or fcpEQ = '1') then
              fcpC <= "00000000000000000000000000000001";
          end if;
      when sel_sflt_w32 =>
          if (fcpLT = '1') then
              fcpC <= "00000000000000000000000000000001";
          end if;
      when sel_sfeq_w32 =>
          if (fcpEQ = '1') then
              fcpC <= "00000000000000000000000000000001";
          end if;
      when others =>
        null;
    end case;
  end process p_fcp_result;

  fcpC_out <= signed(fcpC);

end rtl;
