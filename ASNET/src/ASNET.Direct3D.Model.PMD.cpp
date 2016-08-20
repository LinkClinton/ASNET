#include "ASNET.Direct3D.Model.PMD.h"

float ASNET::Graph::Direct3D::PMDModel::PMDFloatRead(std::ifstream*  file){
	PMDFloat Float;
	for (int i = 0; i < 4; i++)
		*file >> Float._char[i];
	return Float._float;
}

short ASNET::Graph::Direct3D::PMDModel::PMDShortRead(std::ifstream * file){
	PMDShort Short;
	for (int i = 0; i < 2; i++)
		*file >> Short._char[i];
	return Short._short;
}

DWORD ASNET::Graph::Direct3D::PMDModel::PMDDwordRead(std::ifstream * file){
	PMDDword Dword;
	for (int i = 0; i < 4; i++)
		*file >> Dword._char[i];
	return Dword._Dwrod;
}

WORD ASNET::Graph::Direct3D::PMDModel::PMDWordRead(std::ifstream * file){
	PMDWord Word;
	for (int i = 0; i < 2; i++)
		*file >> Word._char[i];
	return Word._Word;
}

void ASNET::Graph::Direct3D::PMDModel::PMDRuleOut(std::ifstream * file, int num) {
	char c;
	for (int i = 0; i < num; i++)
		*file >> c;
}
