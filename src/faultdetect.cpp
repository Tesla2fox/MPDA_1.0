#include "Faultdetect.h"

vector<double> vVel;
vector<double> vKamount;
vector<double> vNoiseTs;
vector<double> vNoiseK;
void Faultdetect::loadTxt(const char * fileName)
{
	sscfg::ConfigFile cfg = cfg.load(fileName);
	cfg.get("vel", vVel);
	cfg.get("kamount", vKamount);
	cfg.get("noisets", vNoiseTs);
	cfg.get("noisek", vNoiseK);
}
