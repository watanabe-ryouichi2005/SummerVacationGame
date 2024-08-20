
#include <vector>
#include <stdint.h>
#include "Vector3.h"

    enum class MapChipType {
	    kBlank,//空白
	    kBlock,//ブロック
    };
struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};
class MapChipField {
public:
	// １ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
struct IndexSet {
	uint32_t xindex;
	uint32_t yindex;

};
struct Rect {
	float left;
	float right;
	float bottom;
	float top;
};
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filepath);
	MapChipType GetMapChipTypeByIndex(uint32_t xindex, uint32_t yindex);
	MapChipType GetMapChipTypeByPosition(const Vector3& positio);
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);
	Vector3 GetMapChipPositionByIndex(uint32_t xindex, uint32_t yindex);
	uint32_t GetkNumBlockVirtical();
	uint32_t GetkNumBlockHorizontal();
	Rect GetRectByIndex(uint32_t xindex,uint32_t yindex);
private:
	
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
	MapChipData mapChipData_;
};
