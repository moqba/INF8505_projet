#ifndef __PIN_MEMORIES_H__
#define __PIN_MEMORIES_H__

// program memory size = 2**PM_SIZE_NBIT in bytes
#define PM_SIZE_NBIT   18

// data memory size = 2**DM_SIZE_NBIT in bytes
#define DM_SIZE_NBIT   23

#define PM_SIZE (1ULL<<(PM_SIZE_NBIT)) /* in byte  */
#define DM_SIZE (1ULL<<(DM_SIZE_NBIT)) /* in byte */

// PM ; aligned addresses only
SC_MODULE(PMType)
{
public:
static const int addr_bits = 32;
static const int mem_size = PM_SIZE / 4;
  typedef sc_uint<32>   D;
  typedef sc_uint<addr_bits>    A;

private:
  D ram[mem_size];
public:
  sc_in_clk           clock;
  sc_in<bool>         ld, st;
  sc_in<A>            a;
  sc_in<D>            d;
  sc_out<D>           q;


  void prc_memory() {
    unsigned    ar = a.read();
    if (ld.read() && ar < mem_size) {
      q.write(ram[ar]);
    } else if (st.read() && ar < mem_size) {
      ram[ar] = d.read();
    }
  }

  SC_CTOR(PMType)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(int a, D val) {
    if (a < mem_size) ram[a] = val;
  }
  void iss_put(int a, int e, sc_uint<8> val) {
    if (a < mem_size) {
      ram[a].range(8*(e+1)-1,8*e) = val; // little endian
    }
  }
  D iss_get(int a) {
    return (a < mem_size) ? ram[a] : (D)0;
  }
  sc_uint<8> iss_get(int a, int e) {
    if (a < mem_size) {
      return ram[a].range(8*(e+1)-1,8*e); // little endian
    } else
      return 0;
  }
};



// memory with byte write enable, aligned accesses only
SC_MODULE(DMBankType)
{
public:
static const int addr_bits = 32;
static const int mem_size = DM_SIZE / 4;
  typedef sc_uint<32>           D;
  typedef sc_uint<addr_bits>    A;

private:
  D ram[mem_size];
public:

  sc_in_clk             clock;
  sc_in<bool>           ld;
  sc_in<sc_uint<4> >    st;
  sc_in<A>              a;
  sc_in<D>              d;
  sc_out<D>             q;


  void prc_memory() {
    unsigned    ar = a.read();
    sc_uint<4>  wen = st.read();
    if (ld.read() && ar < mem_size) {
      q.write(ram[ar]);
    } else if (wen != 0 && ar < mem_size) {
      D mem = ram[ar];
      D inp = d.read();
      for (int i = 0; i < 4; ++i) {
        if (wen[i] != 0) {
          mem.range(8*(i+1)-1,8*i) =
            inp.range(8*(i+1)-1,8*i);  // little endian
        }
      }
      ram[ar] = mem;
    }
  }

  SC_CTOR(DMBankType)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(int a, D val) {
    if (a < mem_size) ram[a] = val;
  }
  void iss_put(int a, int e, sc_uint<8> val) {
    if (a < mem_size) {
      ram[a].range(8*(e+1)-1,8*e) = val; // little endian
    }
  }
  D iss_get(int a) {
    return (a < mem_size) ? ram[a] : (D)0;
  }
  sc_uint<8> iss_get(int a, int e) {
    if (a < mem_size) {
      return ram[a].range(8*(e+1)-1,8*e); // little endian
    } else {
      return 0;
    }
  }
};


// memory with byte write enable, aligned accesses only
SC_MODULE(Memory)
{
public:
static const int addr_bits = 32;
static const int mem_size = DM_SIZE / 4;
  typedef sc_uint<8>           D;
  typedef sc_uint<addr_bits>    A;

private:
  D ram[mem_size];
public:

  sc_in_clk             clock;
  sc_in<bool>           ld;
  sc_in<bool>    st;
  sc_in<A>              a;
  sc_in<D>              d;
  sc_out<D>             q;


  void prc_memory() {
    unsigned    ar = a.read();
    bool  wen = st.read();
    if (ld.read() && ar < mem_size) {
      q.write(ram[ar]);
    } else if (wen != 0 && ar < mem_size) {
      D mem = ram[ar];
      D inp = d.read();
      ram[ar] = inp;
    }
  }

  SC_CTOR(Memory)
    : clock("clock"),ld("ld"),st("st"),a("a"),d("d"),q("q")
  {
    SC_METHOD(prc_memory);
    sensitive << clock.pos();
  }

  void iss_put(int a, D val) {
    if (a < mem_size) ram[a] = val;
  }

  D iss_get(int a) {
    return (a < mem_size) ? ram[a] : (D)0;
  }

};


#endif
