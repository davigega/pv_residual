#include "SC_fftlib.h"
#include "FFT_UGens.h"
#include <math.h>

InterfaceTable *ft;

struct PV_Residual : public PV_Unit
{
  // float mExp;
  SndBuf *m_buf;
};

extern "C"
{
  void PV_Residual_Ctor(PV_Residual *unit);
  void PV_Residual_next(PV_Residual *unit, int inNumSamples);
}

void PV_Residual_Ctor(PV_Residual *unit)
{
  // unit->mExp = std::max(IN0(1), 1.0);
  ZOUT0(0) = ZIN0(0);
  SETCALC(PV_Residual_next);
}

void PV_Residual_next(PV_Residual *unit, int inNumSamples)
{
  PV_GET_BUF
  RGen& rgen = *unit->mParent->mRGen;

	SCPolarBuf *out = ToPolarApx(buf);
  float exp = std::max(ZIN0(1), 1.f);
	// float exp = unit->mExp;
  float highest = 1.f;

  // find heighest peak
  for (int i=0; i<numbins; i++) {
    if(highest < out->bin[i].mag){
      highest = out->bin[i].mag;
    }
  }

  // substract the exponential spectra with itself
	for (int i=0; i<numbins; ++i) {
	  float thisMag = out->bin[i].mag;
    float normalize = thisMag/highest;
    float magPow = pow(normalize,exp)*highest;
    out-> bin[i].mag = thisMag-magPow;
    // add random phases
    out-> bin[i].phase = rgen.frand() * twopi;
  }
}


#define DefinePVUnit(name)						\
	(*ft->fDefineUnit)(#name, sizeof(PV_Unit), (UnitCtorFunc)&name##_Ctor, 0, 0);


PluginLoad(PV_Residual)
{
  ft = inTable;
  DefinePVUnit(PV_Residual);
}
