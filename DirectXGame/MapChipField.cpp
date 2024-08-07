#include "MapChipField.h"

#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

namespace{
	std::map<std::string, MapChipType> mapChipTable = {
		{"0", MapChipType::kBlank},
		{"1", MapChipType::kBlock}
	};
}

void MapChipField::ResetMapChipData() {
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for(std::vector<MapChipType>& line : mapChipData_.data){
		line.resize(kNumBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {
	ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;
	mapChipCsv << file.rdbuf();

	file.close();


	for(uint32_t i = 0; i < kNumBlockVirtical; ++i){
		std::string line;
		getline(mapChipCsv, line);

		std::istringstream line_stream(line);

		for(uint32_t j = 0; j < kNumBlockHorizontal; ++j){
			std::string word;
			getline(line_stream, word, ',');
			mapChipData_.data[i][j] = mapChipTable[word];
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t x, uint32_t y) const {
	if (x < 0 || kNumBlockHorizontal - 1 < x){
		return MapChipType::kBlank;
	}
	if (y < 0 || kNumBlockVirtical - 1 < y){
		return MapChipType::kBlank;
	}

	return mapChipData_.data[y][x];

}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t x, uint32_t y) const {
	return Vector3{
		kBlockWidth * x,
		kBlockHeight * (kNumBlockVirtical - 1 - y),
		0.f
	};
}


