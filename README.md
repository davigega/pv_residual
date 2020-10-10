# SuperCollider Residual Noise PV_Ugen

A PV_Ugen which extracts the residual noise of an input signal

## Compile

create a build folder:
```shell
$ mkdir build && cd build
```
compile with cmake:
```shell
$ cmake -DSC_PATH=/path/to/sc/source/ -DCMAKE_BUILD_TYPE=RELEASE ..
$ make
```
copy the compiled file and the class `PV_Residual.sc` into the user Extension folder.
If you don't know the Extension folder location, in SCIDE type and evaluate:

```
Platform.userExtensionDir
```
## Help File (schelp not ready yet)
In the mean time:
Like every PV_Ugen the `PV_Residual` needs an FFT chain to work. The second argument can be any float number bigger than 1. Usually values between 1.1 and 3 works better.

### Example
```
(
SynthDef(\pv_residual, {
	var
	fftSize = 2048,
	in = SinOsc.ar(400, 0, 0.1)+PinkNoise.ar(0.01),
	buf = LocalBuf(fftSize),
	fft = FFT(buf, in),

	res = PV_Residual(fft,MouseX.kr(1, 4)),
	ifft = IFFT(res);
	Out.ar(0, ifft);
}).play
)
```
