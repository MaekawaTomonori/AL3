#include "MapChipField.h"

#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "Model.h"


namespace{
    std::map<std::string, MapBlockType> mapTable = {
    	{"0", MapBlockType::AIR},
    	{"1", MapBlockType::BLOCK},
    	{"2", MapBlockType::PLAYER},
    };

    std::map<std::string, MapData> loadedMaps;
}

void MapChipField::ResetMapData() {
    mapData_.blockType.clear();
    mapData_.blockType.resize(kNumBlockVertical);
    for (std::vector<MapBlockType>& mapDataLine : mapData_.blockType){
        mapDataLine.resize(kNumBlockHorizontal);
    }
}

MapChipField::~MapChipField() {
    mapData_.blockType.clear();
}

void MapChipField::LoadMapCsv(std::string filePath) {
    ResetMapData();

    //既に読み込んでいたら返す
    if (loadedMaps.contains(filePath)){
        mapData_ = loadedMaps[filePath];
        return;
    }

    //load method
    std::ifstream file;
    file.open(filePath);
    assert(file.is_open());

    std::stringstream mapCsv;
    mapCsv << file.rdbuf();
    file.close();


    std::string line;
    for (uint32_t i = 0; i < kNumBlockVertical; ++i){
        getline(mapCsv, line);

        std::istringstream lineStream(line);

        for (uint32_t j = 0; j < kNumBlockHorizontal; ++j){
            std::string word;
            getline(lineStream, word, ',');

            if (mapTable.contains(word)){
                mapData_.blockType[i][j] = mapTable[word];
            }
        }
    }

    loadedMaps[filePath] = mapData_;
}

MapBlockType MapChipField::getMapBlockTypeByIndex(uint32_t xIndex, uint32_t yIndex) const {
    if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex){
        return MapBlockType::AIR;
    }
    if (yIndex < 0 || kNumBlockVertical - 1 < yIndex){
        return MapBlockType::AIR;
    }

    return mapData_.blockType[yIndex][xIndex];
}

Vector3 MapChipField::getMapPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
    return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical - 1 - yIndex), 0);
}

MapData MapChipField::getMapData() const {
    return mapData_;
}

Map::~Map() {
    delete field_;
    delete blockModel_;
}

void Map::Initialize() {
    field_ = new MapChipField();
    field_->LoadMapCsv("Resources/map.csv");
    GenerateBlock();
    blockModel_ = new Model;
    blockModel_ = Model::CreateFromOBJ("block", true);
}

void Map::Update() {
    for (std::vector<WorldTransform*>& row : worldTransforms_){
        for (WorldTransform* wtfb : row){
            if (!wtfb)continue;
            wtfb->UpdateMatrix();
        }
    }
}

void Map::Draw(const ViewProjection& viewProjection) {
    for (auto blockLine : worldTransforms_){
        for (WorldTransform* block : blockLine){
            if (!block)continue;
            blockModel_->Draw(*block, viewProjection);
        }
    }
}

void Map::GenerateBlock() {
    worldTransforms_.resize(kNumBlockVertical);
    for (uint32_t row = 0; row < kNumBlockVertical; ++row){
        worldTransforms_[row].resize(kNumBlockHorizontal);
        for (uint32_t col = 0; col < kNumBlockHorizontal; ++col){
            if (field_->getMapBlockTypeByIndex(col, row) == MapBlockType::PLAYER){
                playerPos = field_->getMapPositionByIndex(col, row);
                continue;
            }
            if (field_->getMapBlockTypeByIndex(col, row) == MapBlockType::BLOCK){
                WorldTransform* wt = new WorldTransform;
                wt->Initialize();
                worldTransforms_[row][col] = wt;
                worldTransforms_[row][col]->translation_ = field_->getMapPositionByIndex(col, row);
            }
        }
    }
}
