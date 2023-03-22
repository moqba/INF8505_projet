
//User hdl for divide function

`timescale 1ns/1ps


module divide
  ( input                    reset,
    input                    clock,
    input                    start,
    input      signed [31:0] opA,
    input      signed [31:0] opB,
    output reg               ready,
    output reg        [63:0] result
  );

  reg        [31:0] B;
  reg        [31:0] pdg_update_B;
  reg               pdg_we_B;
  reg        [63:0] PA;
  reg        [63:0] pdg_update_PA;
  reg               pdg_we_PA;
  reg         [5:0] cnt;
  reg         [5:0] pdg_update_cnt;
  reg               pdg_we_cnt;

  // main
  always @ (*)
  begin : p_main
    reg         [5:0] new_cnt;
    reg               new_ready;
    reg        [63:0] new_result;
    reg signed [31:0] div_clb_result;
    reg signed [31:0] a;
    reg         [4:0] r;
    reg signed [31:0] tmp;
    reg         [4:0] n;
    reg        [31:0] tmp_0;
    reg        [63:0] div_step_result;
    reg        [63:0] new_pa;
    reg        [32:0] diff;

    ready = 1'b0;
    result = 64'h0;

    div_clb_result = 32'sh0;
    a = 32'sh0;
    r = 5'h0;
    tmp = 32'sh0;
    n = 5'h0;
    tmp_0 = 32'h0;
    div_step_result = 64'h0;
    new_pa = 64'h0;
    diff = 33'h0;

    pdg_we_B = 1'b0;
    pdg_update_B = 32'h0;
    pdg_we_PA = 1'b0;
    pdg_update_PA = 64'h0;
    pdg_we_cnt = 1'b0;
    pdg_update_cnt = 6'h0;

    new_cnt = 6'h0;
    new_ready = 1'b0;
    new_result = 64'h0;
    if (start)
    begin
      a = $signed($unsigned(opA));
      tmp = a;
      if ($signed(tmp[31 : 0]) == 32'sh0)
      begin
        r = 5'h1F;
      end
      else
      begin
        if ($signed(tmp[31 : 1]) == 31'sh0)
        begin
          r = 5'h1E;
        end
        else
        begin
          if ($signed(tmp[31 : 2]) == 30'sh0)
          begin
            r = 5'h1D;
          end
          else
          begin
            if ($signed(tmp[31 : 3]) == 29'sh0)
            begin
              r = 5'h1C;
            end
            else
            begin
              if ($signed(tmp[31 : 4]) == 28'sh0)
              begin
                r = 5'h1B;
              end
              else
              begin
                if ($signed(tmp[31 : 5]) == 27'sh0)
                begin
                  r = 5'h1A;
                end
                else
                begin
                  if ($signed(tmp[31 : 6]) == 26'sh0)
                  begin
                    r = 5'h19;
                  end
                  else
                  begin
                    if ($signed(tmp[31 : 7]) == 25'sh0)
                    begin
                      r = 5'h18;
                    end
                    else
                    begin
                      if ($signed(tmp[31 : 8]) == 24'sh0)
                      begin
                        r = 5'h17;
                      end
                      else
                      begin
                        if ($signed(tmp[31 : 9]) == 23'sh0)
                        begin
                          r = 5'h16;
                        end
                        else
                        begin
                          if ($signed(tmp[31 : 10]) == 22'sh0)
                          begin
                            r = 5'h15;
                          end
                          else
                          begin
                            if ($signed(tmp[31 : 11]) == 21'sh0)
                            begin
                              r = 5'h14;
                            end
                            else
                            begin
                              if ($signed(tmp[31 : 12]) == 20'sh0)
                              begin
                                r = 5'h13;
                              end
                              else
                              begin
                                if ($signed(tmp[31 : 13]) == 19'sh0)
                                begin
                                  r = 5'h12;
                                end
                                else
                                begin
                                  if ($signed(tmp[31 : 14]) == 18'sh0)
                                  begin
                                    r = 5'h11;
                                  end
                                  else
                                  begin
                                    if ($signed(tmp[31 : 15]) == 17'sh0)
                                    begin
                                      r = 5'h10;
                                    end
                                    else
                                    begin
                                      if ($signed(tmp[31 : 16]) == 16'sh0)
                                      begin
                                        r = 5'hF;
                                      end
                                      else
                                      begin
                                        if ($signed(tmp[31 : 17]) == 15'sh0)
                                        begin
                                          r = 5'hE;
                                        end
                                        else
                                        begin
                                          if ($signed(tmp[31 : 18]) == 14'sh0)
                                          begin
                                            r = 5'hD;
                                          end
                                          else
                                          begin
                                            if ($signed(tmp[31 : 19]) == 13'sh0)
                                            begin
                                              r = 5'hC;
                                            end
                                            else
                                            begin
                                              if ($signed(tmp[31 : 20]) == 12'sh0)
                                              begin
                                                r = 5'hB;
                                              end
                                              else
                                              begin
                                                if ($signed(tmp[31 : 21]) == 11'sh0)
                                                begin
                                                  r = 5'hA;
                                                end
                                                else
                                                begin
                                                  if ($signed(tmp[31 : 22]) == 10'sh0)
                                                  begin
                                                    r = 5'h9;
                                                  end
                                                  else
                                                  begin
                                                    if ($signed(tmp[31 : 23]) == 9'sh0)
                                                    begin
                                                      r = 5'h8;
                                                    end
                                                    else
                                                    begin
                                                      if ($signed(tmp[31 : 24]) == 8'sh0)
                                                      begin
                                                        r = 5'h7;
                                                      end
                                                      else
                                                      begin
                                                        if ($signed(tmp[31 : 25]) == 7'sh0)
                                                        begin
                                                          r = 5'h6;
                                                        end
                                                        else
                                                        begin
                                                          if ($signed(tmp[31 : 26]) == 6'sh0)
                                                          begin
                                                            r = 5'h5;
                                                          end
                                                          else
                                                          begin
                                                            if ($signed(tmp[31 : 27]) == 5'sh0)
                                                            begin
                                                              r = 5'h4;
                                                            end
                                                            else
                                                            begin
                                                              if ($signed(tmp[31 : 28]) == 4'sh0)
                                                              begin
                                                                r = 5'h3;
                                                              end
                                                              else
                                                              begin
                                                                if ($signed(tmp[31 : 29]) == 3'sh0)
                                                                begin
                                                                  r = 5'h2;
                                                                end
                                                                else
                                                                begin
                                                                  if ($signed(tmp[31 : 30]) == 2'sh0)
                                                                  begin
                                                                    r = 5'h1;
                                                                  end
                                                                  else
                                                                  begin
                                                                    r = 5'h0;
                                                                  end
                                                                end
                                                              end
                                                            end
                                                          end
                                                        end
                                                      end
                                                    end
                                                  end
                                                end
                                              end
                                            end
                                          end
                                        end
                                      end
                                    end
                                  end
                                end
                              end
                            end
                          end
                        end
                      end
                    end
                  end
                end
              end
            end
          end
        end
      end
      div_clb_result = $signed({{27{1'b0}}, r});
      n = div_clb_result[4:0];
      tmp_0 = $unsigned(opA) << n;
      pdg_we_PA = 1'b1;
      pdg_update_PA = {{32{1'b0}}, tmp_0};
      pdg_we_B = 1'b1;
      pdg_update_B = $unsigned(opB);
      new_cnt = 6'h21 - {1'b0, n};
    end
    else
    begin
      if (cnt > 6'h1)
      begin
        new_pa = PA << 1'b1;
        diff = {1'b0, new_pa[63 : 32]} - {1'b0, B};
        if (diff[32] == 1'b0)
        begin
          new_pa[63 : 32] = diff[31:0];
          new_pa[0] = 1'b1;
        end
        div_step_result = new_pa;
        pdg_we_PA = 1'b1;
        pdg_update_PA = div_step_result;
        new_cnt = cnt - 6'h1;
      end
      else
      begin
        if (cnt == 6'h1)
        begin
          new_result = PA;
          new_ready = 1'b1;
          new_cnt = 6'h0;
        end
      end
    end
    pdg_we_cnt = 1'b1;
    pdg_update_cnt = new_cnt;
    ready = new_ready;
    result = new_result;
  end //p_main



  always @ (posedge clock or posedge reset)
  begin : p_update_status
    if (reset)
    begin
      B <= 32'h0;
      PA <= 64'h0;
      cnt <= 6'h0;
    end
    else
    begin
      if (pdg_we_B)
        B <= pdg_update_B;
      if (pdg_we_PA)
        PA <= pdg_update_PA;
      if (pdg_we_cnt)
        cnt <= pdg_update_cnt;
    end
  end // p_update_status

endmodule // divide
