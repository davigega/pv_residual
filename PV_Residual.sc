PV_Residual : PV_ChainUGen
{
	*new {arg buffer, exponent = 2.0;
		^this.multiNew('control', buffer, exponent);
		}
}
