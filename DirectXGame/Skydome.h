#include"Model.h"
#include "WorldTransform.h"

class Skydome{
public:
	void Initialize(Model* model,uint32_t texturHandle,ViewProjection* viewProjection);
	void Update();
void Draw();

private:

WorldTransform worldTransform_ ;
	ViewProjection* viewProjection_ = nullptr;
uint32_t texturHandle_ = 0u;
	Model* model_ = nullptr ;
};