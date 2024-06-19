#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "Model.h"
#include "nullable.h"
#include "Vector3.h"
#include "WorldTransform.h"

enum class MapBlockType{
	AIR,
	BLOCK,
	PLAYER,
};

struct MapData{
	std::vector<std::vector<MapBlockType>> blockType;
};

	static inline const uint32_t kNumBlockVertical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	static inline const float kBlockWidth = 2.f;
	static inline const float kBlockHeight = 2.f;

class MapChipField{
private:
	MapData mapData_;
	void ResetMapData();

public:
	~MapChipField();
	void LoadMapCsv(std::string filePath);
	MapBlockType getMapBlockTypeByIndex(uint32_t xIndex, uint32_t yIndex) const;
	static Vector3 getMapPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	MapData getMapData() const;
};

class Map{
private:
	MapChipField* field_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransforms_;

	Model* blockModel_ = nullptr;

	nullable<Vector3> playerPos;

public:
	struct IndexSet{
		uint32_t xIndex;
		uint32_t yIndex;
	};

	struct Rect{
		float Left;
		float Right;
		float Bottom;
		float Top;
	};

	~Map();
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection);


	//GetPlayer
	//return player location
	//@nullable
	nullable<Vector3> getPlayer() const {
		return playerPos;
	}

	IndexSet GetMapIndexSetByPosition(const Vector3& position) const;
	MapBlockType GetMapBlockTypeByIndex(IndexSet index) const;
	Rect GetRectByIndex(IndexSet index);

private: //private methods
	void GenerateBlock();
};
