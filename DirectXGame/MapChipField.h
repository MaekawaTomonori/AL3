#pragma once
#include <string>
#include <vector>

#include "Vector3.h"

enum class MapChipType{
	kBlank,
	kBlock
};

struct MapChipData{
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField{
	static inline const float kBlockWidth = 1.f;
	static inline const float kBlockHeight = 1.f;

	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	//static inline const float 


private: //variables
	MapChipData mapChipData_;

	void ResetMapChipData();

public: //functions
	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t x, uint32_t y) const;
	Vector3 GetMapChipPositionByIndex(uint32_t x, uint32_t y) const;

	uint32_t GetNumBlockHorizontal() const { return kNumBlockHorizontal; }
	uint32_t GetNumBlockVirtical() const { return kNumBlockVirtical; }
};

